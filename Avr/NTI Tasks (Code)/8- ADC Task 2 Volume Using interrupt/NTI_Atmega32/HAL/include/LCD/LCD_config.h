/**************************************************************************/
/* Filename						: LCD_config.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 21 Oct 2023  	           	 	      	  */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef HAL_INCLUDE_LCD_CONFIG_H_
#define HAL_INCLUDE_LCD_CONFIG_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


#define LCD_ROW_NUMBERS			4
#define LCD_COL_NUMBERS			20


#define LCD_4BIT_D4				DIO_PINB0_CHANNEL8
#define LCD_4BIT_D5				DIO_PINB1_CHANNEL9
#define LCD_4BIT_D6				DIO_PINB2_CHANNEL10
#define LCD_4BIT_D7				DIO_PINB4_CHANNEL12


#define LCD_4BIT_EN				DIO_PINA2_CHANNEL2
#define LCD_4BIT_RS 			DIO_PINA3_CHANNEL3

/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* HAL_INCLUDE_LCD_CONFIG_H_ */
