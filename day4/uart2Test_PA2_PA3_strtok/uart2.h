
#ifndef __UART2_H__    //�ڵ��� ������� �ߺ��� ���� ���ؼ�
#define __UART2_H__    //�ڵ��� ������� �ߺ��� ���� ���ؼ�

void UART2_init();
void Serial2_Event();  //���� �Լ� ������ ����, \n������ �����͸� ����
void Serial2_Send(unsigned char t);    //���ڿ��� �����ϴ� �Լ�
void Serial2_Send_String(char* s); 
int putchar(int ch);     //printf�� ����ϱ� ���� �Լ�
void print_2d1(double number);    //���� 2�ڸ�, �Ҽ��� 1�ڸ��� ��Ÿ���ڴ�
#endif