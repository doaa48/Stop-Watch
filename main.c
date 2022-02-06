/*
  * main.c
 *
 *  Created on: Sep 28, 2021
 *      Author: dell
 */
#include"util/delay.h"
#include <stdio.h>
#include "STDTYPES.h"
#include "BIT_MATH.h"
//#include "../Files/CHECK_ERROR.h"
#include "DIO_REG.h"
#include "DIO_Interface.h"
#include "PORT_REG.h"
#include "PORT_Config.h"
#include "PORT_private.h"
#include "PORT_Interface.h"
#include "Keypad_Config.h"
#include "Keypad_Interface.h"
#include "Keypad_Private.h"
#include "Keypad_REG.h"
#include"LCD_Config.h"
#include"LCD_Interface.h"
/*stack implementations*/
#define MAX_SIZE 6
s8 top=-1;
void push(u8 Element);
void pop(void);
void Reset(void);
static u32 Global_u32Time[MAX_SIZE];
static u32 Global_u8diff=0;
static u32 Global_u32TotalTime=0;
static u8 Global_u8Operand=0;
u32 Global_u32Factor=3600;
static u32 Global_u8Display[8]={'0','0',':','0','0',':','0','0'};
u32 power(u32 a, u32 b);
u8 enter=0;
int main(void)
{

	 PORT_VoidInit();
	 LCD_VoidInit();
	 LCD_VoidSendString("Enter the Time :");
	 _delay_ms(2000);
	 LCD_VoidSendCommand(1);
	 LCD_VoidSendString("00:00:00");
	 u8 Local_u8Char_Pressed;

while(1)
{
		 do
		 {
			 Local_u8Char_Pressed=Keypad_u8GetPressedKey();

		 }while(Local_u8Char_Pressed==0xff);


		 /*if we pressed reset*/
		 if(Local_u8Char_Pressed=='c')
		 {
			 Reset();
		 }
		 else
		 {
			 /*Pushing data to stack */
		 push(Local_u8Char_Pressed-'0');
		 LCD_VoidSendCommand(1);
		 Global_u8diff=top+1;

		 /*Display the data Pressed in LCD*/
		 for(u8 i=0;i<=top;i++)
		 {
				 if(i==2)
			 {
				 LCD_VoidGoToPos(0,i);
				 LCD_VoidSendData(':');
				 Global_u8diff++;
			 }
				  if(i==4)
			 {
				 LCD_VoidGoToPos(0,5);
				 LCD_VoidSendData(':');
				 Global_u8diff++;
			 }

			 LCD_VoidSendData(Global_u32Time[i]+'0');

		 }
         /*Stay 100ms to be seen in LCD*/
          _delay_ms(100);

          /*to make comfortable Display Format to user*/
		for(u8 i=Global_u8diff;i<8;i++)
		 {
			 LCD_VoidSendData(Global_u8Display[i]);
		 }


		/*Calculating the time of StopWatch*/
		if(top==5)
		{
			LCD_VoidSendCommand(1);

			for(u8 k=0;k<=top;k++)
			{

				for(u32 l=power(10,1);l>=1;l/=10)
				{
					Global_u8Operand+=Global_u32Time[k]*l;
					 if(l==10)
					 {k++;}
				}

				Global_u32TotalTime+=Global_u32Factor*Global_u8Operand;
				Global_u8Operand=0;
				Global_u32Factor/=60;

			}

			for(u8 l=0;l<Global_u32TotalTime/5;l++)
			{
				_delay_ms(5000);
			}


				for(u8 k=0;k<5;k++)
				{
					DIO_U8SetPinVal(PORTD,PIN3,HIGH);
					LCD_VoidSendString("Done");
					_delay_ms(250);
					 LCD_VoidSendCommand(1);
					DIO_U8SetPinVal(PORTD,PIN3,LOW);
					_delay_ms(250);
				}


		}



	 }
}



return 0;

}








void Reset()
{
	top=-1;
	static u32 Global_u8diff=0;
	static u32 Global_u32TotalTime=0;
	static u8 Global_u8Operand=0;
	u32 Global_u32Factor=3600;
    LCD_VoidSendCommand(1);
}
u32 power(u32 a, u32 b)
{   if(b==0)
	return 1;
      for (u8 i=1; i<b; i++)
            a *=a;
      return a;
}

u8 isEmpty()
{
	return top < 0;
}

void push(u8 Element)
{
	if (top >= MAX_SIZE-1)
	{
		LCD_VoidSendString("Stack Full");
	}
	else
	{
		top++;
		Global_u32Time[top] = Element;
	}
}
void pop()
{
	if (isEmpty())
		LCD_VoidSendString("No Data deleted");
	else
		top--;
}
