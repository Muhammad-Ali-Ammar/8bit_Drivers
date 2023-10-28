/**************************************************************************/
/* Filename						: SEVEN_SEGMENT_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"

#include "../../../MCAL/DIO/include/DIO.h"
#include "../../include/SEVEN_SEGMENT/SEVEN_SEGMENT_private.h"
#include "../../include/SEVEN_SEGMENT/SEVEN_SEGMENT.h"

/********************************** Macros Declarations *******************************/


#define SEGMENT_COMMON1		DIO_PINA3_CHANNEL3
#define SEGMENT_COMMON2		DIO_PINA2_CHANNEL2
#define SEGMENT_COMMON3		DIO_PINB5_CHANNEL13
#define SEGMENT_COMMON4		DIO_PINB6_CHANNEL14

/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

Seven_Segment_BCDType Seven_Segment ={
		.seven_segment_pins[0]=  DIO_PINB0_CHANNEL8,
		.seven_segment_pins[1]=  DIO_PINB1_CHANNEL9,
		.seven_segment_pins[2]=  DIO_PINB2_CHANNEL10,
		.seven_segment_pins[3]=  DIO_PINB4_CHANNEL12
};

u8 	Seven_SegmentCom4 =  DIO_PINB6_CHANNEL14;
u8 	Seven_SegmentCom3 =  DIO_PINB5_CHANNEL13;
u8 	Seven_SegmentCom2 =  DIO_PINA2_CHANNEL2;
u8 	Seven_SegmentCom1 =  DIO_PINA3_CHANNEL3;

/********************************** Software Interfaces Declarations *******************/
