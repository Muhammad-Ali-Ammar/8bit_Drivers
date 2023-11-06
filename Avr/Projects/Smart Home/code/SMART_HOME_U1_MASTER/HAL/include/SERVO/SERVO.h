/**************************************************************************/
/* Filename						: SERVO.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef HAL_INCLUDE_SERVO_SERVO_H_
#define HAL_INCLUDE_SERVO_SERVO_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


typedef enum{
	SERVO_STATUS_OK,
	SERVO_STATUS_FAIL,
	SERVO_STATUS_NULL_POINTER_ADDRESS
}Servo_StatusErrorType;



/********************************** Software Interfaces Declarations *******************/


Servo_StatusErrorType Servo_enuInitTimer1(void);
Servo_StatusErrorType Servo_enuSetAngle(u8 Copy_u8Angle);

#endif /* HAL_INCLUDE_SERVO_SERVO_H_ */
