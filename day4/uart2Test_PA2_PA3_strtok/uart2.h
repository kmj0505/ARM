
#ifndef __UART2_H__    //코드의 헤더파일 중복을 막기 위해서
#define __UART2_H__    //코드의 헤더파일 중복을 막기 위해서

void UART2_init();
void Serial2_Event();  //밑의 함수 원형을 정의, \n까지의 데이터를 저장
void Serial2_Send(unsigned char t);    //문자열을 저장하는 함수
void Serial2_Send_String(char* s); 
int putchar(int ch);     //printf를 사용하기 위한 함수
void print_2d1(double number);    //정수 2자리, 소수점 1자리로 나타내겠다
#endif