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
#include  "../HAL/include/BUTTON/BUTTON.h"
#include  "../HAL/include/SEVEN_SEGMENT/SEVEN_SEGMENT.h"
#include "../MCAL/ADC/include/ADC.h"


///////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
//

#define VOLT_FLAG			0
#define MILLI_VOLT_FLAG		1

//////////////////////////////////////////////////////////////////
extern Lcd_4bitType Lcd;

u8 Global_Flag = VOLT_FLAG;

Adc_PinConfigType Adc1 ={
		.channel_number = ADC_SELECT_CHANNEL1,
		.conversion_frequancy = ADC_FOSC_DIV_128,
		.result_format = ADC_RIGHT_JUSTIFIED,
		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR

};


void	Exti_ApplicationIsr0_VOLT(){
	Global_Flag = VOLT_FLAG;
}


void	Exti_ApplicationIsr1_MILIVOLT(){
	Global_Flag = MILLI_VOLT_FLAG;
}




int main(void){

	u16 Loc_u16Result= ZERO_VALUE;
	f32 Loc_f32Result;

	Port_voidInit();
	Lcd_4bit_enuInit(&Lcd);
	Adc_enuInit(&Adc1);

		Exti_enuEnable(EXTI_INT0_INDEX, EXTI_INT0_SELECT_FAILING_EDGE);
		Exti_enuSetCallbackFunction(EXTI_INT0_INDEX, Exti_ApplicationIsr0_VOLT);

		Exti_enuEnable(EXTI_INT1_INDEX, EXTI_INT1_SELECT_FAILING_EDGE);
		Exti_enuSetCallbackFunction(EXTI_INT1_INDEX, Exti_ApplicationIsr1_MILIVOLT);
		Gie_enuEnableGlobalInterrupt();
		Lcd_4bit_enuDisplayString(&Lcd, "Volt= ");

	while(1){
		Adc_enuStartConversionSync(&Adc1,&Loc_u16Result);
		Adc_ConvertResultToVoltage(Loc_u16Result, &Loc_f32Result);

		// Volt Mode
		if(Global_Flag == VOLT_FLAG){

						Loc_u16Result= Loc_f32Result;
						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
						Lcd_4bit_enuDisplayString(&Lcd,"       ");
						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
						Lcd_4bit_enuDisplayNumber(&Lcd,Loc_u16Result);
						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ',LCD_ROW4, LCD_COL18);
						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 'V',LCD_ROW4, LCD_COL19);

					}
					else {
						Loc_u16Result= Loc_f32Result* 1000;
						Lcd_4bit_enuDisplayString(&Lcd,"       ");
						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
						Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW1, LCD_COL7);
						Lcd_4bit_enuDisplayNumber(&Lcd,Loc_u16Result);
						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 'm',LCD_ROW4, LCD_COL18);
						Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 'V',LCD_ROW4, LCD_COL19);
					}

			_delay_ms(25);

	}
	return 0;
}




/////////////////////////////////////////////////////////////////////
