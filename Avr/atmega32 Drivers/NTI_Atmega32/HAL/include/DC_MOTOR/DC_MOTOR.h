/**************************************************************************/
/* Filename						: DC_MOTOR.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef HAL_INCLUDE_DC_MOTOR_DC_MOTOR_H_
#define HAL_INCLUDE_DC_MOTOR_DC_MOTOR_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{
	DC_MOTOR_STATUS_OK,
	DC_MOTOR_STATUS_FAIL,
	DC_MOTOR_STATUS_NULL_POINTER_ADDRESS
}Dc_Motor_StatusErrorType;


typedef struct{
	u8 dc_motor_direction_pin1;
	u8 dc_motor_direction_pin2;
}Dc_Motor_ConfigPinsType;
/********************************** Software Interfaces Declarations *******************/
Dc_Motor_StatusErrorType Dc_Motor_MoveForward(const Dc_Motor_ConfigPinsType* Address_DcMotor);
Dc_Motor_StatusErrorType Dc_Motor_MoveBackward(const Dc_Motor_ConfigPinsType* Address_DcMotor);
Dc_Motor_StatusErrorType Dc_Motor_Stop(const Dc_Motor_ConfigPinsType* Address_DcMotor);


#endif /* HAL_INCLUDE_DC_MOTOR_DC_MOTOR_H_ */
