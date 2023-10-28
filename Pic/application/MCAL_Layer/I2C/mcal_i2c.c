/* 
 * File:   I2C.c
 * Author: Muhammad Ammar
 *
 * Created on 24 ?????, 2023, 11:14 ?
 */



/********************************** Includes *****************************************/
#include "mcal_i2c.h"

/********************************** Private  definition  and declaration  *****************************************/

#if INTERRUPT_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*I2c_InterruptHandler)( void);
    static void (*I2cReceiveOverflow_InterruptHandler)( void);
#endif

#if INTERRUPT_I2C_WRITE_COLLISION_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*I2cWriteCollision_InterruptHandler)( void);
#endif

static Std_ReturnType I2c_ConfigMasterSlaveMode(const I2c_ConfigType* _i2c);
static Std_ReturnType I2c_ConfigureInterrupt(const I2c_ConfigType* _i2c);

/********************************** Public Function Implementation  *****************************************/

Std_ReturnType I2c_Init(const I2c_ConfigType* _i2c){
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c){
        ret = E_NOT_OK;
    }
    else{
        I2c_Disable();
         
        ret &= I2c_ConfigMasterSlaveMode(_i2c);
        
        /* configure slew rate */
        I2c_SelectSlewRate(_i2c->slew_rate);
        
        /* configure  SMBUS */
        I2c_SelectSMBus(_i2c->SMBus_config);
        
        /* configure Interrupt*/
        ret &= I2c_ConfigureInterrupt(_i2c);
        
        I2c_Enable();
    }
    
    
    return ret;
}

Std_ReturnType I2c_DeInit(const I2c_ConfigType* _i2c){
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c){
        ret = E_NOT_OK;
    }
    else{
        I2c_Disable();
#if INTERRUPT_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
I2c_DisableInterrupt();
#endif
        
#if INTERRUPT_I2C__WRITE_COLLISION_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
I2cWriteCollision_DisableInterrupt();
#endif


    }
    
    
    return ret;
}

Std_ReturnType I2c_MasterTransmitStartConditionBlocking(const I2c_ConfigType* _i2c){
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c){
        ret = E_NOT_OK;
    }
    else{
        I2c_TransmitStartMasterMode();
        while( I2c_IsTransmitStartCompletedMasterMode() == I2C_FALSE);
        I2c_ClearFlagBit();
        if(I2c_IsStartBitDetected() != I2C_TRUE){
            
            ret = E_NOT_OK;
        }
        else { /*  nothing */ }
    }
    
    
    return ret;
}
Std_ReturnType I2c_MasterTransmitStopConditionBlocking(const I2c_ConfigType* _i2c){
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c){
        ret = E_NOT_OK;
    }
    else{
        I2c_TransmitStopMasterMode();
        while( I2c_IsTransmitStopCompletedMasterMode() == I2C_FALSE);
        I2c_ClearFlagBit();
        if(I2c_IsStopBitDetected() != I2C_TRUE){
            
            ret = E_NOT_OK;
        }
        else { /*  nothing */ }
    }
    
    
    return ret;
}
Std_ReturnType I2c_MasterTransmitRepeatedStartConditionBlocking(const I2c_ConfigType* _i2c){
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c){
        ret = E_NOT_OK;
    }
    else{
       I2c_TransmitRepeatedStartMasterMode();
        while( I2c_IsTransmitRepeatedStartCompletedMasterMode() == I2C_FALSE);
        I2c_ClearFlagBit();
        
    }
    
    
    return ret;
}


Std_ReturnType I2c_MasterTransmitDataBlocking(const I2c_ConfigType* _i2c, uint8 _data, uint8* _ack_received){
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c || NULL == _ack_received){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = _data;
        
        while(I2c_IsTransmitDataCompletedMasterMode()  == I2C_FALSE);
        I2c_ClearFlagBit(); 
        * _ack_received = I2c_IsAckReceivedFromSlave_MasterTransmitMode();
        
    }
    
    
    return ret;
}
Std_ReturnType I2c_MasterReceiveDataBlocking(const I2c_ConfigType* _i2c, uint8* _data, uint8 _send_ack){
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c || NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        
        I2c_EnableReceiveMasterMode();
        while(I2c_IsReceiveDataCompleted_MasterMode() == I2C_FALSE);
        *_data = SSPBUF;
        I2c_TransmitAckMasterReceiveMode(_send_ack);
        I2c_DisableReceiveMasterMode();
    }
    
    
    return ret;
}

Std_ReturnType I2c_MasterTransmitFrame_WriteBlocking(const I2c_ConfigType* _i2c,uint8 _slave_address_7bit, uint8 _data, uint8* _ack_received){

    Std_ReturnType ret = E_OK;
    if(NULL == _i2c || NULL == _ack_received){
        ret = E_NOT_OK;
    }
    else{
        
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)(_slave_address_7bit<<1), _ack_received);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,_data, _ack_received);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
        
    }
    
    return ret;
}

//Std_ReturnType I2c_SlaveReceiveDataNonBlocking(const I2c_ConfigType* _i2c){
//    Std_ReturnType ret = E_OK;
//    if(NULL == _i2c ){
//        ret = E_NOT_OK;
//    }
//    else{
//        I2c_EnableInterrupt();
//    }
//}

Std_ReturnType I2c_MasterTransmitFrame_Receivelocking(const I2c_ConfigType* _i2c,uint8 _slave_address_7bit, 
                                    uint8* _data, uint8* _ack_received_for_slave_address,uint8 _ack_send ){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c || NULL == _data || NULL == _ack_received_for_slave_address){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (_slave_address_7bit<<1)|1 ), _ack_received_for_slave_address);
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _data, _ack_send);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    return ret;
}

/********************************** Private Function Implementation  *****************************************/

static Std_ReturnType I2c_ConfigMasterSlaveMode(const I2c_ConfigType* _i2c){
   Std_ReturnType ret = E_OK;
   Dio_PinConfigType l_scl_pin ={
                .direction = DIO_DIRECTION_INPUT,
                .logic = DIO_HIGH,
                .port = DIO_PORTC_INDEX,
                .pin = DIO_PIN3
                         };
    Dio_PinConfigType l_sda_pin ={
                .direction = DIO_DIRECTION_INPUT,
                .logic = DIO_HIGH,
                .port = DIO_PORTC_INDEX,
                .pin = DIO_PIN4 };
    if(NULL == _i2c){
        ret = E_NOT_OK;
    }
    else{
        
        I2c_SelectMasterSlave( (uint8)(_i2c->master_slave_config));
        switch(_i2c->master_slave_config){
            
            case I2C_SLAVE_MODE_7BIT_ADDRESS :
            case I2C_SLAVE_MODE_10BIT_ADDRESS :
            case I2C_SLAVE_MODE_7BIT_ADDRESS_START_STOP_ENABLE :
            case I2C_SLAVE_MODE_10BIT_ADDRESS_START_STOP_ENABLE :
                
             I2c_SelectGeneralCallWithInterruptSlaveMode(_i2c->slave_mode_general_call_config);
             I2c_SelectClockStretchSlaveMode(_i2c->slave_mode_clock_stretch_config);
             I2c_ClearWriteCollisionSlaveMode();
             I2c_ClearReceieveOverflow();
             I2c_RelaseClockSlaveMode();
             SSPADD = (uint8)((_i2c->slave_address_7bit)<<1);
                break;
                
            case I2C_MASTER_MODE :
                SSPADD = (uint8) ((_XTAL_FREQ/ (4.0*_i2c->master_mode_clock))-1);
                break;
                
            case I2C_MASTER_MODE_MANUAL_SW_CONTROLLED :
                /* Do Nothing*/
                 break;
                 
            default :
                ret = E_NOT_OK;
                break;
                       
        }
        
        ret &= Dio_InitChannelDirection(&l_scl_pin);
        ret &= Dio_InitChannelDirection(&l_sda_pin);
    }
    
    
    return ret; 
}


static Std_ReturnType I2c_ConfigureInterrupt(const I2c_ConfigType* _i2c){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _i2c ){
        ret = E_NOT_OK;
    }
    else{
#if INTERRUPT_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        I2c_InterruptHandler = _i2c->I2c_InterruptHandler;
        I2cReceiveOverflow_InterruptHandler = _i2c->I2cReceiveOverflow_InterruptHandler;
        I2c_EnableInterrupt();
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 I2c_SetPrioirty(_i2c->I2c_interrupt_priority);
                 Interrupt_EnablePrioirtyOfTheSystem();
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
    #else 
            Interrupt_EnableGlobalInterrupt();
            Interrupt_EnablePeripheralInterrupt();
    #endif
        
        
#endif  
            
 #if INTERRUPT_I2C_WRITE_COLLISION_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        I2cWriteCollision_InterruptHandler = _i2c->I2cWriteCollision_InterruptHandler;
        I2cWriteCollision_EnableInterrupt();
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 I2cWriteCollision_SetPrioirty(_i2c->I2cWriteCollision_interrupt_priority);
                 Interrupt_EnablePrioirtyOfTheSystem();
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
    #else 
            Interrupt_EnableGlobalInterrupt();
            Interrupt_EnablePeripheralInterrupt();
    #endif
        
        
#endif  
    }
    
    
    return ret;
}



 #if INTERRUPT_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void I2c_ISR(void){
    Std_ReturnType ret = E_OK;
    
    I2c_ClearFlag();
    
    if(NULL != I2c_InterruptHandler){
        I2c_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
    
    if( (I2c_IsReceiveOverflowDetected() == I2C_TRUE )&& (NULL != I2cReceiveOverflow_InterruptHandler) ) {
        I2cReceiveOverflow_InterruptHandler();
    }
    else {/* do nothing */ }
    
}

#endif

#if INTERRUPT_I2C_WRITE_COLLISION_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void I2cWriteCollision_ISR(void){
    Std_ReturnType ret = E_OK;
    
    I2cWriteCollision_ClearFlag();
    
    if(NULL != I2cWriteCollision_InterruptHandler){
        I2cWriteCollision_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}

#endif