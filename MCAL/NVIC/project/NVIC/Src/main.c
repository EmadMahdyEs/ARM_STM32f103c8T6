#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/NVIC/NVIC_interface.h"

int main(void)
{

	MNVIC_voidSetPendingInterrupt(2);

	MNVIC_voidSetPendingInterrupt(8);

	MNVIC_voidSetPendingInterrupt(34);

	MNVIC_voidSetPriorityGrouping(NVIC_8_GROUP_2_SUB);

	MNVIC_voidSetISRPriority(9, NVIC_4_GROUP_4_SUB, 3, 3);

	MNVIC_voidSetISRPriority(NVIC_USAGE_FAULT, NVIC_4_GROUP_4_SUB, 3, 3);
	MNVIC_voidSetISRPriority(NVIC_SYSTICK, NVIC_4_GROUP_4_SUB, 3, 3);

	MNVIC_voidClearPendingInterrupt(2);
	MNVIC_voidClearPendingInterrupt(8);
	MNVIC_voidClearPendingInterrupt(34);
	/* Loop forever */
	while (1)
	{

	}
}
