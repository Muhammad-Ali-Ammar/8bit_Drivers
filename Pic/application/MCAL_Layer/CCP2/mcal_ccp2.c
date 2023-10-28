/* 
 * File:   mcal_ccp2.c
 * Author:  
 *
 * Created on 22 ?????, 2023, 07:51 ?
 */


/********************************** Includes *****************************************/

#include "mcal_ccp2.h"


/********************************** Private  defination and declaration  *****************************************/

#if CCP2_CFG_CAPTURE_MODE_SELECTED == CCP2_MODULE_ENABLE
    
static void (*Capture2_InterruptHandler)( void);
static Std_ReturnType Capture2_ConfigureInterrupt(const Capture2_Type* _capture);
static Std_ReturnType Capture2_SetTimerSource(const Capture2_ConfigType* _capture);

static Dio_PinConfigType g_ccp2_pin ={
    .direction = DIO_DIRECTION_INPUT,
    .logic = DIO_LOW,
    .pin =DIO_PIN1,
    .port = DIO_PORTC_INDEX
};


#elif CCP2_CFG_COMPARE_MODE_SELECTED == CCP2_MODULE_ENABLE


static void (*Compare2_InterruptHandler)( void);
static Std_ReturnType Compare2_ConfigureInterrupt(const Compare2_ConfigType* _compare);
static Std_ReturnType Compare2_SetTimerSource(const Compare2_ConfigType* _compare);

static Dio_PinConfigType g_ccp2_pin ={
    .direction = DIO_DIRECTION_OUTPUT,
    .logic = DIO_LOW,
    .pin =DIO_PIN1,
    .port = DIO_PORTC_INDEX
};

#elif CCP2_CFG_PWM_MODE_SELECTED == CCP2_MODULE_ENABLE

static Dio_PinConfigType g_ccp2_pin ={
    .direction = DIO_DIRECTION_OUTPUT,
    .logic = DIO_LOW,
    .pin =DIO_PIN1,
    .port = DIO_PORTC_INDEX
};

static Std_ReturnType Pwm2_SetFrequancy(const Pwm2_ConfigType* _pwm);

#else 

#endif 

/********************************** Public Function Implementation  *****************************************/

#if CCP2_CFG_CAPTURE_MODE_SELECTED == CCP2_MODULE_ENABLE

Std_ReturnType Capture2_Init(const Capture2_Type* _capture){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture){
        ret = E_NOT_OK;
    }
    else{
        /* Disable perihperal first */
        CAPTURE2_SET_EDGE(CAPTURE2_EDGE_DISABLE_MODULE);
        
        /* Configure pin as INPUT */
        ret &= Dio_InitChannelDirection(&g_ccp2_pin);
        
        /* Configure Timer source*/
        ret &= Capture2_SetTimerSource(_capture);
        
        /* Configure The interrupt*/
        ret &=Capture2_ConfigureInterrupt(_capture);
        
        
        /* Set Mode */
        CAPTURE2_SET_EDGE(_capture->edge);
    }
    
    return ret;
}

Std_ReturnType Capture2_DeInit(const Capture2_Type* _capture){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture){
        ret = E_NOT_OK;
    }
    else{
        /* Disable perihperal first */
        CAPTURE2_SET_EDGE(CAPTURE2_EDGE_DISABLE_MODULE);
        
#if INTERRUPT_CAPTURE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Capture2_DisableInterrupt();
#endif
    }
    
    return ret;
}

Std_ReturnType Capture2_GetValue(const Capture2_Type* _capture, uint16* _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        
        *_value = CCPR2;
    }
    
    return ret;
}

Std_ReturnType Capture2_ChangeEdge(const Capture2_ConfigType* _capture, Capture2_EdgeType _edge){
    Std_ReturnType ret = E_OK;
    if(NULL == _capture ){
        ret = E_NOT_OK;
    }
    else{
        
        CAPTURE2_SET_EDGE(_edge);
        Capture2_ClearFlag();

    }
    
    return ret;
}

///////////////////////// COMPARE MODE ////////////////////////////////

#elif CCP2_CFG_COMPARE_MODE_SELECTED == CCP2_MODULE_ENABLE


Std_ReturnType Compare2_Init(const Compare2_ConfigType* _compare){
    Std_ReturnType ret = E_OK;
    if(NULL == _compare){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable */
        COMPARE2_SET_MODE(COMPARE2_MODE_DISABLE);
        
        /* Configure pin as output*/
        ret &= Dio_InitChannel(&g_ccp2_pin);
        
        /* Configure Interrupt */
        ret &= Compare2_ConfigureInterrupt(_compare);
        
        /* Configure Timer source*/
        ret &= Compare2_SetTimerSource(_compare);
        
        /* set mode */
        COMPARE2_SET_MODE(_compare->mode);
    }
    
    return ret;
}
Std_ReturnType Compare2_DeInit(const Compare2_ConfigType* _compare){
    Std_ReturnType ret = E_OK;
    if(NULL == _compare){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable perihperal first */
        COMPARE2_SET_MODE(COMPARE2_MODE_DISABLE);
        
#if INTERRUPT_COMPARE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Compare2_DisableInterrupt();
#endif
    }
    
    return ret;
}
Std_ReturnType Compare2_SetValue(const Compare2_ConfigType* _compare, uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _compare) {
        ret = E_NOT_OK;
    }
    else{
        
        CCPR2 = _value;
    }
    
    return ret;
}

#elif CCP2_CFG_PWM_MODE_SELECTED == CCP2_MODULE_ENABLE


Std_ReturnType Pwm2_Init(const Pwm2_ConfigType* _pwm){
    Std_ReturnType ret = E_OK;
    if(NULL == _pwm){
        ret = E_NOT_OK;
    }
    else{
        /* Disable Peripheral  */
        PWM2_DISABLE();
        
        /* Configure pin as output*/
        ret &= Dio_InitChannel(&g_ccp2_pin);
        
        /* SetFrequancy/ Period   */
        ret &= Pwm2_SetFrequancy( _pwm);
        
        /* Enable Peripheral  */
        PWM2_ENABLE();
    }
    
    return ret;
}

Std_ReturnType Pwm2_DeInit(const Pwm2_ConfigType* _pwm){
    Std_ReturnType ret = E_OK;
    if(NULL == _pwm){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable Peripheral  */
        PWM2_DISABLE();
    }
    
    return ret;
}

Std_ReturnType Pwm2_SetDutyCycle(const Pwm2_ConfigType* _pwm, uint8 _duty_cycle_precentage){
    Std_ReturnType ret = E_OK;
    uint16 l_pwm2_10bit = ZERO_VALUE;
    if(NULL == _pwm){
        ret = E_NOT_OK;
    }
    else {
        
     l_pwm2_10bit = (uint16) ((PR2+1)*4*(_duty_cycle_precentage/100.0));
     CCP2CONbits.DC2B = (l_pwm2_10bit &0x0003);
     CCPR2L = (uint8)(l_pwm2_10bit>>2);
     
    }
    
    
    return ret;
}


Std_ReturnType Pwm2_Stop(const Pwm2_ConfigType* _pwm){
    
    Std_ReturnType ret = E_OK;
   
    ret &= Pwm2_SetDutyCycle(_pwm,0);
    
    
    return ret;
}


#else 

#endif 

/********************************** Private Function Implementation  *****************************************/

#if CCP2_CFG_CAPTURE_MODE_SELECTED == CCP2_MODULE_ENABLE

 #if INTERRUPT_CAPTURE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Capture2_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Capture2_ClearFlag();
    
    if(NULL != Capture2_InterruptHandler){
        Capture2_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}

#endif
static Std_ReturnType Compare1_SetTimerSource(const Capture2_Type* _capture){
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
static Std_ReturnType Capture2_ConfigureInterrupt(const Capture2_Type* _capture){
  
Std_ReturnType ret = E_OK;
    if(NULL == _capture ){
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_CAPTURE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Capture2_InterruptHandler = _capture->Capture2_InterruptHandler;
        Capture2_EnableInterrupt();
        
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Capture2_SetPrioirty(_capture->priority);
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
#elif CCP2_CFG_COMPARE_MODE_SELECTED == CCP2_MODULE_ENABLE


 #if INTERRUPT_COMPARE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void Compare2_ISR(void){
    Std_ReturnType ret = E_OK;
    
    Compare2_ClearFlag();
    
    if(NULL != Compare2_InterruptHandler){
        Compare2_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
}

#endif

static Std_ReturnType Compare2_SetTimerSource(const Compare2_ConfigType* _compare){
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

static Std_ReturnType Compare2_ConfigureInterrupt(const Compare2_ConfigType* _compare){
  
Std_ReturnType ret = E_OK;
    if(NULL == _compare ){
        ret = E_NOT_OK;
    }
    else{
  
 #if INTERRUPT_COMPARE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Compare2_InterruptHandler = _compare->Compare2_InterruptHandler;
        Compare2_EnableInterrupt();
        
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Compare2_SetPrioirty(_capture->priority);
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

#elif CCP2_CFG_PWM_MODE_SELECTED == CCP2_MODULE_ENABLE

static Std_ReturnType Pwm2_SetFrequancy(const Pwm2_ConfigType* _pwm){
    
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
