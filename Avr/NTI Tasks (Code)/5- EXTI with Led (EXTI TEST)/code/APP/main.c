/*
 * main.c
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */


#include "../SERIVICES/include/STD_TYPES.h"
#include "../SERIVICES/include/BIT_UTILS.h"
#include "../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../MCAL/PORT/include/PORT.h"
#include "../MCAL/DIO/include/DIO.h"
#include <util/delay.h>
#include  "../HAL/include/LCD/LCD.h"
#include  "../HAL/include/LCD/LCD_config.h"

#include  "../HAL/include/KEYPAD/KEYPAD_config.h"
#include  "../HAL/include/KEYPAD/KEYPAD.h"
#include "../MCAL/GIE/include/GIE.h"
#include "../MCAL/EXTI/include/EXTI.h"






void Exti_ApplicationIsr0(){

	Dio_enuFlipChannel(DIO_PINA4_CHANNEL4);

}

void Exti_ApplicationIsr1(){


	Dio_enuFlipChannel(DIO_PINA6_CHANNEL6);
}


void Exti_ApplicationIsr2(){


	Dio_enuFlipChannel(DIO_PINA5_CHANNEL5);

}

int main(void){

	Port_voidInit();

	Exti_enuEnable(EXTI_INT0_INDEX, EXTI_INT0_SELECT_FAILING_EDGE);
	Exti_enuSetCallbackFunction(EXTI_INT0_INDEX, Exti_ApplicationIsr0);

	Exti_enuEnable(EXTI_INT1_INDEX, EXTI_INT1_SELECT_FAILING_EDGE);
	Exti_enuSetCallbackFunction(EXTI_INT1_INDEX, Exti_ApplicationIsr1);

	Exti_enuEnable(EXTI_INT2_INDEX, EXTI_INT2_SELECT_FAILING_EDGE);
	Exti_enuSetCallbackFunction(EXTI_INT2_INDEX, Exti_ApplicationIsr2);


	Gie_enuEnableGlobalInterrupt();

	while(1){



	}
	return 0;
}



