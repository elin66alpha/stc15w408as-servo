#include <STC15F2K60S2.H>
#include "intrins.h"

sbit servo = P3^7;//�����io��

unsigned char signal;//�źŲ���
unsigned char input;//�������
void Timer0Init(void) //100΢��@12.000MHz
{
AUXR |= 0x80; //��ʱ��ʱ��1Tģʽ
TMOD &= 0xF0; //���ö�ʱ��ģʽ
TMOD |= 0x01; //���ö�ʱ��ģʽ
TL0 = 0x50; //���ö�ʱ��ֵ
TH0 = 0xFB; //���ö�ʱ��ֵ
TF0 = 0; //���TF0��־
TR0 = 1; //��ʱ��0��ʼ��ʱ
EA=1;//cpu�������ж�
ET0=1;//������ʱ��0�ж�
}

void Delay(unsigned int time) //@12.000MHz
{ while(time--)
   { unsigned char i, j;
      i = 12;
      j = 169; 
      do 
         { while (--j); } while (--i);
   }
}

void servo_function() interrupt 1
{
TR0=0;//��ʱ��0���п���
TL0 = 0x50; //��һ�����ö�ʱ��ֵ
TH0 = 0xFB; //��һ�����ö�ʱ��ֵ
signal++;
if(signal>1999) signal=0;
//���źŲ���������ֵ����ֵȡ��������������ʱ�ֳ��˶��ٷ�
if(signal<input) servo=1;//�ź�С�����룬�ߵ�ƽ
else servo=0;//��֮,�͵�ƽ
TR0=1;//��ʱ��0���п���
}

void main()
{
  int i=0,j=0;
   Timer0Init();
   //��������Զ�������л�ȡ�ʹ�����һ����Ϊ�ؼ�����ϵ�������ת�ĽǶȡ�����ʹ��adת����ȡ��������֡�����������һ�����ҷ����ĳ���ʵ��
   while(1)
   {
      for(i=50;i<250;i++) input=i;
      Delay(1);
      for(j=250;j>50;j--) input=j;
   }
}