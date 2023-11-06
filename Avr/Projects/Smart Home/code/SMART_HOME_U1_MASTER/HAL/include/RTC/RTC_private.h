/**************************************************************************/
/* Filename						: RTC_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef HAL_INCLUDE_RTC_RTC_PRIVATE_H_
#define HAL_INCLUDE_RTC_RTC_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define RTC_ADDRESS_7BIT                ((u8)(0b1101000))
#define RTC_SECOND_REG_ADDRESS          ((u8)(0x00))
#define RTC_MINUTE_REG_ADDRESS          ((u8)(0x01))
#define RTC_HOUR_REG_ADDRESS            ((u8)(0x02))

#define RTC_DAY_REG_ADDRESS             ((u8)(0x04))
#define RTC_MONTH_REG_ADDRESS           ((u8)(0x05))
#define RTC_YEAR_REG_ADDRESS            ((u8)(0x06))


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* HAL_INCLUDE_RTC_RTC_PRIVATE_H_ */
