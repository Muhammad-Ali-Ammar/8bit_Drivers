/**************************************************************************/
/* Filename						: RTC.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/



#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../../SERIVICES/include/calculation_functions.h"
#include <util/delay.h>
#include "../../../MCAL/DIO/include/DIO.h"

#include "../../../MCAL/I2C/include/I2C.h"
#include "../../include/RTC/RTC_private.h"
#include "../../include/RTC/RTC_config.h"
#include "../../include/RTC/RTC.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/

Rtc_StatusErrorType Rtc_enuGetSecond(u8* Address_Result){

	Rtc_StatusErrorType Loc_enuRtcStatusError = RTC_STATUS_OK;
	u8 Loc_u8Temp;
	u8 Loc_u8AnswerInBCD;
	if(NULL == Address_Result){
		Loc_enuRtcStatusError = RTC_STATUS_FAIL;
	}
	else{

		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(RTC_SECOND_REG_ADDRESS, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterReceiveDataBlocking(&Loc_u8AnswerInBCD,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		Convert_BCDToInt(Loc_u8AnswerInBCD, Address_Result);
		_delay_ms(1);
	}
	return Loc_enuRtcStatusError;
}

Rtc_StatusErrorType Rtc_enuGetMinute(u8* Address_Result){

	Rtc_StatusErrorType Loc_enuRtcStatusError = RTC_STATUS_OK;
	u8 Loc_u8Temp;
	u8 Loc_u8AnswerInBCD;
	if(NULL == Address_Result){
		Loc_enuRtcStatusError = RTC_STATUS_FAIL;
	}
	else{

		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(RTC_MINUTE_REG_ADDRESS, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterReceiveDataBlocking(&Loc_u8AnswerInBCD,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		Convert_BCDToInt(Loc_u8AnswerInBCD, Address_Result);
		_delay_ms(1);
	}
	return Loc_enuRtcStatusError;
}
Rtc_StatusErrorType Rtc_enuGetHour(u8* Address_Result){

	Rtc_StatusErrorType Loc_enuRtcStatusError = RTC_STATUS_OK;
	u8 Loc_u8Temp;
	u8 Loc_u8AnswerInBCD;
	if(NULL == Address_Result){
		Loc_enuRtcStatusError = RTC_STATUS_FAIL;
	}
	else{
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(RTC_HOUR_REG_ADDRESS, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterReceiveDataBlocking(&Loc_u8AnswerInBCD,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		Convert_BCDToInt(Loc_u8AnswerInBCD, Address_Result);
		_delay_ms(1);
	}
	return Loc_enuRtcStatusError;
}


Rtc_StatusErrorType Rtc_enuGetDay(u8* Address_Result){

	Rtc_StatusErrorType Loc_enuRtcStatusError = RTC_STATUS_OK;
	u8 Loc_u8Temp;
	u8 Loc_u8AnswerInBCD;

	if(NULL == Address_Result){
		Loc_enuRtcStatusError = RTC_STATUS_FAIL;
	}
	else{
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(RTC_DAY_REG_ADDRESS, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterReceiveDataBlocking(&Loc_u8AnswerInBCD,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		Convert_BCDToInt(Loc_u8AnswerInBCD, Address_Result);
		_delay_ms(1);
	}
	return Loc_enuRtcStatusError;
}
Rtc_StatusErrorType Rtc_enuGetMonth( u8* Address_Result){

	Rtc_StatusErrorType Loc_enuRtcStatusError = RTC_STATUS_OK;
	u8 Loc_u8Temp;
	u8 Loc_u8AnswerInBCD;
	if(NULL == Address_Result){
		Loc_enuRtcStatusError = RTC_STATUS_FAIL;
	}
	else{
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(RTC_MONTH_REG_ADDRESS, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterReceiveDataBlocking(&Loc_u8AnswerInBCD,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		Convert_BCDToInt(Loc_u8AnswerInBCD, Address_Result);
		_delay_ms(1);
	}
	return Loc_enuRtcStatusError;
}
Rtc_StatusErrorType Rtc_enuGetYear(u8* Address_Result){

	Rtc_StatusErrorType Loc_enuRtcStatusError = RTC_STATUS_OK;
	u8 Loc_u8Temp;
	u8 Loc_u8AnswerInBCD;
	if(NULL == Address_Result){
		Loc_enuRtcStatusError = RTC_STATUS_FAIL;
	}
	else{
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(RTC_YEAR_REG_ADDRESS, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(RTC_ADDRESS_7BIT, &Loc_u8Temp);
		I2c_enuMasterReceiveDataBlocking(&Loc_u8AnswerInBCD,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		Convert_BCDToInt(Loc_u8AnswerInBCD, Address_Result);
		_delay_ms(1);
	}
	return Loc_enuRtcStatusError;
}



