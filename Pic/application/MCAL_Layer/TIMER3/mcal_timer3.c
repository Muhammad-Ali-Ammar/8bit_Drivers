/* 
 * File:   mcal_timer3.c
 * Author: isammar93
 *
 * Created on 04 ?????, 2023, 03:12 ?
 */


#include "mcal_timer3.h"

#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*Timer3_InterruptHandler)( void);
    static uint16 g_init_timer3_value =0;
#endif
    
static Std_ReturnType Timer3_ConfigureClockSource(const Timer3_ConfigType* _timer3);
static Std_ReturnType Timer3_ConfigurePrescaler(const Timer3_ConfigType* _timer3);
static Std_ReturnType Timer3_ConfigureInterrupt(const Timer3_ConfigType* _timer3);

Std_ReturnType Timer3_Init(const Timer3_ConfigType* _timer3){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer3){
        ret = E_NOT_OK;
    }
    else{
        /* Disable Timer3 Peripheral */
        Timer3_Disable();
        
        /* configure clock source of timer */
        ret &= Timer3_ConfigureClockSource(_timer3);
        
        /* Configure Prescaler*/
        Timer3_SetPrescalerValue(_timer3->prescaler_value);
        
        /* enable 16 bit instruction operation*/
        Timer3_EnableWR16Operation();
        
        
       /* Interrupt Configuration */
        ret &= Timer3_ConfigureInterrupt(_timer3);
        
        /* Update Init Value*/
        ret &= Timer3_SetValue(_timer3,_timer3->init_value);
        
        /* Enable Timer3 Peripheral */
        Timer3_Enable();
        
        
    }
    
    return ret; 
}



Std_ReturnType Timer3_DeInit(const Timer3_ConfigType* _timer3){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer3){
        ret = E_NOT_OK;
    }
    else{
        Timer3_Disable();
 #if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer3_DisableInterrupt();
#endif
    }
    
    return ret; 
}

Std_ReturnType Timer3_SetValue(const Timer3_ConfigType* _timer3, uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer3){
        ret = E_NOT_OK;
    }
    else{
        
        TMR3 = _value;
    }
    
    return ret; 
}

Std_ReturnType Timer3_GetTimeElapsed(const Timer3_ConfigType* _timer3, uint16* _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer3 || NULL == _value ){
        ret = E_NOT_OK;
    }
    else{
        
        *_value = TMR3  ;
    }
    
    return ret;
}

Std_ReturnType Timer3_GetRemaining(const Timer3_ConfigType* _timer3, uint16* _value){
    Std_ReturnType ret = E_OK;
    uint16 l_total = 65535;
    if(NULL == _timer3 || NULL == _value ){
        ret = E_NOT_OK;
    }
    else{
        
        *_value = l_total - TMR3 ;
    }
    
    return ret;
}





 #if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Timer3_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Timer3_ClearFlag();
    TMR3 = g_init_timer3_value;
    
    if(NULL != Timer3_InterruptHandler){
        Timer3_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}
#endif




//////////////////////////////////////////
static Std_ReturnType Timer3_ConfigureClockSource(const Timer3_ConfigType* _timer3){
        Std_ReturnType ret = E_OK;
    Dio_PinConfigType l_T13CKI ={
                .direction = DIO_DIRECTION_INPUT,
                .logic = DIO_LOW,
                .port = DIO_PORTC_INDEX,
                .pin = DIO_PIN0
                         };
    Dio_PinConfigType l_T1OSI ={
                .direction = DIO_DIRECTION_INPUT,
                .logic = DIO_LOW,
                .port = DIO_PORTC_INDEX,
                .pin = DIO_PIN1 };
    
    if(NULL == _timer3){
        ret = E_NOT_OK;
    }
    else{
        
        switch(_timer3->source_type){
            
            case TIMER3_SOURCE_TIMER_MODE_WITH_INTERNAL_OSCILLIATOR:
                Timer3_SetClockSource(TIMER3_TIMER_MODE_WITH_INTERNAL_OSCILLATOR);
                break;
                
            case TIMER3_SOURCE_TIMER_MODE_WITH_TIMER1_OSCILLIATOR:
                Timer3_EnableSyncWithTimer1Oscillator();
                Timer3_SetClockSource(TIMER3_COUNTER_MODE_AND_TIMER1_OSCILLATOR);
                ret &= Dio_InitChannelDirection(&l_T13CKI);
                ret &= Dio_InitChannelDirection(&l_T1OSI);
                break;
                
            case TIMER3_SOURCE_COUNTER_MODE_SYNC_WITH_TIMER_OSCILLIATOR:
                Timer3_EnableSyncWithTimer1Oscillator();
                Timer3_SetClockSource(TIMER3_COUNTER_MODE_AND_TIMER1_OSCILLATOR);
                ret &= Dio_InitChannelDirection(&l_T13CKI);
                
                break;
                
            case TIMER3_SOURCE_COUNTER_MODE_ASYNC:
                Timer3_DisableSyncWithTimer1Oscillator();
                Timer3_SetClockSource(TIMER3_COUNTER_MODE_AND_TIMER1_OSCILLATOR);
                ret &= Dio_InitChannelDirection(&l_T13CKI);
                break;
                
            default :
               
                ret = E_NOT_OK;
        }
    }
    
    return ret; 
}

static Std_ReturnType Timer3_ConfigureInterrupt(const Timer3_ConfigType* _timer3){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer3 ){
        
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer3_InterruptHandler = _timer3->Timer3_InterruptHandler;
        Timer3_EnableInterrupt();
        g_init_timer3_value = _timer3->init_value;
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Timer3_SetPrioirty(_timer3->priority);
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