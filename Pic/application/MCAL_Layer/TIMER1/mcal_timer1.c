/* 
 * File:   mcal_timer1.c
 * Author: isammar93
 *
 * Created on 04 ?????, 2023, 03:12 ?
 */


#include "mcal_timer1.h"

#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*Timer1_InterruptHandler)( void);
    static uint16 g_init_timer1_value =0;
#endif
    
static Std_ReturnType Timer1_ConfigureClockSource(const Timer1_ConfigType* _timer1);
static Std_ReturnType Timer1_ConfigurePrescaler(const Timer1_ConfigType* _timer1);
static Std_ReturnType Timer1_ConfigureInterrupt(const Timer1_ConfigType* _timer1);

    
Std_ReturnType Timer1_Init(const Timer1_ConfigType* _timer1){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer1){
        ret = E_NOT_OK;
    }
    else{
        /* Disable Timer1 Peripheral */
        Timer1_Disable();
        
        /* configure clock source of timer */
        ret &= Timer1_ConfigureClockSource(_timer1);
        
        /* Configure Prescaler*/
        Timer1_SetPrescalerValue(_timer1->prescaler_value);
        
        /* enable 16 bit instruction operation*/
        Timer1_EnableWR16Operation();
        
        
       /* Interrupt Configuration */
        ret &= Timer1_ConfigureInterrupt(_timer1);
        
        /* Update Init Value*/
        ret &= Timer1_SetValue(_timer1,_timer1->init_value);
        
        /* Enable Timer1 Peripheral */
        Timer1_Enable();
        
        
    }
    
    return ret; 
}

Std_ReturnType Timer1_DeInit(const Timer1_ConfigType* _timer1){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer1){
        ret = E_NOT_OK;
    }
    else{
        Timer1_Disable();
 #if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer1_DisableInterrupt();
#endif
    }
    
    return ret; 
}

Std_ReturnType Timer1_SetValue(const Timer1_ConfigType* _timer1, uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer1){
        ret = E_NOT_OK;
    }
    else{
        
        TMR1 = _value;
    }
    
    return ret; 
}
Std_ReturnType Timer1_GetTimeElapsed(const Timer1_ConfigType* _timer1, uint16* _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer1 || NULL == _value ){
        ret = E_NOT_OK;
    }
    else{
        
        *_value = TMR1  ;
    }
    
    return ret;
}

Std_ReturnType Timer1_GetRemaining(const Timer1_ConfigType* _timer1, uint16* _value){
    Std_ReturnType ret = E_OK;
    uint16 l_total = 65535;
    if(NULL == _timer1 || NULL == _value ){
        ret = E_NOT_OK;
    }
    else{
        
        *_value = l_total - TMR1 ;
    }
    
    return ret;
}

Std_ReturnType Timer1_ActivateTimer1Oscillator(void){
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
    
    
    Timer1_EnableTimer1Oscillator();
    ret &= Dio_InitChannelDirection(&l_T13CKI);
    ret &= Dio_InitChannelDirection(&l_T1OSI);
    
    return ret;
}

Std_ReturnType Timer1_DeactivateTimer1Oscillator(void){
    Std_ReturnType ret = E_OK;
    Timer1_DisableTimer1Oscillator();
    return ret;
}

    
 #if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Timer1_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Timer1_ClearFlag();
    TMR1 = g_init_timer1_value;
    
    if(NULL != Timer1_InterruptHandler){
        Timer1_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}
#endif




//////////////////////////////////////////
static Std_ReturnType Timer1_ConfigureClockSource(const Timer1_ConfigType* _timer1){
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
    
    if(NULL == _timer1){
        ret = E_NOT_OK;
    }
    else{
        
        switch(_timer1->source_type){
            
            case TIMER1_SOURCE_TIMER_MODE_WITH_INTERNAL_OSCILLIATOR:
                Timer1_SetClockSource(TIMER1_TIMER_MODE_WITH_INTERNAL_OSCILLATOR);
                break;
                
            case TIMER1_SOURCE_TIMER_MODE_WITH_TIMER1_OSCILLIATOR:
                Timer1_EnableSyncWithTimer1Oscillator();
                Timer1_SetClockSource(TIMER1_COUNTER_MODE_AND_TIMER1_OSCILLATOR);
                ret &= Dio_InitChannelDirection(&l_T13CKI);
                ret &= Dio_InitChannelDirection(&l_T1OSI);
                break;
                
            case TIMER1_SOURCE_COUNTER_MODE_SYNC_WITH_TIMER_OSCILLIATOR:
                Timer1_EnableSyncWithTimer1Oscillator();
                Timer1_SetClockSource(TIMER1_COUNTER_MODE_AND_TIMER1_OSCILLATOR);
                ret &= Dio_InitChannelDirection(&l_T13CKI);
                
                break;
                
            case TIMER1_SOURCE_COUNTER_MODE_ASYNC:
                Timer1_DisableSyncWithTimer1Oscillator();
                Timer1_SetClockSource(TIMER1_COUNTER_MODE_AND_TIMER1_OSCILLATOR);
                ret &= Dio_InitChannelDirection(&l_T13CKI);
                break;
                
            default :
               
                ret = E_NOT_OK;
        }
    }
    
    return ret; 
}

static Std_ReturnType Timer1_ConfigureInterrupt(const Timer1_ConfigType* _timer1){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer1 ){
        
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer1_InterruptHandler = _timer1->Timer1_InterruptHandler;
        Timer1_EnableInterrupt();
        g_init_timer1_value = _timer1->init_value;
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Timer1_SetPrioirty(_timer1->priority);
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