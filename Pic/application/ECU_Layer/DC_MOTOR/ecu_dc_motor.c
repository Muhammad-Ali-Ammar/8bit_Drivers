/* 
 * File:   dc_motor.c
 * Author: Ammar
 *
 * Created on 29 1 2023, 10:40 ?
 */

#include "ecu_dc_motor.h"


Std_ReturnType Dc_Motor_Init(const Dc_Motor_ConfigPins* _dc_motor){
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _dc_motor  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        /*make direction pins 1,2 output */
        ret = Dio_InitChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN1_IDX]));
        ret &= Dio_InitChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN2_IDX]));
        
        ret &= Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN1_IDX]),(Dio_LogicPinType)_dc_motor->dc_motor_pin_status[DC_MOTOR_IN1_IDX] );
        ret &= Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN2_IDX]),(Dio_LogicPinType)_dc_motor->dc_motor_pin_status[DC_MOTOR_IN2_IDX] );
        
    }


    return ret;
}

Std_ReturnType Dc_Motor_MoveForward(const Dc_Motor_ConfigPins* _dc_motor){
    
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _dc_motor  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        
        ret = Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN1_IDX]),DIO_HIGH);
        ret &= Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN2_IDX]),DIO_LOW );
        
    }


    return ret;
}

Std_ReturnType Dc_Motor_MoveBackward(const Dc_Motor_ConfigPins* _dc_motor){
    
    
    Std_ReturnType ret = E_OK;
    
    if (NULL == _dc_motor  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        
        ret = Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN1_IDX]),DIO_LOW);
        ret &= Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN2_IDX]),DIO_HIGH );
        
    }


    return ret;
}
Std_ReturnType Dc_Motor_Stop(const Dc_Motor_ConfigPins* _dc_motor){
    
    
    Std_ReturnType ret = E_OK;
    
    if (NULL == _dc_motor  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        
        ret = Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN1_IDX]),DIO_LOW);
        ret &= Dio_WriteChannel(&(_dc_motor->dc_motor_pin[DC_MOTOR_IN2_IDX]),DIO_LOW );
        
    }


    return ret;
}



