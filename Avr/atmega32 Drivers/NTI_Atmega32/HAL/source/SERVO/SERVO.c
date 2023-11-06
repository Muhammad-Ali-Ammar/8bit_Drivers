/**************************************************************************/
/* Filename						: SERVO.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"

#include "../../../MCAL/DIO/include/DIO.h"
#include "../../../MCAL/TIMER1/include/TIMER1.h"
#include "../../../HAL/include/SERVO/SERVO.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

extern Timer1_ConfigType Timer1;


/********************************** Software Interfaces Declarations *******************/

Servo_StatusErrorType Servo_enuInitTimer1(void){

	Servo_StatusErrorType Loc_enuServoStatusError = SERVO_STATUS_OK;
	Timer1_enuInit(&Timer1);
	Timer1_enuSetValueIcu(311);
	Timer1_enuSetValueCompareChannelB(ZERO_VALUE);


	return Loc_enuServoStatusError;
}
Servo_StatusErrorType Servo_enuSetAngle(u8 Copy_u8Angle){

	Servo_StatusErrorType Loc_enuServoStatusError = SERVO_STATUS_OK;
	Copy_u8Angle = (Copy_u8Angle>180)? 180 : Copy_u8Angle;

	/* 1ms === 0 angle
	 * 2ms === 180 angle
	 *
	 * time = a*Angle + b
	 * 1ms = b
	 * 2ms = 180a + 1ms
	 * a = 1ms/180
	 * time = (1ms/180)*a + b
	 * time = ticks* 1024/16M = (1ms/180)*a + b
	 * ticks = (25/288)*angle + (125/8)
	 *
	 */
	Timer1_enuSetValueCompareChannelB((u16)(Copy_u8Angle*25/288.0+(125/8.0)));


	return Loc_enuServoStatusError;
}
