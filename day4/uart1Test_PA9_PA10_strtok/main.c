/******************************************************************************
  ��Ʈ ����:
    1)  ARM Cortex-M4 ����� ��ƮA�� 9~10������(PA9~PA10) 2�� ���̺��
        UART����� RXD, TXD �ɿ� �����Ѵ�.
******************************************************************************/
// stm32f4xx�� �� �������͵��� ������ �������
#include "stm32f4xx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_SIZE 50
#define ARR_CNT 5   //����Ʈ �迭�� ����


volatile unsigned char rx1Flag = 0;   
char rx1Data[50];    //rx1Data �� ���ŵǴ� ������ ũ��   
void Serial_Event();  //���� �Լ� ������ ����, \n������ �����͸� ����
void Serial_Send(unsigned char t);    //���ڿ��� �����ϴ� �Լ�
void Serial_Send_String(char* s); 
int putchar(int ch);     //printf�� ����ϱ� ���� �Լ�
void print_2d1(double number);    //���� 2�ڸ�, �Ҽ��� 1�ڸ��� ��Ÿ���ڴ�

int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;    //GPIO �ʱⰪ �����ϱ� ���� ������ �����ϱ� ���� ����ü
  USART_InitTypeDef USART_InitStructure;  
  NVIC_InitTypeDef   NVIC_InitStructure;    //��ø������ ���ͷ�Ʈ ����ü ����(���ͷ�Ʈ ���� �� �� �켱������ ���� �׷��� ���ͷ�Ʈ�� �߻��ϸ� �����ϴ� �� ���߰� ���ο� ���ͷ�Ʈ ����)

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //������� ����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // PULL UP PULL DOWN���� ����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz �ӵ��� ����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //PULL UP PULL DOWN ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //����� LED �� ����
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);     //USART1_TX
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);    //USART1_RX

  //���ͷ�Ʈ enable �� Priority ����.
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  //������ �̸����� ���ͷ�Ʈ �����ؾ��Ѵ�
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
  USART_Init(USART1, &USART_InitStructure); 

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // USART1 Interrupt enable
  USART_Cmd(USART1, ENABLE);

  Serial_Send_String("Start Main()\n\r");    //���ڿ��� ù��° ������ �ּҸ� ���Ѵ�
  while(1)
  {
    if(rx1Flag)  // '\r' ���� �ԷµǸ�
      Serial_Event();
  }
}

void Serial_Event()
{
  int i=0;
  int num = 0;
  char * pToken;   //������ ���� ����
  char * pArray[ARR_CNT]={0};    //������ �ڷ��� ���� = ó���� null ����
  char recvBuf[CMD_SIZE]={0};       
  strcpy(recvBuf,rx1Data);    //���� �����͸� ����

  rx1Flag = 0; // �ٽ� Rflag �� 0���� ���´�.    
  Serial_Send_String(recvBuf);
  Serial_Send_String("\n\r");   //\n : �ٺ���, \r : �� ������ Ŀ�� ������ ��
  printf("rx : %s\r\n",recvBuf);
  //printf("test : %f\r\n",12.3);
  //printf("\n\r");
  //print_2d1(12.3);
     
  pToken = strtok(recvBuf,"[@]");  // [@]������ ���ڿ� �и�, pToken�� �ּҰ��� �ǹ��� "[", "@", "]"�� ������ '\0'���� ����ȴ�(������ ���ڿ��� return)

  while(pToken != NULL)
  {
    pArray[i] =  pToken;
    if(++i >= ARR_CNT)
      break;
    pToken = strtok(NULL,"[@]");
  }
       
  if(!strcmp(pArray[1],"LED"))  //strcmp(pArray[1], "LED"�� ������ 0�� ��ȯ�ϹǷ� null�� �ƴϱ� ���ؼ� !�� �ٿ��� �� �����Ѵ� -> pArray[1] == "LED"�� NULL(0)�� �ƴϸ�
  {
    if(pArray[3] != NULL)         
      num = atoi(pArray[3]);    //pArray[3]�� �ִ� ���ڸ� (a to i) ���ڷ� �ٲ㼭 num�� ���� 
    else
      num = 0;
    if(!strcmp(pArray[2],"ON"))
    {
     GPIO_SetBits(GPIOC, 0x01 << num);  //ON�� �� num ���ڿ� �´� LED�� �Ҵ�(SetBits)
    }
    else 
    {
      GPIO_ResetBits(GPIOC, 0x01 << num);  //OFF�� �� ����(ResetBits)
    }
  }  
}

void Serial_Send(unsigned char t)
{
  USART_SendData(USART1, t);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //USART���� FLAG_TXE�� �ִ°�
}

void Serial_Send_String(char* s)
{
  while( *s != '\0')    //null�� �ƴ�
  {
   Serial_Send((unsigned char)(*s));
   s++;   //s = s + 1;
  }
}

int putchar(int ch)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1,ch);
	return ch;
}

void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
	static int i=0;
	rx1Data[i] = USART_ReceiveData(USART1);
	if(rx1Data[i] == '\r')  //���� �����Ϳ� ���� \n�� ���� ��� 
	{
		rx1Data[i] = '\0';
		rx1Flag = 1;
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
	if(i == 0) Serial_Send(' ');   // �տ� ������ ����
	else       Serial_Send(i + '0');   //0�� �ƽ�Ű�ڵ� 0x30 �� ���Ѵ�

	j = j % 100;					// 10^0
	i = j / 10;
	Serial_Send(i + '0');
	Serial_Send('.');

	i = j % 10;					// 10^-1
	Serial_Send(i + '0');
}