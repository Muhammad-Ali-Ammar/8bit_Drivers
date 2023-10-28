/* 
 * File:   mcal_timer2.c
 * Author: isammar93
 *
 * Created on 04 ?????, 2023, 03:12 ?
 */


#include "mcal_timer2.h"

#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*Timer2_InterruptHandler)( void);
    static uint8 g_init_timer2_value =0;
#endif

static Std_ReturnType Timer2_ConfigureInterrupt(const Timer2_ConfigType* _timer2);

Std_ReturnType Timer2_Init(const Timer2_ConfigType* _timer2){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer2){
        ret = E_NOT_OK;
    }
    else{
        /* Disable Timer2 Peripheral */
        Timer2_Disable();
        

        /* Configure Prescaler*/
        Timer2_SetPrescalerValue(_timer2->prescaler_value);
        
        /* Configure Postscaler*/
        Timer2_SetPostscalerValue(_timer2->postscaler_value);
        

       /* Interrupt Configuration */
        ret &= Timer2_ConfigureInterrupt(_timer2);
        
        /* Update Init Value*/
        ret &= Timer2_SetValue(_timer2,_timer2->init_value);
        
        /* Enable Timer2 Peripheral */
        Timer2_Enable();
    }
    
    return ret; 
}

Std_ReturnType Timer2_DeInit(const Timer2_ConfigType* _timer2){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer2){
        ret = E_NOT_OK;
    }
    else{
        Timer2_Disable();
 #if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer2_DisableInterrupt();
#endif
    }
    
    return ret; 
}

Std_ReturnType Timer2_SetValue(const Timer2_ConfigType* _timer2, uint8 _value){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer2){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = _value;
    }
    
    return ret; 
}

Std_ReturnType Timer2_GetTimeElapsed(const Timer2_ConfigType* _timer2, uint8* _value){
    
    Std_ReturnType ret = E_OK;
    if((NULL == _timer2) ||(NULL == _value) ){
        ret = E_NOT_OK;
    }
    else{
        *_value = TMR2;
    }
    
    return ret; 
}

Std_ReturnType Timer2_GetRemaining(const Timer2_ConfigType* _timer2, uint8* _value){
    
    Std_ReturnType ret = E_OK;
    uint8 l_total = _timer2->init_value; 
    if((NULL == _timer2) ||(NULL == _value) ){
        ret = E_NOT_OK;
    }
    else{
        
        *_value =  (l_total - TMR2);
    }
    
    return ret; 
}
 #if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Timer2_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Timer2_ClearFlag();
     TMR2 = g_init_timer2_value;
    
    if(NULL != Timer2_InterruptHandler){
        Timer2_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}
#endif

////////////////////////////// Helper Functions //////////////////////////////////////////

static Std_ReturnType Timer2_ConfigureInterrupt(const Timer2_ConfigType* _timer2){
     Std_ReturnType ret = E_OK;
    if(NULL == _timer2 ){
        
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Timer2_InterruptHandler = _timer2->Timer2_InterruptHandler;
        Timer2_EnableInterrupt();
        g_init_timer2_value = _timer2->init_value;
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Timer2_SetPrioirty(_timer2->priority);
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