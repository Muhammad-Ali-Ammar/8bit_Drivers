/**************************************************************************/
/* Filename						: ADC.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef MCAL_ADC_INCLUDE_ADC_H_
#define MCAL_ADC_INCLUDE_ADC_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

/********************************** Macros Declarations like Function *******************************/



/********************************** Data Type Declarations ****************************/

typedef enum{
    ADC_SELECT_CHANNEL0,
    ADC_SELECT_CHANNEL1,
    ADC_SELECT_CHANNEL2,
    ADC_SELECT_CHANNEL3,
    ADC_SELECT_CHANNEL4,
    ADC_SELECT_CHANNEL5,
    ADC_SELECT_CHANNEL6,
    ADC_SELECT_CHANNEL7,
}Adc_ChannelSelectType;


typedef enum{
    ADC_REF_VOLTAGE_AREF_INTERNAL_TURN_OFF,
    ADC_REF_VOLTAGE_AVCC_WITH_EXTERNAL_CAPACITOR, // in ETA32
    ADC_REF_VOLTAGE_INTERNAL_2point56V_WITH_EXTERNAL_CAPACITOR=2

}Adc_RefVoltageSourceType;

typedef enum{
	ADC_RIGHT_JUSTIFIED,
    ADC_LEFT_JUSTIFIED
}Adc_ResultFormartType;


typedef enum{
    ADC_FOSC_DIV_2,
    ADC_FOSC_DIV_4=2,
    ADC_FOSC_DIV_8,
    ADC_FOSC_DIV_16,
    ADC_FOSC_DIV_32,
    ADC_FOSC_DIV_64,
    ADC_FOSC_DIV_128,
}Adc_CoversionClockType;


typedef struct{
    Adc_ChannelSelectType channel_number;
    Adc_RefVoltageSourceType vref_source;
    Adc_ResultFormartType result_format;
    Adc_CoversionClockType  conversion_frequancy;

}Adc_PinConfigType;



typedef enum{
	ADC_STATUS_FAIL,
	ADC_STATUS_OK,
	ADC_STATUS_NULL_POINTER_ADDRESS,
}Adc_StatusErrorType;


/********************************** Software Interfaces Declarations *******************/

Adc_StatusErrorType Adc_enuInit(const Adc_PinConfigType* Address_Adc);
Adc_StatusErrorType Adc_enuDeInit(void);
Adc_StatusErrorType Adc_enuEnableInterrupt(void);
Adc_StatusErrorType Adc_enuDisableInterrupt(void);

Adc_StatusErrorType Adc_enuStartConversionSync(const Adc_PinConfigType* Address_Adc, u16* Address_ResultDigitalVoltage);
Adc_StatusErrorType Adc_ConvertResultToVoltage( u16 Copy_u16DigitalValue, f32* Address_ResultAnalogVoltage);

Adc_StatusErrorType Adc_StartConversionAsync(const Adc_PinConfigType* Address_Adc);
Adc_StatusErrorType Adc_SetCallbackFunction(const Adc_PinConfigType* Address_Adc,void (*callback)(u16));


#endif /* MCAL_ADC_INCLUDE_ADC_H_ */
