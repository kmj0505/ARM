/******************************************************************************
  ��Ʈ ����:
    1)  ARM Cortex-M4 ����� ��ƮA�� 9~10������(PA9~PA10) 2�� ���̺��
        UART����� RXD, TXD �ɿ� �����Ѵ�.
******************************************************************************/
// stm32f4xx�� �� �������͵��� ������ �������
#include "stm32f4xx.h"
#include  "uart2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_SIZE 50
#define ARR_CNT 5   //����Ʈ �迭�� ����

  
void UART2_init();
void Serial2_Event();  //���� �Լ� ������ ����, \n������ �����͸� ����
void Serial2_Send(unsigned char t);    //���ڿ��� �����ϴ� �Լ�
void Serial2_Send_String(char* s); 
int putchar(int ch);     //printf�� ����ϱ� ���� �Լ�
void print_2d1(double number);    //���� 2�ڸ�, �Ҽ��� 1�ڸ��� ��Ÿ���ڴ�

extern volatile unsigned char rx2Flag;   //extern �Լ��� �ʱ�ȭ�� �� ���� (=0)
extern char rx2Data[50];


int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;    //GPIO �ʱⰪ �����ϱ� ���� ������ �����ϱ� ���� ����ü

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //������� ����
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     // PULL UP PULL DOWN���� ����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz �ӵ��� ����
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //PULL UP PULL DOWN ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  //����� LED �� ����
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  UART2_init();

  Serial2_Send_String("Start Main()\n\r");    //���ڿ��� ù��° ������ �ּҸ� ���Ѵ�
  while(1)
  {
    if(rx2Flag)  // '\r' ���� �ԷµǸ�
      Serial2_Event();
  }
}


void Serial2_Event()
{
  int i=0;
  int num = 0;
  char * pToken;   //������ ���� ����
  char * pArray[ARR_CNT]={0};    //������ �ڷ��� ���� = ó���� null ����
  char recvBuf[CMD_SIZE]={0};       
  strcpy(recvBuf,rx2Data);    //���� �����͸� ����

  rx2Flag = 0; // �ٽ� Rflag �� 0���� ���´�.    
  Serial2_Send_String(recvBuf);
  Serial2_Send_String("\n\r");   //\n : �ٺ���, \r : �� ������ Ŀ�� ������ ��
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

