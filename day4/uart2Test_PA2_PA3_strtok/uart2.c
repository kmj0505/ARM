#include "stm32f4xx.h"

volatile unsigned char rx2Flag = 0;   
char rx2Data[50];

void UART2_init(){
  GPIO_InitTypeDef   GPIO_InitStructure;    //GPIO 초기값 설정하기 위한 값들을 저장하기 위한 구조체
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

  //인터럽트 enable 및 Priority 설정.
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;  //정해진 이름으로 인터럽트 선언해야한다
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);    // NVIC 초기화 > 설정했던 값들 NVIC에 저장

  USART_InitStructure.USART_BaudRate = 115200;    //통신 속도 BPS
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //하나의 프레임 5~9bits 사이, 보통은 8비트 보냄
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;    //사용할 수도 있고 안할 수도 있음 (Stop Bits 앞에 있음), 짝수 홀수로 구분, 짝수 = 1의 개수 짝수, 홀수 = 1의 개수 홀수로 변경하기, 기본적인 오류체크 방식 
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 흐름제어, pc와 모뎀의 흐름제어하는 것
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //한 방향으로만 전송 또는 수신하겠다(여기서는 전이중 통신으로 둘 다 쓰겠다) 
  USART_Init(USART2, &USART_InitStructure); 

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // USART1 Interrupt enable
  USART_Cmd(USART2, ENABLE);
}

void Serial2_Send(unsigned char t)
{
  USART_SendData(USART2, t);
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); //USART번에 FLAG_TXE가 있는가
}

void Serial2_Send_String(char* s)
{
  while( *s != '\0')    //null이 아님
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
	if(rx2Data[i] == '\r')  //들어온 데이터에 따라서 \n이 있을 경우 
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

	j = (int)(number*10. + 0.5);       //10을 곱해서 0.5를 더하고 int형으로 바꾸면 반올림된다(0.5를 쓰면 반올림 될 숫자는 반올림된다) 
	i = j / 100;					// 10^1
	if(i == 0) Serial2_Send(' ');   // 앞에 공백을 붙임
	else       Serial2_Send(i + '0');   //0의 아스키코드 0x30 을 더한다

	j = j % 100;					// 10^0
	i = j / 10;
	Serial2_Send(i + '0');
	Serial2_Send('.');

	i = j % 10;					// 10^-1
	Serial2_Send(i + '0');
}