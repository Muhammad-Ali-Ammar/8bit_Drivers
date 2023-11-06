/**************************************************************************/
/* Filename						: SERVO_config.c                            */
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
#include "../../../MCAL/TIMER1/include/TIMER1.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
	Timer1_ConfigType Timer1 ={
			.init_counter_value =0,
			.prescaler_value = TIMER1_PRESCALER_DIV_1024,
			.select_mode = TIMER1_SELECT_MODE_PWM_FAST_ICR1_MODE14,
			.select_output_mode_channelB = TIMER1_SELECT_OUTPUT_MODE_IN_CTC_CLEAR__IN_FAST_PWM_CLEAR_ON_MATCH___IN_PHASE_CORRECT_CLEAR_AT_MATCH_UPCOUNTING_SET_AT_MATCH_AT_DOCOUNTING_CHANNELB,

	};




/********************************** Software Interfaces Declarations *******************/
