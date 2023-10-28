/**************************************************************************/
/* Filename						: BUTTON.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 22 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef HAL_INCLUDE_BUTTON_BUTTON_H_
#define HAL_INCLUDE_BUTTON_BUTTON_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{
    BUTTON_NOT_PRESSED,
    BUTTON_PRESSED
}Button_PressStatusType;


typedef enum{
    BUTTON_CONNECTION_PULL_UP,
    BUTTON_CONNECTION_PULL_DOWN
}Button_ConnectionType;


typedef enum{
    BUTTON_STATUS_OK,
    BUTTON_STATUS_FAIL,
    BUTTON_STATUS_NULL_POINTER_ADDRESS
}Button_StatusErrorType;


typedef struct{
    u8                 button_pin;
    Button_ConnectionType button_connection;

}Button_ConfigType;




/********************************** Software Interfaces Declarations *******************/

Button_StatusErrorType Button_enuRead(const Button_ConfigType *Address_Button,Button_PressStatusType* Address_State );

#endif /* HAL_INCLUDE_BUTTON_BUTTON_H_ */
