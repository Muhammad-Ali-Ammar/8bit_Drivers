/**************************************************************************/
/* Filename						: slave_smart_home.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 4 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef APP_SLAVE_SMART_HOME_H_
#define APP_SLAVE_SMART_HOME_H_

/********************************** Includes *********************************************/

#include "../SERIVICES/include/STD_TYPES.h"
#include "../SERIVICES/include/BIT_UTILS.h"
#include "../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../SERIVICES/include/calculation_functions.h"

#include "../MCAL/DIO/include/DIO.h"
#include "../MCAL/PORT/include/PORT.h"
#include "../MCAL/TIMER0/include/TIMER0.h"
#include "../MCAL/ADC/include/ADC.h"
#include "../MCAL/SPI/include/SPI.h"
#include "../MCAL/GIE/include/GIE.h"



#include <util/delay.h>

/********************************** Macros Declarations *******************************/

#define ROOM1_PIN		DIO_PINC0_CHANNEL16
#define ROOM2_PIN		DIO_PINC1_CHANNEL17
#define ROOM3_PIN		DIO_PINC2_CHANNEL18
#define BUZZER_PIN		DIO_PINC3_CHANNEL19

/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
extern Timer0_ConfigType Timer0;
extern Adc_PinConfigType Adc0;
extern Spi_ConfigType Spi;

typedef enum{
	SLAVE_SMART_ERROR_STATUS_OK,
	SLAVE_SMART_ERROR_STATUS_FAIL
}SlaveSmart_ErrorStatusType;



/********************************** Software Interfaces Declarations *******************/
SlaveSmart_ErrorStatusType SlaveSmart_enuInit(void);


/* ISRs */
void smart_voidTimer0Isr(void);
void smart_voidSpiIsr(u8 Copy_u8Result);

#endif /* APP_SLAVE_SMART_HOME_H_ */
