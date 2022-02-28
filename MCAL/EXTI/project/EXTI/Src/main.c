#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/NVIC/NVIC_interface.h"
#include "../Inc/MCAL/EXTI/EXTI_interface.h"

void EXTI0_IRQHandler(void)
{
	MEXTI_voidClearPending(EXTI_LINE0);
	static u8 x = 0;

	if (x == 0)
	{
		MGPIO_voidSetPinValue(GPIO_PORTB, 1, GPIO_LOW);
		x = 1;
	}
	else
	{
		MGPIO_voidSetPinValue(GPIO_PORTB, 1, GPIO_HIGH);
		x = 0;
	}

}

int main(void)
{
	//RCC
	MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_GPIOB, RCC_STATUS_ON);
	MRCC_voidSetPeripheralClock(RCC_AFIO, RCC_STATUS_ON);

	//GPIO
	MGPIO_voidSetPinDirection(GPIO_PORTB, 0, GPIO_MODE_INPUT,
			GPIO_INPUT_CNFG_PUSH_PULL);
	MGPIO_voidSetPinValue(GPIO_PORTB, 0, GPIO_HIGH);

	MGPIO_voidSetPinDirection(GPIO_PORTB, 1, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	//AFIO
	MAFIO_voidSetEXTILineSource(AFIO_EXTI0_LINE, AFIO_EXTI_GPIOB);

	//NVIC
	MNVIC_voidEnableInterrupt(NVIC_EXTI0);

	//EXTI
	MEXTI_voidSetInterruptMode(EXTI_LINE0, EXTI_FALLING);
	MEXTI_voidEXTILineStatus(EXTI_LINE0, EXTI_ENABLE);

	while (1)
	{

	}

	return 1;
}
