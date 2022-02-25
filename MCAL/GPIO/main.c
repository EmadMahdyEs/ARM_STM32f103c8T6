#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"



int main(void)
{
	//MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_GPIOC, RCC_STATUS_ON);
	MRCC_voidSetPeripheralClock(RCC_GPIOA, RCC_STATUS_ON);

	MGPIO_voidSetPinDirection(GPIO_PORTC, 13, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 1, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 2, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MGPIO_voidLockPins(GPIO_PORTA, 0x0006);
	MGPIO_voidSetPinDirection(GPIO_PORTA, 1, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	while (1)
	{
		MGPIO_voidSetPinValue(GPIO_PORTC, 13, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, 1, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, 2, GPIO_HIGH);
		for (int x = 0; x < 50000; x++)
			;

		MGPIO_voidSetPinValue(GPIO_PORTC, 13, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, 1, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, 2, GPIO_LOW);
		for (int x = 0; x < 50000; x++)
			;
	}

	return 0;
}
