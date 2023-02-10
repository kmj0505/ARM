#include "stm32f4xx.h"

static void Delay(const uint32_t Count)    //static 함수를 사용해서 파일 내에서 참조하게끔 범위 제한, const 사용으로 uint32_t변수를 상수화 시킴 
{
__IO uint32_t index = 0;      //uint32_t = unsigned int형
for(index = (16800 * Count); index != 0; index--);
}

int main()
{
GPIO_InitTypeDef GPIO_InitStructure;      //GPIO를 사용하기 위해 GPIO_InitStructure 구조체 선언
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //GPIO의 모드를 입력 또는 출력으로 사용할지
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //Output type -> PP(push-pull)
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //GPIO의 반응속도
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // NOPULL로 설정 -> 풀업, 풀다운을 사용하지 않음.

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
GPIO_Init(GPIOC, &GPIO_InitStructure);
while(1)
{
  GPIO_SetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
               GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);        //GPIO_Pin0 ~ 7번까지 1로 set
  
  Delay(500);      //Delay는 안쓰는게 좋음(단시간에 빠르게 처리하려고 하는데 Delay 사용 시 지연)
  GPIO_ResetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                 GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);      //GPIO_Pin0 ~ 7번까지 0으로 reset
  Delay(500);
}
}
