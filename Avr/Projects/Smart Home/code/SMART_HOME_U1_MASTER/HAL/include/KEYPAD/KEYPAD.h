/**************************************************************************/
/* Filename						: KEYPAD.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef HAL_INCLUDE_KEYPAD_KEYPAD_H_
#define HAL_INCLUDE_KEYPAD_KEYPAD_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{

	KEYPAD_IS_PRESSED,
	KEYPAD_STATUS_FAIL,
	KEYPAD_STATUS_NULL_POINTER_ADDRESS,
	KEYPAD_STATUS_NOT_PRESSED
}Keypad_ErrorStatusType;

typedef enum{

    KEYPAD_IDLE_VOLTAGE_LOW,
    KEYPAD_IDLE_VOLTAGE_HIGH
}Keypad_IdleVoltageType;

typedef enum{

    KEYPAD_ROW_CONTROL,
    KEYPAD_COL_CONTROL
}Keypad_ControllingPinsType;


typedef struct{
    u8 keypad_rows_pins[KEYPAD_ROWS_NUMBER];
    u8 keypad_cols_pins[KEYPAD_COLS_NUMBER];
    Keypad_ControllingPinsType keypad_control_pins;
    Keypad_IdleVoltageType  keypad_idle_volt;
}Keypad_ConfigType;

/********************************** Software Interfaces Declarations *******************/
Keypad_ErrorStatusType Keypad_enuRead(const Keypad_ConfigType* Address_Keypad, pu8 Address_ResultValue);


#endif /* HAL_INCLUDE_KEYPAD_KEYPAD_H_ */
