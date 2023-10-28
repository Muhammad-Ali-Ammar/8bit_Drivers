/* 
 * File:   mcal_adc.h
 * Author: isammar93
 *
 * Created on 30 ????, 2023, 05:18 ?
 */



#include "mcal_adc.h"

#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        static void (*Adc_InterruptHandlerArr[12])( uint16 _result);
        static uint8 g_adc_interrupt_idx=0;
        static Adc_ResultFormartType current_format=0;
#endif

        
static Std_ReturnType Adc_InitPinDirection(const Adc_PinConfigType* _adc);
static Std_ReturnType Adc_ConfigureInterrupt(const Adc_PinConfigType* _adc);
static Std_ReturnType Adc_GetResult(const Adc_ResultFormartType _result_format, uint16* _result);

Std_ReturnType Adc_Init(const Adc_PinConfigType* _adc){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable Adc Peripheral */
        Adc_Disable();
        
        /* Choose acquisition Time */
        Adc_SelectAcquistionTime(_adc->acqusition_time);
        
        /* Choose Conversion Clock  */
        Adc_SelectConversionClock(_adc->conversion_frequancy);
        
        /* Choose Selected Channel */
        Adc_SelectChannel(_adc->channel_number);
        
        /* Init Pin As Input */
        ret &= Adc_InitPinDirection(_adc);
        
        
        /* Interrupt Configuration */
        ret &= Adc_ConfigureInterrupt(_adc);
        
        /*Configure Result Format */
        Adc_SelectResultFormat(_adc->result_format);
        
        /* Configure Voltage Reference*/
        Adc_SelectRefVoltageSource(_adc->vref_source);
        
        /* Enable Adc Peripheral */
        Adc_Enable();
    }
    
    return ret;
}
Std_ReturnType Adc_DeInit(){
    
    Std_ReturnType ret = E_OK;

        Adc_Disable();
#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        Adc_DisableInterrupt();
#endif
    
    return ret;
}


Std_ReturnType Adc_StartConversionSync(const Adc_PinConfigType* _adc, uint16* _result){
    
    Std_ReturnType ret = E_OK;
    uint8 l_adc_interrupt_status = ZERO_VALUE;
    if(NULL == _adc || NULL == _result){
        
        ret = E_NOT_OK;
    }
    else{
        
        /* Read Status of The interrupt */
         l_adc_interrupt_status = Adc_GetInterruptEnableStatus();
    
        /* Choose Selected Channel */
        Adc_SelectChannel(_adc->channel_number);
        
        
        /* Start Conversion  */
        Adc_StartConversion();
        
        /* Disable Interrupt not to jump after completing*/
        Adc_SetInterruptEnable(ZERO_VALUE);
        
        /* wait =polling for conversion */
        while( ZERO_VALUE == Adc_IsConversionCompleted() );
        ret &= Adc_GetResult(_adc->result_format ,_result);
        
        /* Return Status Of The Adc Interrupt*/
        Adc_ClearFlagBit();
        Adc_SetInterruptEnable(l_adc_interrupt_status);
    }
    
    return ret;
}

Std_ReturnType Adc_ConvertResultToVoltage( uint16 _digital_voltage, float32* _analogvoltage){
    Std_ReturnType ret = E_OK;
    if( NULL == _analogvoltage){
        
        ret = E_NOT_OK;
    }
    else{
        /* Vanalog = Vdigital * step    */
        /* Step Size = (Vmax-Vmin)/2^n      */
        *_analogvoltage = _digital_voltage*0.004883F;
    }
    return ret;
}


#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

Std_ReturnType Adc_StartConversionAsync(const Adc_PinConfigType* _adc){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        
        ret = E_NOT_OK;
    }
    else{
        /* You can't start A new Conversion Unless The old One Is Done*/
        while( ZERO_VALUE == Adc_IsConversionCompleted() );
        
        g_adc_interrupt_idx = (uint8)_adc->channel_number;
        current_format = _adc->result_format;
        /* Choose Selected Channel */
        Adc_SelectChannel(_adc->channel_number);
        
        
        /* Start Conversion  */
        Adc_StartConversion();
        
    }
    
    return ret;
}

/* Interrupt Handler */
void Adc_ISR(){
    Adc_ClearFlag();
    uint16 l_result;
    Std_ReturnType ret = E_OK;
    
    ret &= Adc_GetResult(current_format,&l_result);
    if(NULL != Adc_InterruptHandlerArr[g_adc_interrupt_idx]){
        Adc_InterruptHandlerArr[g_adc_interrupt_idx](l_result);
    }
    else {/* do nothing , error in declaration */ }
}
#endif




/* Helper Functions */

static Std_ReturnType Adc_InitPinDirection(const Adc_PinConfigType* _adc){
    Std_ReturnType ret = E_OK;
    Dio_PinConfigType l_adc_pin ={
        .direction = DIO_DIRECTION_INPUT,
        .logic = DIO_LOW,
    };
    
    
    if(NULL == _adc){
        
        ret = E_NOT_OK;
    }
    else{
        switch(_adc->channel_number){
            
            case ADC_SELECT_CHANNEL0:
            case ADC_SELECT_CHANNEL1:
            case ADC_SELECT_CHANNEL2:
            case ADC_SELECT_CHANNEL3:
                l_adc_pin.pin = (Dio_PinIndexType)_adc->channel_number;
                l_adc_pin.port = DIO_PORTA_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL4:
                l_adc_pin.pin = DIO_PIN5;
                l_adc_pin.port = DIO_PORTA_INDEX;
            
                break;
                
            case ADC_SELECT_CHANNEL5:
                l_adc_pin.pin = DIO_PIN0;
                l_adc_pin.port = DIO_PORTE_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL6:
                l_adc_pin.pin = DIO_PIN1;
                l_adc_pin.port = DIO_PORTE_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL7:
                l_adc_pin.pin = DIO_PIN2;
                l_adc_pin.port = DIO_PORTE_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL8:
                l_adc_pin.pin = DIO_PIN2;
                l_adc_pin.port = DIO_PORTB_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL9:
                l_adc_pin.pin = DIO_PIN3;
                l_adc_pin.port = DIO_PORTB_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL10:
                l_adc_pin.pin = DIO_PIN1;
                l_adc_pin.port = DIO_PORTB_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL11:
                l_adc_pin.pin = DIO_PIN4;
                l_adc_pin.port = DIO_PORTB_INDEX;
                break;
                
            case ADC_SELECT_CHANNEL12:
                l_adc_pin.pin = DIO_PIN0;
                l_adc_pin.port = DIO_PORTB_INDEX;
                break;
                
            default:
                
                ret = E_NOT_OK;
        }
        ret &= Dio_InitChannelDirection(&l_adc_pin);
    }
    
    return ret;
}

static Std_ReturnType Adc_ConfigureInterrupt(const Adc_PinConfigType* _adc){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _adc ){
        
        ret = E_NOT_OK;
    }
    else{
        
#if   INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        Adc_InterruptHandlerArr[_adc->channel_number] = _adc->Adc_InterruptHandler;
        Adc_EnableInterrupt();
        
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 Adc_SetPrioirty(_adc->priority);
                 Interrupt_EnablePrioirtyOfTheSystem();
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
    #else 
            Interrupt_EnableGlobalInterrupt();
            Interrupt_EnablePeripheralInterrupt();
    #endif
        
        
        
#endif   // Interrupt
            
    }
    
    return ret;
    
    
    
}

static Std_ReturnType Adc_GetResult(const Adc_ResultFormartType _result_format, uint16* _result){
    
    Std_ReturnType ret = E_OK;
    if( NULL == _result){
        
        ret = E_NOT_OK;
    }
    else{
        switch(_result_format){
            ADC_LEFT_JUSTIFIED:
                *_result = (ADRES>>6) & 0x3FF;
                break;
                
            default:
                *_result = ADRES & 0x3FF ;
            
        }
    }
    
    return ret;
}