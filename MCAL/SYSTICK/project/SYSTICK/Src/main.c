#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"

void ISR(void)
{
	static u8 x = 1;

	if (x)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, 1, GPIO_HIGH);
		x = 0;
	}
	else
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, 1, GPIO_LOW);
		x = 1;
	}

}

int main(void)
{

	MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_GPIOA, RCC_STATUS_ON);
	MSYSTICK_voidInit();
	MGPIO_voidSetPinDirection(GPIO_PORTA, 1, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MSYSTICK_voidSetIntervalPeriodic(3000000, ISR);

	/* Loop forever */
	while (1)
	{
//		MGPIO_voidSetPinValue(GPIO_PORTA, 1, GPIO_HIGH);
//		MSYSTICK_voidDelay_MS(1000);
//		MGPIO_voidSetPinValue(GPIO_PORTA, 1, GPIO_LOW);
//		MSYSTICK_voidDelay_MS(1000);

	}
}
