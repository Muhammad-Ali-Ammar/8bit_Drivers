/* 
 * File:   mcal_adc.h
 * Author: isammar93
 *
 * Created on 30 ????, 2023, 05:18 ?
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H

/********************************** Includes *****************************************/
#include "../mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "mcal_adc_cfg.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/
#define Adc_SelectChannel(x)                    (ADCON0bits.CHS = (x))

#define Adc_StartConversion()                   (ADCON0bits.GODONE = 1)
#define Adc_IsConversionCompleted()             (ADCON0bits.GODONE == 0)


#define Adc_Enable()                            (ADCON0bits.ADON = 1)
#define Adc_Disable()                           (ADCON0bits.ADON = 0)


/* Second Register */

#define Adc_SelectRefVoltageSource(x)           {ADCON1bits.VCFG0 =(x); \
                                                 ADCON1bits.VCFG1 =(x); \
                                                 }
                                                 


#define Adc_SelectPinsAnalogOrDigitalMode(x)     (ADCON1bits.PCFG = (x))

/* Third Control Register*/

#define Adc_SelectResultFormat(x)                 (ADCON2bits.ADFM = (x))
#define Adc_SelectAcquistionTime(x)               (ADCON2bits.ACQT = (x))
#define Adc_SelectConversionClock(x)              (ADCON2bits.ADCS = (x))

/*  Fot Interrupt Part */
#define Adc_GetInterruptEnableStatus()            (PIE1bits.ADIE )
#define Adc_SetInterruptEnable(x)                 (PIE1bits.ADIE =(x) )
#define Adc_ClearFlagBit()                        (PIR1bits.ADIF = 0)
/********************************** Data Type Declarations *******************************/

typedef enum{
    ADC_SELECT_CHANNEL0,
    ADC_SELECT_CHANNEL1,
    ADC_SELECT_CHANNEL2,
    ADC_SELECT_CHANNEL3,
    ADC_SELECT_CHANNEL4,
    ADC_SELECT_CHANNEL5,
    ADC_SELECT_CHANNEL6,
    ADC_SELECT_CHANNEL7,
    ADC_SELECT_CHANNEL8,
    ADC_SELECT_CHANNEL9,
    ADC_SELECT_CHANNEL10,
    ADC_SELECT_CHANNEL11,
    ADC_SELECT_CHANNEL12
}Adc_ChannelSelectType;


typedef enum{
    ADC_PIN_CONFIG_AN0_TO_AN12_ANALOG = 0b0010,
    ADC_PIN_CONFIG_AN0_TO_AN11_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN10_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN9_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN8_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN7_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN6_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN5_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN4_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN3_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN2_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN1_ANALOG,
    ADC_PIN_CONFIG_AN0_TO_AN0_ANALOG,
    ADC_PIN_CONFIG_ALL_DIGITAL
            
}Adc_PinConfigDigitalOrAnalogType;

typedef enum{
    ADC_REF_VOLTAGE_VDD_VSS,
    ADC_REF_VOLTAGE_AN3_AN2,
            
}Adc_RefVoltageSourceType;

typedef enum{
    ADC_LEFT_JUSTIFIED,
    ADC_RIGHT_JUSTIFIED,
}Adc_ResultFormartType;

typedef enum{
    ADC_0TAD,
    ADC_2TAD,
    ADC_4TAD,
    ADC_6TAD,
    ADC_8TAD,
    ADC_12TAD,
    ADC_16TAD,
    ADC_20TAD
}Adc_AcquisitionTimeType;


typedef enum{
    ADC_FOSC_DIV_2,
    ADC_FOSC_DIV_8,
    ADC_FOSC_DIV_32,
    ADC_FRC,
    ADC_FOSC_DIV_4,
    ADC_FOSC_DIV_16,
    ADC_FOSC_DIV_64,
}Adc_CoversionClockType;


typedef struct{
    Adc_ChannelSelectType channel_number;
    Adc_RefVoltageSourceType vref_source;
    Adc_ResultFormartType result_format;
    Adc_AcquisitionTimeType acqusition_time;
    Adc_CoversionClockType  conversion_frequancy;
    
    void (*Adc_InterruptHandler)(uint16 _result);
    Interrupt_PrioityType priority;
    
}Adc_PinConfigType;
/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Adc_Init(const Adc_PinConfigType* _adc);
Std_ReturnType Adc_DeInit();



Std_ReturnType Adc_StartConversionSync(const Adc_PinConfigType* _adc, uint16* _result);
Std_ReturnType Adc_ConvertResultToVoltage( uint16 _digital_voltage, float32* _analogvoltage);


    #if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    Std_ReturnType Adc_StartConversionAsync(const Adc_PinConfigType* _adc);
    #endif



#endif	/* MCAL_ADC_H */

