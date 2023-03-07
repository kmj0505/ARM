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

 왼쪽에서 첫 번째 7-세그면트 구동 시 :  PG0 비트를 ‘0’ 으로 해준다.
   왼쪽에서 두 번째 7-세그면트 구동 시 :  PG1 비트를 ‘0’ 으로 해준다.
   왼쪽에서 세 번째 7-세그면트 구동 시 :  PG2 비트를 ‘0’ 으로 해준다.
   왼쪽에서 네 번째 7-세그면트 구동 시 :  PG3 비트를 ‘0’ 으로 해준다.

  GPIO_Write(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);   // 왼쪽에서 첫 번째  7-세그먼트만  구동한다.

  while(1)
  {
    GPIO_Write(GPIOC, GPIO_Pin_0);
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, GPIO_Pin_1);
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, GPIO_Pin_2);
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, GPIO_Pin_3);
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, GPIO_Pin_4);
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, GPIO_Pin_5);
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, GPIO_Pin_6);
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, GPIO_Pin_7);
    Delay(500); // 0.5초 딜레이
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

// 7-세그먼트 폰트를 배열로 지정한다.
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

  // 7-세그먼트 4개를 모두 켠다.
  GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);

  while(1)
  {
    GPIO_Write(GPIOC, Font[10]); // 7-세그먼트에 ‘0000’을 출력한다 / 10일 경우 'aaaa'출력
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, Font[11]); // 7-세그먼트에 ‘1111’을 출력한다 / 11일 경우 'bbbb'출력
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, Font[12]); // 7-세그먼트에 ‘2222’을 출력한다 / 12일 경우 'cccc'출력
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, Font[13]); // 7-세그먼트에 ‘3333’을 출력한다 / 13일 경우 'dddd'출력
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, Font[14]); // 7-세그먼트에 ‘4444’을 출력한다 / 14일 경우 'eeee'출력
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, Font[15]); // 7-세그먼트에 ‘5555’을 출력한다 / 15일 경우 'ffff'출력
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, Font[16]); // 7-세그먼트에 ‘6666’을 출력한다 / 16일 경우 '____'출력
    Delay(500); // 0.5초 딜레이 

    GPIO_Write(GPIOC, Font[17]); // 7-세그먼트에 ‘7777’을 출력한다 / 17일 경우 '....'출력
    Delay(500); // 0.5초 딜레이

    GPIO_Write(GPIOC, Font[8]); // 7-세그먼트에 ‘8888’을 출력한다 
    Delay(500); // 0.5초 딜레이

    GPIO_Write(GPIOC, Font[9]); // 7-세그먼트에 ‘9999’을 출력한다 
    Delay(500); // 0.5초 딜레이
  }
}

*/


//3-6
/*
#include "stm32f4xx.h"

// delay 함수
static void Delay(const uint32_t Count)
{
  __IO uint32_t index = 0; 
  for(index = (16800 * Count); index != 0; index--);
}

// 7-세그먼트 폰트를 배열로 지정한다.
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
    GPIO_Write(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3); // 왼쪽에서 첫 번째 7-세그먼트 ON
    GPIO_Write(GPIOC, Font[1]);                                         // '1'을 출력한다 
    Delay(100);                                                                     // 사람 눈에 잔상을 남게 하기 위하여 약간의 Delay를 준다

    GPIO_Write(GPIOA,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3); // 왼쪽에서 두 번째 7-세그먼트 ON
    GPIO_Write(GPIOC, Font[2]);                                         // '2'을 출력한다 
    Delay(100);                                                                     // 사람 눈에 잔상을 남게 하기 위하여 약간의 Delay를 준다

    GPIO_Write(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3); // 왼쪽에서 세 번째 7-세그먼트 ON
    GPIO_Write(GPIOC, Font[3]);                                         // '3'을 출력한다 
    Delay(100);                                                                     // 사람 눈에 잔상을 남게 하기 위하여 약간의 Delay를 준다

    GPIO_Write(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2); // 왼쪽에서 네 번째 7-세그먼트 ON
    GPIO_Write(GPIOC, Font[4]);                                         // '4'을 출력한다 
    Delay(100);                                                                     // 사람 눈에 잔상을 남게 하기 위하여 약간의 Delay를 준다
  }
}
*/

//3-7


extern volatile unsigned char rx2Flag;  //(extern) = 이 변수가 다른 외부에 정의되어있다고 알려줌 (=0으로 초기화 불가)
extern char rx2Data[50];



// delay 함수
static void Delay(const uint32_t Count) //다른 파일에서도 사용해야하므로 static으로 하면 안된다
{
  __IO uint32_t index = 0; 
  for(index = (16800 * Count); index != 0; index--);
}


  /*
  for( i = 0 ; i < 30; i++ )
  {
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
    
     // GPIO_Write(GPIOC,GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);  // 왼쪽 첫 번째 세그먼트 ON
     //GPIO_Write(GPIOC, Font[N1000]|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);  // 천의 자리 숫자를 출력해 준다 --> 이 것만 써도 결과(숫자)가 나타남
      Delay(1);            
     
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
      
      //GPIO_Write(GPIOC,GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11); // 왼쪽 두 번째 세그먼트 ON
      //GPIO_Write(GPIOC, Font[N100]|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11);  // 백의 자리 숫자를 출력해 준다 --> 이 것만 써도 결과(숫자)가 나타남    
      Delay(1);  
       
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
      
      //GPIO_Write(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11); // 왼쪽 세 번째 세그먼트 ON
      //GPIO_Write(GPIOC, Font[N10]|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11);  // 십의 자리 숫자를 출력해 준다 --> 이 것만 써도 결과(숫자)가 나타남
      Delay(1);
  
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xf0ff)|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
    GPIO_Write(GPIOC,(GPIO_ReadInputData(GPIOC)&0xff00)|Font[N1000]);
      
      //GPIO_Write(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10); // 왼쪽 네 번째 세그먼트 ON
      //GPIO_Write(GPIOC, Font[N1]|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);  // 일의 자리 숫자를 출력해 준다 --> 이 것만 써도 결과(숫자)가 나타남
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


