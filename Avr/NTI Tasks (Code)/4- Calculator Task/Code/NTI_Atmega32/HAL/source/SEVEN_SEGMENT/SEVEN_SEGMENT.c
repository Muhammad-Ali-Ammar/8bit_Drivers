/**************************************************************************/
/* Filename						: SEVEN_SEGMENT.c                            */
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


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/

Seven_Segment_StatusErrorType  Seven_Segment_WriteBCDConnection(const Seven_Segment_BCDType* Address_Segment, u8 Copy_u8Value){

	Seven_Segment_StatusErrorType Loc_enuSegmentState = SEVEN_SEGMENT_STATUS_OK;
	Dio_ErrorStatusType Loc_enuDioState = DIO_STATUS_OK;
	    u8 Loc_u8FinalBit = DIO_LOW;
	    u8 Loc_u8Counter=ZERO_VALUE;

	    if (NULL == Address_Segment  ){

	    	Loc_enuSegmentState = SEVEN_SEGMENT_STATUS_NULL_POINTER_ADDRESS;
	    }

	    else{

	        for(Loc_u8Counter=ZERO_VALUE;Loc_u8Counter<4;Loc_u8Counter++){
	        	Loc_u8FinalBit = (Copy_u8Value>>Loc_u8Counter)& (ONE_VALUE);
	        	Loc_enuDioState= Dio_enuWriteChannel(Address_Segment->seven_segment_pins[Loc_u8Counter], Loc_u8FinalBit );
	        }
	    }

	    return Loc_enuSegmentState;

}
