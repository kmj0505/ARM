#include "stm32f4xx.h"

static void Delay(const uint32_t Count)    //static �Լ��� ����ؼ� ���� ������ �����ϰԲ� ���� ����, const ������� uint32_t������ ���ȭ ��Ŵ 
{
__IO uint32_t index = 0;      //uint32_t = unsigned int��
for(index = (16800 * Count); index != 0; index--);
}

int main()
{
GPIO_InitTypeDef GPIO_InitStructure;      //GPIO�� ����ϱ� ���� GPIO_InitStructure ����ü ����
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //GPIO�� ��带 �Է� �Ǵ� ������� �������
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //Output type -> PP(push-pull)
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //GPIO�� �����ӵ�
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   // NOPULL�� ���� -> Ǯ��, Ǯ�ٿ��� ������� ����.

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
GPIO_Init(GPIOC, &GPIO_InitStructure);
while(1)
{
  GPIO_SetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
               GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);        //GPIO_Pin0 ~ 7������ 1�� set
  
  Delay(500);      //Delay�� �Ⱦ��°� ����(�ܽð��� ������ ó���Ϸ��� �ϴµ� Delay ��� �� ����)
  GPIO_ResetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
                 GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);      //GPIO_Pin0 ~ 7������ 0���� reset
  Delay(500);
}
}
