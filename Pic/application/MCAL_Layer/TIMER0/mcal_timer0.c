/* 
 * File:   mcal_timer0.c
 * Author: isammar93
 *
 * Created on 04 ?????, 2023, 03:12 ?
 */


#include "mcal_timer0.h"

#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*Timer0_InterruptHandler)( void);
    static uint16 g_init_timer0_value =0;
#endif

        

static Std_ReturnType Timer0_ConfigurePrescaler(const Timer0_ConfigType* _timer0);
static Std_ReturnType Timer0_ConfigureClockSource(const Timer0_ConfigType* _timer0);
static Std_ReturnType Timer0_ConfigureInterrupt(const Timer0_ConfigType* _timer0);

Std_ReturnType Timer0_Init(const Timer0_ConfigType* _timer0){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        /* Disable Timer0 Peripheral */
        Timer0_Disable();
        
        /* configure clock source of timer */
        ret &= Timer0_ConfigureClockSource(_timer0);
        
        /* Configure Prescaler*/
        ret &= Timer0_ConfigurePrescaler(_timer0);
        
        /* Configure Resolution Bit*/
        Timer0_SetRegisterResolution(_timer0->resolution_bits);
        
       /* Interrupt Configuration */
        ret &= Timer0_ConfigureInterrupt(_timer0);
        
        /* Update Init Value*/
        ret &= Timer0_SetValue(_timer0,_timer0->init_value);
        
        /* Enable Timer0 Peripheral */
        Timer0_Enable();
        
        
    }
    
    return ret; 
}
Std_ReturnType Timer0_DeInit(const Timer0_ConfigType* _timer0){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        Timer0_Disable();
 #if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer0_DisableInterrupt();
#endif
    }
    
    return ret; 
}

Std_ReturnType Timer0_SetValue(const Timer0_ConfigType* _timer0, uint16 _value){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        
        switch(_timer0->resolution_bits){
            case TIMER0_RESOLUTION_16_BIT :
                TMR0H = ((uint8)(_value>>8)) & 0xFF;
                TMR0L = ((uint8)(_value)) & 0xFF;
                break;
                
            default:
                 TMR0L = ((uint8)(_value)) & 0xFF;
                
        }
    }
    
    return ret; 
}
Std_ReturnType Timer0_GetTimeElapsed(const Timer0_ConfigType* _timer0, uint16* _value){
    
    Std_ReturnType ret = E_OK;
    uint16 l_result;

    if(NULL == _timer0 || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        switch(_timer0->resolution_bits){
            case TIMER0_RESOLUTION_16_BIT :
                l_result =  (uint16)TMR0L ;
                l_result |= ((uint16)(TMR0H))<<8;
                break;
                
            default:
               l_result =  TMR0L ;
                
        }
        *_value = l_result;
    }
    
    return ret; 
}

Std_ReturnType Timer0_GetRemaining(const Timer0_ConfigType* _timer0, uint16* _value){
    
     Std_ReturnType ret = E_OK;
    uint16 l_result;
    uint16 l_total ;

    if(NULL == _timer0 || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        switch(_timer0->resolution_bits){
            case TIMER0_RESOLUTION_16_BIT :
                l_result =  TMR0L ;
                l_result |= ((uint16)(TMR0H))<<8;
                l_total = 65535;
                break;
                
            default:
               l_result =  TMR0L ;
               l_total = 256;
                
        }
        *_value = l_total - l_result;
    }
    
    return ret; 
}

 #if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Timer0_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Timer0_ClearFlag();
     TMR0H = ((uint8)(g_init_timer0_value>>8)) & 0xFF;
     TMR0L = ((uint8)(g_init_timer0_value)) & 0xFF;
    
    if(NULL != Timer0_InterruptHandler){
        Timer0_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}
#endif

/* Helper Functions */
static Std_ReturnType Timer0_ConfigurePrescaler(const Timer0_ConfigType* _timer0){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        
        switch(_timer0->prescaler_value){
            
            case TIMER0_PRESCALER_NO_DIV :
                Timer0_SetPrescalerState(TiMER0_DISABLE_PRESCALER);
                break;
                
            default :
                Timer0_SetPrescalerState(TiMER0_ENABLE_PRESCALER);
                Timer0_SetPrescalerValue(_timer0->prescaler_value);
        }
    }
    
    return ret; 
    
}

static Std_ReturnType Timer0_ConfigureClockSource(const Timer0_ConfigType* _timer0){
    Std_ReturnType ret = E_OK;
    Dio_PinConfigType l_counter_pin ={
                .direction = DIO_DIRECTION_INPUT,
                .logic = DIO_LOW,
                .port = DIO_PORTA_INDEX,
                .pin = DIO_PIN4
                         };
    
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }
    else{
        
        switch(_timer0->source_type){
            
            case TIMER0_SOURCE_COUNTER_MODE_RAISING_EDGE :
            case TIMER0_SOURCE_COUNTER_MODE_FAILING_EDGE :
                Timer0_SetClockSource(TIMER0_COUNTER_MODE);
                Timer0_SetEdgeSelect(_timer0->source_type);
                ret &= Dio_InitChannelDirection(&(l_counter_pin));
                break;
                
            default :
                Timer0_SetClockSource(TIMER0_TIMER_MODE);
        }
    }
    
    return ret; 
}

static Std_ReturnType Timer0_ConfigureInterrupt(const Timer0_ConfigType* _timer0){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0 ){
        
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer0_InterruptHandler = _timer0->Timer0_InterruptHandler;
        Timer0_EnableInterrupt();
        g_init_timer0_value = _timer0->init_value;
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Timer0_SetPrioirty(_timer0->priority);
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