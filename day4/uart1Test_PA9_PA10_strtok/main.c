/******************************************************************************
  포트 연결:
    1)  ARM Cortex-M4 모듈의 포트A의 9~10번핀을(PA9~PA10) 2핀 케이블로
        UART모듈의 RXD, TXD 핀에 연결한다.
******************************************************************************/
// stm32f4xx의 각 레지스터들을 정의한 헤더파일
#include "stm32f4xx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_SIZE 50
#define ARR_CNT 5   //포인트 배열의 개수


volatile unsigned char rx1Flag = 0;   
char rx1Data[50];    //rx1Data 에 수신되는 데이터 크기   
void Serial_Event();  //밑의 함수 원형을 정의, \n까지의 데이터를 저장
void Serial_Send(unsigned char t);    //문자열을 저장하는 함수
void Serial_Send_String(char* s); 
int putchar(int ch);     //printf를 사용하기 위한 함수
void print_2d1(double number);    //정수 2자리, 소수점 1자리로 나타내겠다

int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;    //GPIO 초기값 설정하기 위한 값들을 저장하기 위한 구조체
  USART_InitTypeDef USART_InitStructure;  
  NVIC_InitTypeDef   NVIC_InitStructure;    //중첩가능한 인터럽트 구조체 선언(인터럽트 실행 중 더 우선순위가 높은 그룹의 인터럽트가 발생하면 실행하던 걸 멈추고 새로운 인터럽트 실행)

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //출력으로 선언
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // PULL UP PULL DOWN으로 선언
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz 속도로 선언
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //PULL UP PULL DOWN 안함
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //사용할 LED 핀 설정
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

  //인터럽트 enable 및 Priority 설정.
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  //정해진 이름으로 인터럽트 선언해야한다
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
  USART_Init(USART1, &USART_InitStructure); 

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // USART1 Interrupt enable
  USART_Cmd(USART1, ENABLE);

  Serial_Send_String("Start Main()\n\r");    //문자열은 첫번째 문자의 주소를 말한다
  while(1)
  {
    if(rx1Flag)  // '\r' 까지 입력되면
      Serial_Event();
  }
}

void Serial_Event()
{
  int i=0;
  int num = 0;
  char * pToken;   //포인터 변수 선언
  char * pArray[ARR_CNT]={0};    //포인터 자료형 선언 = 처음엔 null 선언
  char recvBuf[CMD_SIZE]={0};       
  strcpy(recvBuf,rx1Data);    //들어온 데이터를 복사

  rx1Flag = 0; // 다시 Rflag 를 0으로 놓는다.    
  Serial_Send_String(recvBuf);
  Serial_Send_String("\n\r");   //\n : 줄변경, \r : 맨 앞으로 커서 보내는 것
  printf("rx : %s\r\n",recvBuf);
  //printf("test : %f\r\n",12.3);
  //printf("\n\r");
  //print_2d1(12.3);
     
  pToken = strtok(recvBuf,"[@]");  // [@]단위로 문자열 분리, pToken은 주소값을 의미함 "[", "@", "]"이 나오면 '\0'으로 변경된다(나머지 문자열은 return)

  while(pToken != NULL)
  {
    pArray[i] =  pToken;
    if(++i >= ARR_CNT)
      break;
    pToken = strtok(NULL,"[@]");
  }
       
  if(!strcmp(pArray[1],"LED"))  //strcmp(pArray[1], "LED"가 같으면 0을 반환하므로 null이 아니기 위해서 !를 붙여서 논리 부정한다 -> pArray[1] == "LED"가 NULL(0)이 아니면
  {
    if(pArray[3] != NULL)         
      num = atoi(pArray[3]);    //pArray[3]에 있는 문자를 (a to i) 숫자로 바꿔서 num에 저장 
    else
      num = 0;
    if(!strcmp(pArray[2],"ON"))
    {
     GPIO_SetBits(GPIOC, 0x01 << num);  //ON일 때 num 숫자에 맞는 LED를 켠다(SetBits)
    }
    else 
    {
      GPIO_ResetBits(GPIOC, 0x01 << num);  //OFF일 때 끈다(ResetBits)
    }
  }  
}

void Serial_Send(unsigned char t)
{
  USART_SendData(USART1, t);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); //USART번에 FLAG_TXE가 있는가
}

void Serial_Send_String(char* s)
{
  while( *s != '\0')    //null이 아님
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
	if(rx1Data[i] == '\r')  //들어온 데이터에 따라서 \n이 있을 경우 
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

	j = (int)(number*10. + 0.5);       //10을 곱해서 0.5를 더하고 int형으로 바꾸면 반올림된다(0.5를 쓰면 반올림 될 숫자는 반올림된다) 
	i = j / 100;					// 10^1
	if(i == 0) Serial_Send(' ');   // 앞에 공백을 붙임
	else       Serial_Send(i + '0');   //0의 아스키코드 0x30 을 더한다

	j = j % 100;					// 10^0
	i = j / 10;
	Serial_Send(i + '0');
	Serial_Send('.');

	i = j % 10;					// 10^-1
	Serial_Send(i + '0');
}