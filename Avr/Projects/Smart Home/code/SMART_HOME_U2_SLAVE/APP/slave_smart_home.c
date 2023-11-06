/**************************************************************************/
/* Filename						: main.h                                  */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/

#include "slave_smart_home.h"


int main(){

	SlaveSmart_enuInit();

	while(1){

	}

	return 0;
}

void smart_voidTimer0Isr(void){
	static volatile u8 Loc_u8Counter = ZERO_VALUE;
	u16 Loc_u16AdcResult;
	f32 Loc_f32Result;
	Loc_u8Counter++;
	if(15 == Loc_u8Counter){

		Adc_enuStartConversionSync(&Adc0, &Loc_u16AdcResult);

		Adc_ConvertResultToVoltage(Loc_u16AdcResult, &Loc_f32Result);
		Convert_VoltToTempLm35(Loc_f32Result, &Loc_u16AdcResult);

		if(Loc_u16AdcResult >=70){
			Dio_enuWriteChannel(BUZZER_PIN, DIO_HIGH);
			Timer0_enuSetDutyCyclePwm(&Timer0,100);
		}
		else{
			Dio_enuWriteChannel(BUZZER_PIN, DIO_LOW);
			Timer0_enuSetDutyCyclePwm(&Timer0,0);
		}

		Loc_u8Counter = ZERO_VALUE;
	}
}

void smart_voidSpiIsr(u8 Copy_u8Result){

		Dio_enuWriteChannel(ROOM1_PIN, READ_BIT(Copy_u8Result,0));
		Dio_enuWriteChannel(ROOM2_PIN, READ_BIT(Copy_u8Result,1));
		Dio_enuWriteChannel(ROOM3_PIN, READ_BIT(Copy_u8Result,2));

}
