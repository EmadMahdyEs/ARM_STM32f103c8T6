#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"

#include "../Inc/HAL/LCD/LCD_interface.h"

u8 arr[] = { 0b00100, 0b01010, 0b00100, 0b11111, 0b00100, 0b00100, 0b01110,
		0b01010 };

u8 arr2[] = { 0b00000, 0b00000, 0b00000, 0b11011, 0b11111, 0b11111, 0b01110,
		0b00100 };

int main(void)
{
	MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_GPIOB, RCC_STATUS_ON);
	MRCC_voidSetPeripheralClock(RCC_GPIOA, RCC_STATUS_ON);

	MGPIO_voidSetPortDirection(GPIO_PORTA, 0, 7, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTB, 0, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTB, 1, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTB, 5, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MSYSTICK_voidInit();

	HLCD_voidInit();

	HLCD_voidSendCommand(LCD_COMMAND_CLEAR_DISPLAY);

	HLCD_voidSendData('N');
	HLCD_voidSendData('O');
	HLCD_voidSendData('U');
	HLCD_voidSendData('R');

	MSYSTICK_voidDelay_MS(1000);

	HLCD_voidSendCommand(LCD_COMMAND_CLEAR_DISPLAY);

	HLCD_voidSendData('1');
	HLCD_voidSendData('2');
	HLCD_voidSendData('3');
	HLCD_voidSendData('4');

	MSYSTICK_voidDelay_MS(1000);

	HLCD_voidClearDisplay();

	HLCD_voidDisplayString("hello");

	HLCD_voidGoToPos(LCD_u8_LINE2, 0);

	HLCD_voidDisplayNumber(1254);

	HLCD_voidSendSpecialCharacter(arr, 0, LCD_u8_LINE2, 6);

	HLCD_voidSendData(0);

	HLCD_voidSetSpecialCharacterPattern(arr2, 2);
	//HLCD_voidGoToPos(LCD_u8_LINE2, 8);

	HLCD_voidSendData(2);
	HLCD_voidSendData(2);

	while (1)
	{

	}
	return 0;
}
