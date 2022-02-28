/*
 * LCD_interface.h
 *
 *  Created on: Feb 25, 2022
 *      Author: noureldeen albrmky
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

void HLCD_voidInit(void);

/************************************************************************
 send command to LCD
 ************************************************************************/
void HLCD_voidSendCommand(u8 copy_u8Command);

/************************************************************************
 send Data to LCD
 ************************************************************************/
void HLCD_voidSendData(u8 copy_u8Char);

/************************************************************************
 display String
 ************************************************************************/
void HLCD_voidDisplayString(char *copy_pu8String);

/************************************************************************
 display number
 ************************************************************************/
void HLCD_voidDisplayNumber(s32 copy_s32Number);

/************************************************************************
 send clear screen command
 ************************************************************************/
void HLCD_voidClearDisplay(void);

/************************************************************************
 specify the address for the position at DDRAM
 ************************************************************************/
void HLCD_voidGoToPos(u8 copy_u8RowNum, u8 copy_u8ColNum);

/************************************************************************
 send the custom pattern to n location from the 8 locations at CGRAM
 then display it
 ************************************************************************/
void HLCD_voidSendSpecialCharacter(u8 *copy_pu8charArr, u8 copy_u8patternNum,
		u8 copy_u8LineNum, u8 copy_ColNum);

/************************************************************************
 sent pattern n at n block at CGRAM only, not displaying it
 if we want to display the character we send the block number with
 HLCD_voidSendData() command
 ************************************************************************/
void HLCD_voidSetSpecialCharacterPattern(u8 *copy_pu8charArr,
		u8 copy_u8patternNum);

u8 HLCD_u8GetFlag(void);

#define LCD_u8_LINE1	0
#define LCD_u8_LINE2	1

#define LCD_COMMAND_CLEAR_DISPLAY			0b00000001
#define LCD_COMMAND_RETURN_HOME 			0b00000010

#define LCD_COMMAND_SHIFT_DISPLAY_LEFT		0b00011000
#define LCD_COMMAND_SHIFT_DISPLAY_RIGHT		0b00011100

#define LCD_COMMAND_SHIFT_CURSOR_LEFT		0b00010000
#define LCD_COMMAND_SHIFT_CURSOR_RIGHT		0b00010100

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
