/*
 * main.c
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */


#include "../SERIVICES/include/STD_TYPES.h"
#include "../SERIVICES/include/BIT_UTILS.h"
#include "../SERIVICES/include/calculation_functions.h"
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
#include  "../HAL/include/BUTTON/BUTTON.h"
#include  "../HAL/include/SEVEN_SEGMENT/SEVEN_SEGMENT.h"
#include "../MCAL/ADC/include/ADC.h"
#include "../MCAL/TIMER0/include/TIMER0.h"
#include "../MCAL/WTD/include/WDT.h"
#include  "../HAL/include/ICUSW/ICUSW.h"



Icusw_ConfigType Icusw0={
		.exti_Intx_Index = EXTI_INT0_INDEX,
		.timer_index = ICUSW_TIMER_INDEX_TIMER0
};


extern Lcd_4bitType Lcd;

int main(void){

	Port_voidInit();
	Icusw_enuInit(&Icusw0);
	Lcd_4bit_enuInit(&Lcd);

	u32 Loc_u32Dutycycle = 0;
	u32 Loc_u32OnTime = 0;
	u32 Loc_u32TotalTime = 0;

	while(1){

		Icusw_enuGetOnTimeMilliSeconds(&Icusw0,&Loc_u32OnTime );

		Icusw_enuGetTotalTimeMilliSeconds(&Icusw0,&Loc_u32TotalTime );

		Icusw_enuGetDutyCycleMilliSeconds(&Icusw0,&Loc_u32Dutycycle );

		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Total Time", LCD_ROW1, LCD_COL1);
		Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u32TotalTime);
		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "on Time", LCD_ROW2, LCD_COL1);

		Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u32OnTime);
		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Duty Time", LCD_ROW3, LCD_COL1);

		Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u32Dutycycle);

		_delay_ms(1000);


	}
	return 0;
}






