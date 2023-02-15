#include "stm32f4xx.h"

volatile unsigned char rx2Flag = 0;   
char rx2Data[50];

void UART2_init(){
  GPIO_InitTypeDef   GPIO_InitStructure;    //GPIO �ʱⰪ �����ϱ� ���� ������ �����ϱ� ���� ����ü
  USART_InitTypeDef USART_InitStructure;  
  NVIC_InitTypeDef   NVIC_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);     //USART2_TX
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);    //USART2_RX

  //���ͷ�Ʈ enable �� Priority ����.
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;  //������ �̸����� ���ͷ�Ʈ �����ؾ��Ѵ�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    // NVIC �ʱ�ȭ > �����ߴ� ���� NVIC�� ����

  USART_InitStructure.USART_BaudRate = 115200;    //��� �ӵ� BPS
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ϳ��� ������ 5~9bits ����, ������ 8��Ʈ ����
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;    //����� ���� �ְ� ���� ���� ���� (Stop Bits �տ� ����), ¦�� Ȧ���� ����, ¦�� = 1�� ���� ¦��, Ȧ�� = 1�� ���� Ȧ���� �����ϱ�, �⺻���� ����üũ ��� 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // �帧����, pc�� ���� �帧�����ϴ� ��
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //�� �������θ� ���� �Ǵ� �����ϰڴ�(���⼭�� ������ ������� �� �� ���ڴ�) 
  USART_Init(USART2, &USART_InitStructure); 

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // USART1 Interrupt enable
  USART_Cmd(USART2, ENABLE);
}

void Serial2_Send(unsigned char t)
{
  USART_SendData(USART2, t);
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); //USART���� FLAG_TXE�� �ִ°�
}

void Serial2_Send_String(char* s)
{
  while( *s != '\0')    //null�� �ƴ�
  {
   Serial2_Send((unsigned char)(*s));
   s++;   //s = s + 1;
  }
}

int putchar(int ch)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2,ch);
	return ch;
}

void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
	static int i=0;
	rx2Data[i] = USART_ReceiveData(USART2);
	if(rx2Data[i] == '\r')  //���� �����Ϳ� ���� \n�� ���� ��� 
	{
		rx2Data[i] = '\0';
		rx2Flag = 1;
		i = 0;
	}
	else
	{
		i++;
	}
  }
}

void print_2d1(double number)		        /* floating-point number xx.x */
{ 
        unsigned int i, j;

	j = (int)(number*10. + 0.5);       //10�� ���ؼ� 0.5�� ���ϰ� int������ �ٲٸ� �ݿø��ȴ�(0.5�� ���� �ݿø� �� ���ڴ� �ݿø��ȴ�) 
	i = j / 100;					// 10^1
	if(i == 0) Serial2_Send(' ');   // �տ� ������ ����
	else       Serial2_Send(i + '0');   //0�� �ƽ�Ű�ڵ� 0x30 �� ���Ѵ�

	j = j % 100;					// 10^0
	i = j / 10;
	Serial2_Send(i + '0');
	Serial2_Send('.');

	i = j % 10;					// 10^-1
	Serial2_Send(i + '0');
}