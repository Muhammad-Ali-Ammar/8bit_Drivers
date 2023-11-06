/**************************************************************************/
/* Filename						: DC_MOTOR.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/
#include "../../../SERIVICES/include/STD_TYPES.h"

#include "../../../MCAL/DIO/include/DIO.h"

#include "../../include/DC_MOTOR/DC_MOTOR.h"




/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/
Dc_Motor_StatusErrorType Dc_Motor_MoveForward(const Dc_Motor_ConfigPinsType* Address_DcMotor){
	Dc_Motor_StatusErrorType Loc_enuDcMotorStatusError = DC_MOTOR_STATUS_OK;
	if(NULL == Address_DcMotor){
		Loc_enuDcMotorStatusError = DC_MOTOR_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		Loc_enuDcMotorStatusError = Dio_enuWriteChannel(Address_DcMotor->dc_motor_direction_pin1,DIO_HIGH);
		Loc_enuDcMotorStatusError = Dio_enuWriteChannel(Address_DcMotor->dc_motor_direction_pin2,DIO_LOW);
	}
	return Loc_enuDcMotorStatusError;
}

Dc_Motor_StatusErrorType Dc_Motor_MoveBackward(const Dc_Motor_ConfigPinsType* Address_DcMotor){
	Dc_Motor_StatusErrorType Loc_enuDcMotorStatusError = DC_MOTOR_STATUS_OK;
	if(NULL == Address_DcMotor){
		Loc_enuDcMotorStatusError = DC_MOTOR_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		Loc_enuDcMotorStatusError = Dio_enuWriteChannel(Address_DcMotor->dc_motor_direction_pin1,DIO_LOW);
		Loc_enuDcMotorStatusError = Dio_enuWriteChannel(Address_DcMotor->dc_motor_direction_pin2,DIO_HIGH);
	}
	return Loc_enuDcMotorStatusError;
}
Dc_Motor_StatusErrorType Dc_Motor_Stop(const Dc_Motor_ConfigPinsType* Address_DcMotor){
	Dc_Motor_StatusErrorType Loc_enuDcMotorStatusError = DC_MOTOR_STATUS_OK;
	if(NULL == Address_DcMotor){
		Loc_enuDcMotorStatusError = DC_MOTOR_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		Loc_enuDcMotorStatusError = Dio_enuWriteChannel(Address_DcMotor->dc_motor_direction_pin1,DIO_LOW);
		Loc_enuDcMotorStatusError = Dio_enuWriteChannel(Address_DcMotor->dc_motor_direction_pin2,DIO_LOW);
	}
	return Loc_enuDcMotorStatusError;
}
