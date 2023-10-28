/* 
 * File:   mcal_ccp1.c
 * Author:  
 *
 * Created on 22 ?????, 2023, 07:51 ?
 */


/********************************** Includes *****************************************/

#include "mcal_ccp1.h"


/********************************** Private  defination and declaration  *****************************************/

#if CCP1_CFG_CAPTURE_MODE_SELECTED == CCP1_MODULE_ENABLE
    
static void (*Capture1_InterruptHandler)( void);
static Std_ReturnType Capture1_ConfigureInterrupt(const Capture1_ConfigType* _capture);
static Std_ReturnType Capture1_SetTimerSource(const Capture1_ConfigType* _capture);
static Dio_PinConfigType g_ccp1_pin ={
    .direction = DIO_DIRECTION_INPUT,
    .logic = DIO_LOW,
    .pin =DIO_PIN2,
    .port = DIO_PORTC_INDEX
};


#elif CCP1_CFG_COMPARE_MODE_SELECTED == CCP1_MODULE_ENABLE


static void (*Compare1_InterruptHandler)( void);
static Std_ReturnType Compare1_ConfigureInterrupt(const Compare1_ConfigType* _compare);
static Std_ReturnType Compare1_SetTimerSource(const Compare1_ConfigType* _compare);

static Dio_PinConfigType g_ccp1_pin ={
    .direction = DIO_DIRECTION_OUTPUT,
    .logic = DIO_LOW,
    .pin =DIO_PIN2,
    .port = DIO_PORTC_INDEX
};

#elif CCP1_CFG_PWM_MODE_SELECTED == CCP1_MODULE_ENABLE

static Dio_PinConfigType g_ccp1_pin ={
    .direction = DIO_DIRECTION_OUTPUT,
    .logic = DIO_LOW,
    .pin =DIO_PIN2,
    .port = DIO_PORTC_INDEX
};

static Std_ReturnType Pwm1_SetFrequancy(const Pwm1_ConfigType* _pwm);

#else 

#endif 

/********************************** Public Function Implementation  *****************************************/

#if CCP1_CFG_CAPTURE_MODE_SELECTED == CCP1_MODULE_ENABLE

Std_ReturnType Capture1_Init(const Capture1_ConfigType* _capture){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture){
        ret = E_NOT_OK;
    }
    else{
        /* Disable perihperal first */
        CAPTURE1_SET_EDGE(CAPTURE1_EDGE_DISABLE_MODULE);
        
        /* Configure pin as INPUT */
        ret &= Dio_InitChannelDirection(&g_ccp1_pin);
        
        /* Configure Timer Source*/
        ret &= Capture1_SetTimerSource(_capture);
        /* Configure The interrupt*/
        ret &=Capture1_ConfigureInterrupt(_capture);
        
        
        /* Set Mode */
        CAPTURE1_SET_EDGE(_capture->edge);
    }
    
    return ret;
}

Std_ReturnType Capture1_DeInit(const Capture1_ConfigType* _capture){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture){
        ret = E_NOT_OK;
    }
    else{
        /* Disable perihperal first */
        CAPTURE1_SET_EDGE(CAPTURE1_EDGE_DISABLE_MODULE);
        
#if INTERRUPT_CAPTURE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Capture1_DisableInterrupt();
#endif
    }
    
    return ret;
}

Std_ReturnType Capture1_GetValue(const Capture1_ConfigType* _capture, uint16* _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        
        *_value = CCPR1;
    }
    
    return ret;
}

Std_ReturnType Capture1_ChangeEdge(const Capture1_ConfigType* _capture, Capture1_EdgeType _edge){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture ){
        ret = E_NOT_OK;
    }
    else{
        
        CAPTURE1_SET_EDGE(_edge);
        Capture1_ClearFlag();

    }
    
    return ret;
}



///////////////////////// COMPARE MODE ////////////////////////////////

#elif CCP1_CFG_COMPARE_MODE_SELECTED == CCP1_MODULE_ENABLE


Std_ReturnType Compare1_Init(const Compare1_ConfigType* _compare){
    Std_ReturnType ret = E_OK;
    if(NULL == _compare){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable */
        COMPARE1_SET_MODE(COMPARE1_MODE_DISABLE);
        
        /* Configure pin as output*/
        ret &= Dio_InitChannel(&g_ccp1_pin);
        
        /* Configure Interrupt */
        ret &= Compare1_ConfigureInterrupt(_compare);
        
        
        
        /* set mode */
        COMPARE1_SET_MODE(_compare->mode);
    }
    
    return ret;
}
Std_ReturnType Compare1_DeInit(const Compare1_ConfigType* _compare){
    Std_ReturnType ret = E_OK;
    if(NULL == _compare){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable perihperal first */
        COMPARE1_SET_MODE(COMPARE1_MODE_DISABLE);
        
#if INTERRUPT_COMPARE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Compare1_DisableInterrupt();
#endif
    }
    
    return ret;
}
Std_ReturnType Compare1_SetValue(const Compare1_ConfigType* _compare, uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _compare) {
        ret = E_NOT_OK;
    }
    else{
        
        CCPR1 = _value;
    }
    
    return ret;
}

#elif CCP1_CFG_PWM_MODE_SELECTED == CCP1_MODULE_ENABLE


Std_ReturnType Pwm1_Init(const Pwm1_ConfigType* _pwm){
    Std_ReturnType ret = E_OK;
    if(NULL == _pwm){
        ret = E_NOT_OK;
    }
    else{
        /* Disable Peripheral  */
        PWM1_DISABLE();
        
        /* Configure pin as output*/
        ret &= Dio_InitChannel(&g_ccp1_pin);
        
        /* SetFrequancy/ Period   */
        ret &= Pwm1_SetFrequancy( _pwm);
        
        /* Enable Peripheral  */
        PWM1_ENABLE();
    }
    
    return ret;
}

Std_ReturnType Pwm1_DeInit(const Pwm1_ConfigType* _pwm){
    Std_ReturnType ret = E_OK;
    if(NULL == _pwm){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable Peripheral  */
        PWM1_DISABLE();
    }
    
    return ret;
}

Std_ReturnType Pwm1_SetDutyCycle(const Pwm1_ConfigType* _pwm, uint8 _duty_cycle_precentage){
    Std_ReturnType ret = E_OK;
    uint16 l_pwm1_10bit = ZERO_VALUE;
    if(NULL == _pwm){
        ret = E_NOT_OK;
    }
    else {
        
     l_pwm1_10bit = (uint16) ((PR2+1)*4*(_duty_cycle_precentage/100.0));
     CCP1CONbits.DC1B = (l_pwm1_10bit &0x0003);
     CCPR1L = (uint8)(l_pwm1_10bit>>2);
     
    }
    
    
    return ret;
}


Std_ReturnType Pwm1_Stop(const Pwm1_ConfigType* _pwm){
    
    Std_ReturnType ret = E_OK;
   
    ret &= Pwm1_SetDutyCycle(_pwm,0);
    
    
    return ret;
}


#else 

#endif 

/********************************** Private Function Implementation  *****************************************/

#if CCP1_CFG_CAPTURE_MODE_SELECTED == CCP1_MODULE_ENABLE

static Std_ReturnType Capture1_SetTimerSource(const Capture1_ConfigType* _capture){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture ){
        ret = E_NOT_OK;
    }
    else{
        
        T3CONbits.T3CCP1 = (_capture->timer_source & 0x01);
        T3CONbits.T3CCP2 = ((_capture->timer_source>>1) & 0x01);

    }
    
    return ret;
}

 #if INTERRUPT_CAPTURE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Capture1_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Capture1_ClearFlag();
    
    if(NULL != Capture1_InterruptHandler){
        Capture1_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}

#endif

static Std_ReturnType Capture1_ConfigureInterrupt(const Capture1_ConfigType* _capture){
  
Std_ReturnType ret = E_OK;
    if(NULL == _capture ){
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_CAPTURE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Capture1_InterruptHandler = _capture->Capture1_InterruptHandler;
        Capture1_EnableInterrupt();
        
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Capture1_SetPrioirty(_capture->priority);
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
            
 
//////////////////////////////////////////// Compare Mode ///////////////////////////////////////////////
#elif CCP1_CFG_COMPARE_MODE_SELECTED == CCP1_MODULE_ENABLE

static Std_ReturnType Compare1_SetTimerSource(const Compare1_ConfigType* _compare){
    Std_ReturnType ret = E_OK;
    if(NULL == _compare ){
        ret = E_NOT_OK;
    }
    else{
        
        T3CONbits.T3CCP1 = (_compare->timer_source & 0x01);
        T3CONbits.T3CCP2 = ((_compare->timer_source>>1) & 0x01);

    }
    
    return ret;
}

 #if INTERRUPT_COMPARE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Compare1_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Compare1_ClearFlag();
    
    if(NULL != Compare1_InterruptHandler){
        Compare1_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}

#endif

static Std_ReturnType Compare1_ConfigureInterrupt(const Compare1_ConfigType* _compare){
  
Std_ReturnType ret = E_OK;
    if(NULL == _compare ){
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_COMPARE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Compare1_InterruptHandler = _compare->Compare1_InterruptHandler;
        Compare1_EnableInterrupt();
        
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Compare1_SetPrioirty(_capture->priority);
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

//////////////////////////////////////////// PWM Mode ///////////////////////////////////////////////

#elif CCP1_CFG_PWM_MODE_SELECTED == CCP1_MODULE_ENABLE

static Std_ReturnType Pwm1_SetFrequancy(const Pwm1_ConfigType* _pwm){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _pwm ){
        ret = E_NOT_OK;
    }
    else{
        
        PR2 = (uint8)(_XTAL_FREQ /(_pwm->frequancy * 4.0 *_pwm->timer2_prescaler))-1;
    }
    
    return ret;
}



#else 

#endif 
