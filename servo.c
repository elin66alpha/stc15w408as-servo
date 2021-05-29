#include <STC15F2K60S2.H>
#include "intrins.h"

sbit servo = P3^7;//舵机的io口

unsigned char signal;//信号参数
unsigned char input;//输入参数
void Timer0Init(void) //100微秒@12.000MHz
{
AUXR |= 0x80; //定时器时钟1T模式
TMOD &= 0xF0; //设置定时器模式
TMOD |= 0x01; //设置定时器模式
TL0 = 0x50; //设置定时初值
TH0 = 0xFB; //设置定时初值
TF0 = 0; //清除TF0标志
TR0 = 1; //定时器0开始计时
EA=1;//cpu开放总中断
ET0=1;//开启定时器0中断
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
TR0=0;//定时器0运行控制
TL0 = 0x50; //再一次设置定时初值
TH0 = 0xFB; //再一次设置定时初值
signal++;
if(signal>1999) signal=0;
//给信号参数设置阈值，阈值取决于你的输入和延时分成了多少份
if(signal<input) servo=1;//信号小于输入，高电平
else servo=0;//反之,低电平
TR0=1;//定时器0运行控制
}

void main()
{
  int i=0,j=0;
   Timer0Init();
   //在这里可以对输入进行获取和处理，这一步尤为关键，关系到舵机旋转的角度。可以使用ad转换获取输入的数字。这里我先以一个左右反复的程序实例
   while(1)
   {
      for(i=50;i<250;i++) input=i;
      Delay(1);
      for(j=250;j>50;j--) input=j;
   }
}