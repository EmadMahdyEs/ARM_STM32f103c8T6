#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"

#include "../Inc/HAL/LED_MATRIX/LED_MATRIX_interface.h"

u8 pattern[8] = { 255, 2, 4, 8, 16, 32, 64, 255 };

u8 pos1[8] = { 8, 200, 43, 63, 63, 43, 200, 8 };
u8 pos2[8] = { 32, 16, 203, 63, 63, 203, 16, 32 };
u8 pos3[8] = { 0, 0, 59, 255, 255, 59, 0, 0 };

u8 line[8] = { 255, 0, 0, 0, 0, 0, 0, 0 };

void swap(u8 *a, u8 *b)
{
	u8 temp = *a;
	*a = *b;
	*b = temp;
}

int main(void)
{

	MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_GPIOC, RCC_STATUS_ON);
	MRCC_voidSetPeripheralClock(RCC_GPIOA, RCC_STATUS_ON);

	MSYSTICK_voidInit();

	MGPIO_voidSetPinDirection(GPIO_PORTC, 14, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTC, 15, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 0, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 1, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 2, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 3, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 4, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 5, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 6, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 7, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 8, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 9, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 10, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 11, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 12, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTC, 13, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	/* Loop forever */
	int x = 20;
	while (1)
	{
//		for (int i = 0; i < x; i++)
//		{
//			LMTRX_voidDisplayPattern(pos1);
//		}
//
//		for (int i = 0; i < x; i++)
//		{
//			LMTRX_voidDisplayPattern(pos2);
//		}
//
//		for (int i = 0; i < x; i++)
//		{
//			LMTRX_voidDisplayPattern(pos3);
//		}
//
//		for (int i = 0; i < x; i++)
//		{
//			LMTRX_voidDisplayPattern(pos2);
//		}

//		for (int i = 0; i < 7; i++)
//		{
//			swap(line + i, line + i + 1);
//			LMTRX_voidDisplayPattern(line);
//
//		}
//
//		for (int i = 7; i > 1; i--)
//		{
//			swap(line + i, line + i - 1);
//			LMTRX_voidDisplayPattern(line);
//
//		}

		LMTRX_voidDisplayPattern2(line, pos1);

	} //while(1)
} //main
