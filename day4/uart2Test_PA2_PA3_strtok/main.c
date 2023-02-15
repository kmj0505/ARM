/******************************************************************************
  포트 연결:
    1)  ARM Cortex-M4 모듈의 포트A의 9~10번핀을(PA9~PA10) 2핀 케이블로
        UART모듈의 RXD, TXD 핀에 연결한다.
******************************************************************************/
// stm32f4xx의 각 레지스터들을 정의한 헤더파일
#include "stm32f4xx.h"
#include  "uart2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_SIZE 50
#define ARR_CNT 5   //포인트 배열의 개수

  
void UART2_init();
void Serial2_Event();  //밑의 함수 원형을 정의, \n까지의 데이터를 저장
void Serial2_Send(unsigned char t);    //문자열을 저장하는 함수
void Serial2_Send_String(char* s); 
int putchar(int ch);     //printf를 사용하기 위한 함수
void print_2d1(double number);    //정수 2자리, 소수점 1자리로 나타내겠다

extern volatile unsigned char rx2Flag;   //extern 함수는 초기화할 수 없다 (=0)
extern char rx2Data[50];


int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;    //GPIO 초기값 설정하기 위한 값들을 저장하기 위한 구조체

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //출력으로 선언
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // PULL UP PULL DOWN으로 선언
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz 속도로 선언
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //PULL UP PULL DOWN 안함
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //사용할 LED 핀 설정
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  UART2_init();

  Serial2_Send_String("Start Main()\n\r");    //문자열은 첫번째 문자의 주소를 말한다
  while(1)
  {
    if(rx2Flag)  // '\r' 까지 입력되면
      Serial2_Event();
  }
}


void Serial2_Event()
{
  int i=0;
  int num = 0;
  char * pToken;   //포인터 변수 선언
  char * pArray[ARR_CNT]={0};    //포인터 자료형 선언 = 처음엔 null 선언
  char recvBuf[CMD_SIZE]={0};       
  strcpy(recvBuf,rx2Data);    //들어온 데이터를 복사

  rx2Flag = 0; // 다시 Rflag 를 0으로 놓는다.    
  Serial2_Send_String(recvBuf);
  Serial2_Send_String("\n\r");   //\n : 줄변경, \r : 맨 앞으로 커서 보내는 것
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

