/* 
 * File:   ecu_seven_segment.h
 * Author: isammar93
 *
 * Created on 29 ?????, 2023, 07:36 ?
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H


/********************************** Includes *****************************************/

#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include"ecu_seven_segment_cfg.h"

/********************************** Macros Declarations *******************************/

/* Normal Seven Segment */
#define SEVEN_SEGMENT_NORMAL_A_IDX     0
#define SEVEN_SEGMENT_NORMAL_B_IDX     1
#define SEVEN_SEGMENT_NORMAL_C_IDX     2
#define SEVEN_SEGMENT_NORMAL_D_IDX     3
#define SEVEN_SEGMENT_NORMAL_E_IDX     4
#define SEVEN_SEGMENT_NORMAL_F_IDX     5
#define SEVEN_SEGMENT_NORMAL_G_IDX     6

#define SEVEN_SEGMENT_NORMAL_DP_IDX     7

#define SEVEN_SEGMENT_NORMAL_PINS       8

#define SEVEN_SEGMENT_TURN_OFF_VALUE_CATHOD     ((uint8)0x00)

/*Seven  Segment With BCD  */
#define SEVEN_SEGMENT_BCD_A_IDX     0
#define SEVEN_SEGMENT_BCD_B_IDX     1
#define SEVEN_SEGMENT_BCD_C_IDX     2
#define SEVEN_SEGMENT_BCD_D_IDX     3


#define SEVEN_SEGMENT_BCD_DP_IDX    4

#define SEVEN_SEGMENT_BCD_PINS       5

/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/
typedef enum{
    SEVEN_SEGMENT_COMMON_ANODE,
    SEVEN_SEGMENT_COMMON_CATHOD
}Seven_Segment_ConnectionType;

typedef enum{
    SEVEN_SEGMENT_OFF,
    SEVEN_SEGMENT_ON,
            
}Seven_Segment_StatusType;


typedef enum{
    SEVEN_SEGMENT_DP_OFF,
    SEVEN_SEGMENT_DP_ON,
            
}Seven_Segment_DecimalPointIsUsedType;



typedef struct{
    
    Dio_PinConfigType            seven_segment_pins[SEVEN_SEGMENT_NORMAL_PINS];
    Seven_Segment_ConnectionType seven_segment_connection;
    Seven_Segment_StatusType     seven_segment_state;
    Seven_Segment_DecimalPointIsUsedType    seven_segment_dp_is_used;
    
}Seven_Segment_NormalType;


typedef struct{
    Seven_Segment_ConnectionType seven_segment_connection;
    Seven_Segment_StatusType     seven_segment_state;
    Dio_PinConfigType            seven_segment_pins[SEVEN_SEGMENT_BCD_PINS];
    Seven_Segment_DecimalPointIsUsedType    seven_segment_dp_is_used;

}Seven_Segment_BCDType;

/********************************** Software Interfaces Declarations *******************************/

/*For normal Seven Segment */

Std_ReturnType  Seven_Segment_InitNormalConnection(const Seven_Segment_NormalType* _seven_segment);
Std_ReturnType  Seven_Segment_WriteNormalConnection(const Seven_Segment_NormalType* _seven_segment, uint8 _value);

Std_ReturnType  Seven_Segment_TurnOffNormalConnection(const Seven_Segment_NormalType* _seven_segment);


Std_ReturnType  Seven_Segment_TurnOnDecimalPointNormalConnection(const Seven_Segment_NormalType* _seven_segment);
Std_ReturnType  Seven_Segment_TurnOffDecimalPointNormalConnection(const Seven_Segment_NormalType* _seven_segment);


/* for bcd seven segment decoder */

Std_ReturnType  Seven_Segment_InitBCDConnection(const Seven_Segment_BCDType* _seven_segment);
Std_ReturnType  Seven_Segment_WriteBCDConnection(const Seven_Segment_BCDType* _seven_segment, uint8 _value);

Std_ReturnType  Seven_Segment_TurnOffBCDConnection(const Seven_Segment_BCDType* _seven_segment);


Std_ReturnType  Seven_Segment_TurnOnDecimalPointBCDConnection(const Seven_Segment_BCDType* _seven_segment);
Std_ReturnType  Seven_Segment_TurnOffDecimalPointBCDConnection(const Seven_Segment_BCDType* _seven_segment);



#endif	/* ECU_SEVEN_SEGMENT_H */

