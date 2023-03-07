#include "stm32f4xx.h"
#include "uart2.h"
#include <stdio.h>

//4-2
/*
// 7-���׸�Ʈ ��Ʈ�� �迭�� �����Ѵ�.
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

  // C��Ʈ�� 8 �� 11 ���� ��� ��0������ ��������ν� 7-���׸�Ʈ 4���� �� �Ҵ�.
  GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11); 

  while(1)
  {
    ps_switch = GPIO_ReadInputData(GPIOA)&0x00FF ;   //����ġ �Է��� ��Ʈ A���� �о� �´� 
    GPIO_Write(GPIOB, ps_switch<<8); // �о�� ����ġ �Է��� LED�� ����� �ش� 
    // ����ġ �Է��� ������ ���׸�Ʈ�� ��0000���� ǥ���� �ְ�
    // ����ġ ��1���� �������� ���׸�Ʈ�� ��1111���� ǥ�����ְ� 
    // ����ġ ��2���� �������� ���׸�Ʈ�� ��2222�� �̷������� ǥ���� �ش� 
    if(ps_switch == 0x00) GPIO_Write(GPIOC, Font[0]&0x00FF);   // ����ġ�� �ȴ��� 
    else if(ps_switch == 0x01) GPIO_Write(GPIOC, Font[1]&0x00FF); // ����ġ 1�� ����
    else if( ps_switch == 0x02 ) GPIO_Write(GPIOC, Font[2]&0x00FF); // ����ġ 2�� ����
    else if( ps_switch == 0x04 ) GPIO_Write(GPIOC, Font[3]&0x00FF);  // ����ġ 3�� ����
    else if( ps_switch == 0x08 ) GPIO_Write(GPIOC, Font[4]&0x00FF);  // ����ġ 4�� ����
    else if( ps_switch == 0x10 ) GPIO_Write(GPIOC, Font[5]&0x00FF);  //����ġ 5�� ����
    else if( ps_switch == 0x20 ) GPIO_Write(GPIOC, Font[6]&0x00FF);  // ����ġ 6�� ����
    else if( ps_switch == 0x40 ) GPIO_Write(GPIOC, Font[7]&0x00FF);  //����ġ 7�� ����
    else if( ps_switch == 0x80 ) GPIO_Write(GPIOC, Font[8]&0x00FF);  //����ġ 8�� ���� 
  }
}

*/

//4-3

/*
// 7-���׸�Ʈ ��Ʈ�� �迭�� �����Ѵ�.
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

  // C��Ʈ�� 8 �� 11 ���� ��� ��0������ ��������ν� 7-���׸�Ʈ 4���� �� �Ҵ�.
  GPIO_ResetBits(GPIOC,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11); 

  while(1)
  {
    R_sw = GPIO_ReadInputData(GPIOA) ;   //��Ÿ�� ����ġ �Է��� �о� �´�.
    R_sw = R_sw & 0x000f ; // A ��Ʈ�� 15~4 ��Ʈ�� Ȯ���� ��0������ ���ش�. 
    GPIO_Write(GPIOB, R_sw<<8); // �о�� ����ġ �Է��� LED�� ����� �ش�.

    // �о�� ��Ÿ�� ����ġ�� �ش�Ǵ� ����  7-���׸�Ʈ�� ����Ѵ�.
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
                                             GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; // C ��Ʈ ���� 8��Ʈ�� ������� �����Ѵ�.
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                                            // A ��Ʈ ���� 8��Ʈ�� �Է����� �����Ѵ�.
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  
  UART2_init();
  printf("Start main()");
  //printf("Dip : %d", );
  
  while(1)
  {
    GPIO_Write(GPIOC,GPIO_ReadInputData(GPIOB)&0x000);// Dip ����ġ �Է��� ��Ʈ E�� LED�� ���� ����Ѵ�.
  }
}
 */

//4-4 ���� > LED 1~8������ ��ư������ 16��Ʈ �� �ޱ�
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
                                             GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; // C ��Ʈ ���� 8��Ʈ�� ������� �����Ѵ�.
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                                             GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; // C ��Ʈ ���� 8��Ʈ�� ������� �����Ѵ�.
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                                            // A ��Ʈ ���� 8��Ʈ�� �Է����� �����Ѵ�.
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
      GPIO_Write(GPIOC,dipSw);// Dip ����ġ �Է��� ��Ʈ E�� LED�� ���� ����Ѵ�.
      dipSwOld = dipSw;
    }
  }
}

