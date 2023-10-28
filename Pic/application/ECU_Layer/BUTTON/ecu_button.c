
/* 
 * File:   ecu_button.c
 * Author: Ammar
 *
 * Created on 26 1 2023, 01:29 ?
 */


#include "ecu_button.h"

Std_ReturnType Button_Init(const Button_ConfigType *_btn){
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _btn  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret = Dio_InitChannelDirection(&(_btn->button_pin));
    }


    return ret;
}

Std_ReturnType Button_Read(const Button_ConfigType *_btn,Button_StatusType* _state){
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _btn  || NULL == _state){

        ret = E_NOT_OK;
    } 
     
     else{
        switch(_btn->button_connection){
            
            case BUTTON_PULL_DOWN:
                ret = Dio_ReadChannel( &(_btn->button_pin), (Dio_LogicPinType*) _state);
                break;
            case BUTTON_PULL_UP:
                
                ret = Dio_ReadChannel( &(_btn->button_pin), (Dio_LogicPinType*) _state);
                *_state = !(*_state);
                break;
                
            default: 
                ret = E_NOT_OK;
        }
       
    }


    return ret;
}