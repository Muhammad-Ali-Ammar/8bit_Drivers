/* 
 * File:   ecu_relay.c
 * Author: Ammar
 *
 * Created on 28 1 2022, 10:40 ?
 */


#include "ecu_relay.h"

Std_ReturnType Relay_Init(const Relay_ConfigType* _relay){
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _relay  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret = Dio_InitChannel(&(_relay->relay_pin));
        
        ret &= Dio_WriteChannel(&(_relay->relay_pin),(Dio_LogicPinType) _relay->relay_state );
        
    }


    return ret;
}

Std_ReturnType Relay_TurnOn(const Relay_ConfigType* _relay){
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _relay  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret = Dio_WriteChannel(&(_relay->relay_pin), DIO_HIGH );
    }


    return ret;
}

Std_ReturnType Relay_TurnOff(const Relay_ConfigType* _relay){
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _relay  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret = Dio_WriteChannel(&(_relay->relay_pin), DIO_LOW );
    }


    return ret;
    
}