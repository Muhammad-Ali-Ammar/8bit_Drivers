/* 
 * File:   ecu_dc_motor.h
 * Author: isammar93
 *
 * Created on 29 ?????, 2023, 01:31 ?
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


/********************************** Includes *****************************************/

#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/********************************** Macros Declarations *******************************/
#define DC_MOTOR_IN1_IDX    0
#define DC_MOTOR_IN2_IDX    1


#define DC_MOTOR_DIRECTION_CONTROL_PINS 2

/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/
typedef enum{
    DC_MOTOR_IN_OFF,
    DC_MOTOR_IN_ON
}Dc_Motor_StatusType;


typedef struct{
    Dio_PinConfigType dc_motor_pin[DC_MOTOR_DIRECTION_CONTROL_PINS];
    Dc_Motor_StatusType dc_motor_pin_status[DC_MOTOR_DIRECTION_CONTROL_PINS];
    
}Dc_Motor_ConfigPins;
/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Dc_Motor_Init(const Dc_Motor_ConfigPins* _dc_motor);
Std_ReturnType Dc_Motor_MoveForward(const Dc_Motor_ConfigPins* _dc_motor);
Std_ReturnType Dc_Motor_MoveBackward(const Dc_Motor_ConfigPins* _dc_motor);
Std_ReturnType Dc_Motor_Stop(const Dc_Motor_ConfigPins* _dc_motor);



#endif	/* ECU_DC_MOTOR_H */

