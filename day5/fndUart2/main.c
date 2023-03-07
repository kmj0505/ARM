#include "stm32f4xx.h"
#include "uart2.h"
#include <stdio.h>
#include "fnd.h"
#include <stdlib.h>

  //UART2_init();
  //printf("Start main()\n\r");
  //printf("float : %f\n\r", 3.14);

//3-4
/*
static void Delay(const uint32_t Count)
{
  __IO uint32_t index = 0; 
  for(index = (16800 * Count); index != 0; index--);
}


int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

 ���ʿ��� ù ��° 7-���׸�Ʈ ���� �� :  PG0 ��Ʈ�� ��0�� ���� ���ش�.
   ���ʿ��� �� ��° 7-���׸�Ʈ ���� �� :  PG1 ��Ʈ�� ��0�� ���� ���ش�.
   ���ʿ��� �� ��° 7-���׸�Ʈ ���� �� :  PG2 ��Ʈ�� ��0�� ���� ���ش�.
   ���ʿ��� �� ��° 7-���׸�Ʈ ���� �� :  PG3 ��Ʈ�� ��0�� ���� ���ش�.

  GPIO_Write(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);   // ���ʿ��� ù ��°  7-���׸�Ʈ��  �����Ѵ�.

  while(1)
  {
    GPIO_Write(GPIOC, GPIO_Pin_0);
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, GPIO_Pin_1);
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, GPIO_Pin_2);
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, GPIO_Pin_3);
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, GPIO_Pin_4);
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, GPIO_Pin_5);
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, GPIO_Pin_6);
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, GPIO_Pin_7);
    Delay(500); // 0.5�� ������
  }
}
*/

//3-5
/*
static void Delay(const uint32_t Count)
{
  __IO uint32_t index = 0; 
  for(index = (16800 * Count); index != 0; index--);
}

// 7-���׸�Ʈ ��Ʈ�� �迭�� �����Ѵ�.
unsigned char Font[18] = {0x3F, 0X06, 0X5B, 0X4F, 
                                         0X66, 0X6D, 0X7C, 0X07,
                                         0X7F, 0X67, 0X77, 0X7C, 
                                         0X39, 0X5E, 0X79, 0X71, 
                                         0X08, 0X80};


int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // 7-���׸�Ʈ 4���� ��� �Ҵ�.
  GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);

  while(1)
  {
    GPIO_Write(GPIOC, Font[10]); // 7-���׸�Ʈ�� ��0000���� ����Ѵ� / 10�� ��� 'aaaa'���
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, Font[11]); // 7-���׸�Ʈ�� ��1111���� ����Ѵ� / 11�� ��� 'bbbb'���
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, Font[12]); // 7-���׸�Ʈ�� ��2222���� ����Ѵ� / 12�� ��� 'cccc'���
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, Font[13]); // 7-���׸�Ʈ�� ��3333���� ����Ѵ� / 13�� ��� 'dddd'���
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, Font[14]); // 7-���׸�Ʈ�� ��4444���� ����Ѵ� / 14�� ��� 'eeee'���
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, Font[15]); // 7-���׸�Ʈ�� ��5555���� ����Ѵ� / 15�� ��� 'ffff'���
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, Font[16]); // 7-���׸�Ʈ�� ��6666���� ����Ѵ� / 16�� ��� '____'���
    Delay(500); // 0.5�� ������ 

    GPIO_Write(GPIOC, Font[17]); // 7-���׸�Ʈ�� ��7777���� ����Ѵ� / 17�� ��� '....'���
    Delay(500); // 0.5�� ������

    GPIO_Write(GPIOC, Font[8]); // 7-���׸�Ʈ�� ��8888���� ����Ѵ� 
    Delay(500); // 0.5�� ������

    GPIO_Write(GPIOC, Font[9]); // 7-���׸�Ʈ�� ��9999���� ����Ѵ� 
    Delay(500); // 0.5�� ������
  }
}

*/


//3-6
/*
#include "stm32f4xx.h"

// delay �Լ�
static void Delay(const uint32_t Count)
{
  __IO uint32_t index = 0; 
  for(index = (16800 * Count); index != 0; index--);
}

// 7-���׸�Ʈ ��Ʈ�� �迭�� �����Ѵ�.
unsigned char Font[18] = {0x3F, 0X06, 0X5B, 0X4F, 
                                         0X66, 0X6D, 0X7C, 0X07,
                                         0X7F, 0X67, 0X77, 0X7C, 
                                         0X39, 0X5E, 0X79, 0X71, 
                                         0X08, 0X80};


int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  while(1)
  {
    GPIO_Write(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3); // ���ʿ��� ù ��° 7-���׸�Ʈ ON
    GPIO_Write(GPIOC, Font[1]);                                         // '1'�� ����Ѵ� 
    Delay(100);                                                                     // ��� ���� �ܻ��� ���� �ϱ� ���Ͽ� �ణ�� Delay�� �ش�

    GPIO_Write(GPIOA,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3); // ���ʿ��� �� ��° 7-���׸�Ʈ ON
    GPIO_Write(GPIOC, Font[2]);                                         // '2'�� ����Ѵ� 
    Delay(100);                                                                     // ��� ���� �ܻ��� ���� �ϱ� ���Ͽ� �ణ�� Delay�� �ش�

    GPIO_Write(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3); // ���ʿ��� �� ��° 7-���׸�Ʈ ON
    GPIO_Write(GPIOC, Font[3]);                                         // '3'�� ����Ѵ� 
    Delay(100);                                                                     // ��� ���� �ܻ��� ���� �ϱ� ���Ͽ� �ణ�� Delay�� �ش�

    GPIO_Write(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2); // ���ʿ��� �� ��° 7-���׸�Ʈ ON
    GPIO_Write(GPIOC, Font[4]);                                         // '4'�� ����Ѵ� 
    Delay(100);                                                                     // ��� ���� �ܻ��� ���� �ϱ� ���Ͽ� �ణ�� Delay�� �ش�
  }
}
*/

//3-7


extern volatile unsigned char rx2Flag;  //(extern) = �� ������ �ٸ� �ܺο� ���ǵǾ��ִٰ� �˷��� (=0���� �ʱ�ȭ �Ұ�)
extern char rx2Data[50];



// delay �Լ�
static void Delay(const uint32_t Count) //�ٸ� ���Ͽ����� ����ؾ��ϹǷ� static���� �ϸ� �ȵȴ�
{
  __IO uint32_t index = 0; 
  for(index = (16800 * Count); index != 0; index--);
}


  /*
  for( i = 0 ; i < 30; i++ )
  {
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
    
     // GPIO_Write(GPIOC,GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);  // ���� ù ��° ���׸�Ʈ ON
     //GPIO_Write(GPIOC, Font[N1000]|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);  // õ�� �ڸ� ���ڸ� ����� �ش� --> �� �͸� �ᵵ ���(����)�� ��Ÿ��
      Delay(1);            
     
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
      
      //GPIO_Write(GPIOC,GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11); // ���� �� ��° ���׸�Ʈ ON
      //GPIO_Write(GPIOC, Font[N100]|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11);  // ���� �ڸ� ���ڸ� ����� �ش� --> �� �͸� �ᵵ ���(����)�� ��Ÿ��    
      Delay(1);  
       
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
      
      //GPIO_Write(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11); // ���� �� ��° ���׸�Ʈ ON
      //GPIO_Write(GPIOC, Font[N10]|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11);  // ���� �ڸ� ���ڸ� ����� �ش� --> �� �͸� �ᵵ ���(����)�� ��Ÿ��
      Delay(1);
  
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
      
      //GPIO_Write(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10); // ���� �� ��° ���׸�Ʈ ON
      //GPIO_Write(GPIOC, Font[N1]|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);  // ���� �ڸ� ���ڸ� ����� �ش� --> �� �͸� �ᵵ ���(����)�� ��Ÿ��
      Delay(1);     
  }
*/


int main()
{
  

  int count = 0;
  
  FND_init();
  UART2_init();
  printf("Start main()\n\r");
  
  while(1)
  {
    if(rx2Flag)
    {
      printf("%s\r\n", rx2Data);
      count = atoi(rx2Data);
      rx2Flag=0;
    }
     
    display_fnd(count);
    count--;
    if(count == 1000)
      count = 0;
    else if(count == -1000)
      count = 0;

  }
}


