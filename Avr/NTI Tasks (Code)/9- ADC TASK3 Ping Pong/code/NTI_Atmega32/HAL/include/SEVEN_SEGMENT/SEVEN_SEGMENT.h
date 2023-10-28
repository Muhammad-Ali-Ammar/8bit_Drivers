/**************************************************************************/
/* Filename						: SEVEN_SEGMENT.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef HAL_INCLUDE_SEVEN_SEGMENT_SEVEN_SEGMENT_H_
#define HAL_INCLUDE_SEVEN_SEGMENT_SEVEN_SEGMENT_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
typedef enum{
    SEVEN_SEGMENT_CONNECTION_COMMON_ANODE,
    SEVEN_SEGMENT_CONNECTION_COMMON_CATHOD
}Seven_Segment_ConnectionType;


typedef struct{
    u8            seven_segment_pins[4];
}Seven_Segment_BCDType;



typedef enum{
    SEVEN_SEGMENT_STATUS_OK,
	SEVEN_SEGMENT_STATUS_FAIL,
	SEVEN_SEGMENT_STATUS_NULL_POINTER_ADDRESS,
}Seven_Segment_StatusErrorType;


/********************************** Software Interfaces Declarations *******************/
Seven_Segment_StatusErrorType  Seven_Segment_WriteBCDConnection(const Seven_Segment_BCDType* Address_Segment, u8 Copy_u8Value);

#endif /* HAL_INCLUDE_SEVEN_SEGMENT_SEVEN_SEGMENT_H_ */
