/**************************************************************************/
/* Filename						: main.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef APP_MASTER_SMART_HOME_H_
#define APP_MASTER_SMART_HOME_H_

/********************************** Includes *********************************************/
#include "../SERIVICES/include/STD_TYPES.h"
#include "../SERIVICES/include/BIT_UTILS.h"
#include "../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../SERIVICES/include/calculation_functions.h"

#include "../MCAL/DIO/include/DIO.h"
#include "../MCAL/PORT/include/PORT.h"
#include "../MCAL/TIMER0/include/TIMER0.h"
#include "../MCAL/TIMER1/include/TIMER1.h"
#include "../MCAL/USART/include/USART.h"
#include "../MCAL/SPI/include/SPI.h"
#include "../MCAL/I2C/include/I2C.h"
#include "../MCAL/GIE/include/GIE.h"


#include "../HAL/include/KEYPAD/KEYPAD_config.h"
#include "../HAL/include/KEYPAD/KEYPAD.h"
#include "../HAL/include/SERVO/SERVO.h"
#include "../HAL/include/EXTERNAL_EEPROM/EXTERNAL_EEPROM_config.h"
#include "../HAL/include/EXTERNAL_EEPROM/EXTERNAL_EEPROM.h"

#include "../HAL/include/RTC/RTC.h"

#include "../HAL/include/LCD/LCD.h"


#include <util/delay.h>
/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
extern Usart_ConfigType Usart1;
extern Lcd_4bitType Lcd;
extern Timer0_ConfigType Timer0;
extern Spi_ConfigType Spi;
extern I2c_ConfigType I2c;
extern Keypad_ConfigType Keypad;

typedef enum{
	SMART_ERROR_STATUS_OK,
	SMART_ERROR_STATUS_FAIL
}Smart_ErrorStatusType;


/********************************** Software Interfaces Declarations *******************/
Smart_ErrorStatusType Smart_enuInit(void);
void smart_WelcomeHome();

void Smart_KeypadModeAdmin();
void Smart_KeypadModeUser();
void Smart_KeypadAdminList();
void Smart_AddUserKeypad();
void Smart_DeleteUserKeypad();
void MasterSmart_ChangePasswordKeypad(u8 Loc_u8CopyUserId,u8 Loc_u8CopyUserPassword);

void Smart_UartModeAdmin();
void Smart_UartModeUser();
void Smart_UartAdminList();
void Smart_AddUserUart();
void Smart_DeleteUserUart();
void MasterSmart_ChangePasswordUart(u8 Loc_u8CopyUserId,u8 Loc_u8CopyUserPassword);


void Smart_ShowTime();
void smart_voidUartIsr(u16 Copy_u16ReceiveData);
void smart_voidTimer0Isr(void);
void Smart_ShowTimeUart(void);
#endif /* APP_MASTER_SMART_HOME_H_ */
