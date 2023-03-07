#include "stm32f4xx.h"
#include "uart2.h"
#include <stdio.h>

//4-2
/*
// 7-세그먼트 폰트를 배열로 지정한다.
unsigned char Font[18] = {0x3F, 0X06, 0X5B, 0X4F, 
                                         0X66, 0X6D, 0X7C, 0X07,
                                         0X7F, 0X67, 0X77, 0X7C, 
                                         0X39, 0X5E, 0X79, 0X71, 
                                         0X08, 0X80};



int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  int ps_switch;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                                             GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
                                             GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
  GPIO_Init(GPIOC, &GPIO_InitStructure);


  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // C포트의 8 ∼ 11 핀을 모두 ‘0’으로 출력함으로써 7-세그먼트 4개를 다 켠다.
  GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11); 

  while(1)
  {
    ps_switch = GPIO_ReadInputData(GPIOA)&0x00FF ;   //스위치 입력을 포트 A에서 읽어 온다 
    GPIO_Write(GPIOB, ps_switch<<8); // 읽어온 스위치 입력을 LED로 출력해 준다 
    // 스위치 입력이 없으면 세그먼트에 ‘0000’을 표시해 주고
    // 스위치 ‘1’이 눌렸으면 세그먼트에 ‘1111’을 표시해주고 
    // 스위치 ‘2’가 눌렸으면 세그먼트에 ‘2222’ 이런식으로 표시해 준다 
    if(ps_switch == 0x00) GPIO_Write(GPIOC, Font[0]&0x00FF);   // 스위치가 안눌림 
    else if(ps_switch == 0x01) GPIO_Write(GPIOC, Font[1]&0x00FF); // 스위치 1이 눌림
    else if( ps_switch == 0x02 ) GPIO_Write(GPIOC, Font[2]&0x00FF); // 스위치 2가 눌림
    else if( ps_switch == 0x04 ) GPIO_Write(GPIOC, Font[3]&0x00FF);  // 스위치 3이 눌림
    else if( ps_switch == 0x08 ) GPIO_Write(GPIOC, Font[4]&0x00FF);  // 스위치 4가 눌림
    else if( ps_switch == 0x10 ) GPIO_Write(GPIOC, Font[5]&0x00FF);  //스위치 5가 눌림
    else if( ps_switch == 0x20 ) GPIO_Write(GPIOC, Font[6]&0x00FF);  // 스위치 6이 눌림
    else if( ps_switch == 0x40 ) GPIO_Write(GPIOC, Font[7]&0x00FF);  //스위치 7이 눌림
    else if( ps_switch == 0x80 ) GPIO_Write(GPIOC, Font[8]&0x00FF);  //스위치 8이 눌림 
  }
}

*/

//4-3

/*
// 7-세그먼트 폰트를 배열로 지정한다.
unsigned char Font[18] = {0x3F, 0X06, 0X5B, 0X4F, 
                                         0X66, 0X6D, 0X7C, 0X07,
                                         0X7F, 0X67, 0X77, 0X7C, 
                                         0X39, 0X5E, 0X79, 0X71, 
                                         0X08, 0X80};



int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  int R_sw;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                                             GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
                                             GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
  GPIO_Init(GPIOC, &GPIO_InitStructure);


  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // C포트의 8 ∼ 11 핀을 모두 ‘0’으로 출력함으로써 7-세그먼트 4개를 다 켠다.
  GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11); 

  while(1)
  {
    R_sw = GPIO_ReadInputData(GPIOA) ;   //로타리 스위치 입력을 읽어 온다.
    R_sw = R_sw & 0x000f ; // A 포트의 15~4 비트를 확실히 ‘0’으로 해준다. 
    GPIO_Write(GPIOB, R_sw<<8); // 읽어온 스위치 입력을 LED로 출력해 준다.

    // 읽어온 로타리 스위치에 해당되는 값을  7-세그먼트에 출력한다.
    GPIO_Write(GPIOC, Font[R_sw]&0x00FF); 
  }
}
*/


//4-4

/*
int main()
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8 |GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                                             GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; // C 포트 하위 8비트를 출력으로 선언한다.
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                                            // A 포트 하위 8비트를 입력으로 선언한다.
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  
  UART2_init();
  printf("Start main()");
  //printf("Dip : %d", );
  
  while(1)
  {
    GPIO_Write(GPIOC,GPIO_ReadInputData(GPIOB)&0x000);// Dip 스위치 입력을 포트 E의 LED로 직접 출력한다.
  }
}
 */

//4-4 응용 > LED 1~8번까지 버튼눌러서 16비트 값 받기
int main()
{
  unsigned short dipSw=0,dipSwOld=0;
  GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; // C 포트 하위 8비트를 출력으로 선언한다.
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                                             GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; // C 포트 하위 8비트를 출력으로 선언한다.
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                                            // A 포트 하위 8비트를 입력으로 선언한다.
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  UART2_init();
  printf("Start main()\n\r");
  
  while(1)
  {
    dipSw = GPIO_ReadInputData(GPIOB)&0xFF00;
    dipSw >>= 8;
    if(dipSw != dipSwOld)
    {
      printf("Dip : %d %#04x\r\n",dipSw, dipSw);
      GPIO_Write(GPIOC,dipSw);// Dip 스위치 입력을 포트 E의 LED로 직접 출력한다.
      dipSwOld = dipSw;
    }
  }
}

