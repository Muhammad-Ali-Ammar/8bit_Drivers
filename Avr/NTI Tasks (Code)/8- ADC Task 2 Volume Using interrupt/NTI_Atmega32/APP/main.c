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




//////////////////////////////////////////////////////////////////
extern Lcd_4bitType Lcd;

u8 Global_Flag = 0;
Adc_PinConfigType Adc0 ={
		.channel_number = ADC_SELECT_CHANNEL1,
		.conversion_frequancy = ADC_FOSC_DIV_128,
		.result_format = ADC_RIGHT_JUSTIFIED,
		.vref_source = ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR

};





u8 Lcd_Custom1[]={0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F};
u8 Lcd_Custom2[]={0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F};
u8 Lcd_Custom3[]={0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};

void adc_isr(u16 result){
	if(result<=341){
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 1, LCD_ROW2, LCD_COL12);
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL13);
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL14);

	}
	else if(result<=682){
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 1, LCD_ROW2, LCD_COL12);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 2, LCD_ROW2, LCD_COL13);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW2, LCD_COL14);

		}
	else {
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 1, LCD_ROW2, LCD_COL12);
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 2, LCD_ROW2, LCD_COL13);
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, 3, LCD_ROW2, LCD_COL14);
	}

}
int main(void){

	Port_voidInit();
	Lcd_4bit_enuInit(&Lcd);
	Adc_enuInit(&Adc0);

	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_Custom1, 1);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_Custom2, 2);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_Custom3, 3);



	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL5);
	Lcd_4bit_enuDisplayString(&Lcd, "VOLUME ");

	Adc_SetCallbackFunction(&Adc0, adc_isr);
	Adc_enuEnableInterrupt();

	Gie_enuEnableGlobalInterrupt();

	while(1){
		Adc_StartConversionAsync(&Adc0);




		_delay_ms(14);
	}
	return 0;
}

