/**************************************************************************/
/* Filename						: main.c                                */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At		  			: NTI 								  	  */
/* Instructor		  			: Mahmoud Embabi 					  	  */
/**************************************************************************/


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
#include "../MCAL/TIMER1/include/TIMER1.h"
#include "../MCAL/WTD/include/WDT.h"
#include  "../HAL/include/ICUSW/ICUSW.h"



/////////////////////////////////////////////////////////////////////////

extern Lcd_4bitType Lcd;
Timer1_ConfigType Timer1={
		.init_counter_value = ZERO_VALUE,
		.prescaler_value = TIMER1_PRESCALER_DIV_256,
		.select_mode= TIMER1_SELECT_MODE_NORMAL_MODE0,
		.select_output_mode_channelA = TIMER1_SELECT_OUTPUT_MODE_NORMAL_CHANNELA,
		.select_output_mode_channelB = TIMER1_SELECT_OUTPUT_MODE_NORMAL_CHANNELB
};
/////////////////////////////////////////////////////////////////

u64 Global_u64OnTime =ZERO_VALUE;
u64 Global_u64TotalTime =ZERO_VALUE;
u64 Global_u64DutyCycle =ZERO_VALUE;


u64 Global_u64OnTicks =ZERO_VALUE;
u64 Global_u64TotalTicks =ZERO_VALUE;



u64 Global_u64OverflowCounter =ZERO_VALUE;

////////////////////////////////////////////////////////

void Timer1_Isr(void){
	Global_u64OverflowCounter++;
}

void Icu_Isr(void){

	f64 Loc_f64TickTimeMiliSeconds = 0.016;  /* Prescaler/16000000 */
	static u8 Loc_u8Counter = ZERO_VALUE;

	static u16 Loc_u16FirstTicks = ZERO_VALUE;
	static u16 Loc_u16SecondTicks = ZERO_VALUE;
	static u16 Loc_u16ThirdTicks = ZERO_VALUE;


	if(Loc_u8Counter == ZERO_VALUE){
		Loc_u8Counter++;
		Global_u64OverflowCounter = ZERO_VALUE;
		Timer1_enuToggleEdgeIcu();
		Timer1_enuGetTimeElapsedIcu(&Loc_u16FirstTicks);


	}
	else if (Loc_u8Counter == ONE_VALUE){
		Loc_u8Counter++;
		Timer1_enuToggleEdgeIcu();
		Timer1_enuGetTimeElapsedIcu(&Loc_u16SecondTicks);
		Global_u64OnTicks = Loc_u16SecondTicks + (Global_u64OverflowCounter * TIMER1_16BIT_MAX_REGISTER_VALUE)-Loc_u16FirstTicks;
		Global_u64OnTime = Global_u64OnTicks * Loc_f64TickTimeMiliSeconds;
	}

	else if (Loc_u8Counter == TWO_VALUE){

		Dio_enuFlipChannel(DIO_PINC0_CHANNEL16);
		Timer1_enuGetTimeElapsedIcu(&Loc_u16ThirdTicks);
		Global_u64TotalTicks = Loc_u16ThirdTicks + (Global_u64OverflowCounter * TIMER1_16BIT_MAX_REGISTER_VALUE)-Loc_u16FirstTicks;
		Global_u64TotalTime = Global_u64TotalTicks * Loc_f64TickTimeMiliSeconds;
		Global_u64DutyCycle = (u64)((Global_u64OnTime*100.0)/Global_u64TotalTime);
		/* start of First Edge Already */
		Loc_u8Counter = ONE_VALUE;
		Timer1_enuToggleEdgeIcu();
		Loc_u16FirstTicks = Loc_u16ThirdTicks;
		Global_u64OverflowCounter = ZERO_VALUE;

	}

}
/////////////////////////////////////////////////////////////////
int main(void){

	Port_voidInit();
	Lcd_4bit_enuInit(&Lcd);

	Timer1_enuSetCallbackFunctionOverflow(Timer1_Isr);
	Timer1_enuSetCallbackFunctionIcu(Icu_Isr);

	Timer1_enuSetRisingEdgeIcu();
	Timer1_enuEnableInterruptIcu();
	Timer1_enuEnableInterruptOverflow();
	Gie_enuEnableGlobalInterrupt();

	Timer1_enuInit(&Timer1);
	while(1){

				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Total Time: ", LCD_ROW1, LCD_COL1);
				Lcd_4bit_enuDisplayNumber(&Lcd, Global_u64TotalTime);
				Lcd_4bit_enuDisplayString(&Lcd, " [mV]");

				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "on Time: ", LCD_ROW2, LCD_COL1);
				Lcd_4bit_enuDisplayNumber(&Lcd, Global_u64OnTime);
				Lcd_4bit_enuDisplayString(&Lcd, " [mV]");

				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, "Duty Cycle:", LCD_ROW3, LCD_COL1);
				Lcd_4bit_enuDisplayNumber(&Lcd, Global_u64DutyCycle);
				Lcd_4bit_enuDisplayString(&Lcd, "%");

				_delay_ms(1000);

	}
	return 0;
}



