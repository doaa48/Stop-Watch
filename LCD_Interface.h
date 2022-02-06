/*
 * LCD_Interface.h
 *
 *  Created on: Sep 24, 2021
 *      Author: dell
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_



#define LINE1  0
#define LINE2  1


#define BIT_8 0
#define BIT_4 1

/*if we select send command*/
void LCD_VoidSendCommand(u8 Copy_u8Command);
/* if we select send data*/
void LCD_VoidSendData(u8 Copy_u8Data);
/*to initialize the LCD*/
void LCD_VoidInit(void);
/*char to integer*/
void LCD_VoidSendNumber(u32 Copy_u8Char);

/*to Display Full String */
void LCD_VoidSendString( const u8* Copy_PtString);

/*to go to finite position in LCD DDRAM*/
void LCD_VoidGoToPos(u8 Copy_u8XPos,u8 Copy_u8YPos);


/*to make special char in LCD using GCRAM*/

void LCD_VoidCreateSpecialChar(const u8 *Copy_PcDataPattern,u8 Copy_u8BlockNo,u8 Copy_u8XPos,u8 Copy_u8YPos);

#endif /* LCD_INTERFACE_H_ */
