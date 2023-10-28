/**************************************************************************/
/* Filename						: TIMER1.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 26 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_TIMER1_INCLUDE_TIMER1_H_
#define MCAL_TIMER1_INCLUDE_TIMER1_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{


    TIMER1_PRESCALER_NO_DIV=1,
    TIMER1_PRESCALER_DIV_8,
    TIMER1_PRESCALER_DIV_64,
    TIMER1_PRESCALER_DIV_256,
    TIMER1_PRESCALER_DIV_1024,
    TIMER1_PRESCALER_EXTERNAL_CLOCK_SORUCE_FAILING_EDGE_T1PIN,
    TIMER1_PRESCALER_EXTERNAL_CLOCK_SORUCE_RASING_EDGE_T1PIN

}Timer1_PrescalerTYpe;





/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_TIMER1_INCLUDE_TIMER1_H_ */
