/**************************************************************************/
/* Filename						: ADC.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 23 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../DIO/include/DIO.h"
#include <util/delay.h>
#include "../include/ADC_config.h"
#include "../include/ADC.h"
#include "../include/ADC_private.h"


//////////////////////////Helpers Functions /////////////////////////////////


static void (*Adc_InterruptHandlerArr[ADC_NUMBER_OF_CHANNELS])( u16 _result);

static Adc_ResultFormartType current_format=ZERO_VALUE;
static u8 Global_AdcInterruptIndex=ZERO_VALUE;


static Adc_StatusErrorType Adc_GetResult(const Adc_ResultFormartType Copy_enuResultFormat, u16* Address_Result);

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/

#define Adc_SelectChannel(CHANNEL)               ( (ADMUX) = ((ADMUX) & 0xF8) | (CHANNEL & 0x07)  )
#define Adc_StartConversion()                   (SET_BIT(ADCSRA,6))
#define Adc_IsConversionCompleted()             (READ_BIT(ADCSRA,6) == 0)

#define Adc_Enable()                            (SET_BIT(ADCSRA,7))
#define Adc_Disable()                           (CLEAR_BIT(ADCSRA,7))


#define Adc_SelectResultFormat(ARGU)                 (WRITE_BIT(ADMUX,5,(ARGU)))

#define Adc_SelectConversionClock(ARGU)              ( (ADCSRA) = ((ADCSRA) &0x70) | (ARGU &0x07)  )


#define Adc_EnableInterrupt()                            (SET_BIT(ADCSRA,3))
#define Adc_DisableInterrupt()                           (CLEAR_BIT(ADCSRA,3))
#define Adc_GetInterruptEnableStatus()					(READ_BIT(ADCSRA,3))
#define Adc_SetInterruptEnable(ARGU)						(WRITE_BIT(ADCSRA,3,(ARGU)))


#define Adc_GetInterruptFlag()					     	(READ_BIT(ADCSRA,4))
#define Adc_ClearInterruptFlag()						(SET_BIT(ADCSRA,4))

#define Adc_SelectRefVoltageSource(ARGU)           ( (ADMUX) = ((ADMUX) & 0x3F) | (ARGU<<6)  )


/********************************** Data Type Declarations ****************************/

/********************************** Software Interfaces Declarations *******************/


Adc_StatusErrorType Adc_enuInit(const Adc_PinConfigType* Address_Adc){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
	    if(NULL == Address_Adc){

	    	Loc_enuAdcStatus = ADC_STATUS_NULL_POINTER_ADDRESS;
	    }
	    else{
	    	 /* Disable Adc Peripheral */
	    	        Adc_Disable();



	    	        /* Choose Conversion Clock  */
	    	        Adc_SelectConversionClock(Address_Adc->conversion_frequancy);

	    	        /* Choose Selected Channel */
	    	        Adc_SelectChannel(Address_Adc->channel_number);


	    	        /*Configure Result Format */
	    	        Adc_SelectResultFormat(Address_Adc->result_format);

	    	        /* Configure Voltage Reference*/
	    	        Adc_SelectRefVoltageSource(Address_Adc->vref_source);

	    	        /* Enable Adc Peripheral */
	    	        Adc_Enable();

	    }

	    return Loc_enuAdcStatus;
}

Adc_StatusErrorType Adc_enuDeInit(void){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;

	Adc_Disable();
	    return Loc_enuAdcStatus;
}


Adc_StatusErrorType Adc_enuStartConversionSync(const Adc_PinConfigType* Address_Adc, u16* Address_ResultDigitalVoltage){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
	u8 Loc_u8AdcInterruptStatus = ZERO_VALUE;
	    if(NULL == Address_Adc || Address_ResultDigitalVoltage == NULL){

	    	Loc_enuAdcStatus = ADC_STATUS_NULL_POINTER_ADDRESS;
	    }
	    else{

	            /* Read Status of The interrupt */
	    	    Loc_u8AdcInterruptStatus = Adc_GetInterruptEnableStatus();

	            /* Choose Selected Channel */
	            Adc_SelectChannel(Address_Adc->channel_number);


	            /* Disable Interrupt not to jump after completing*/
	            Adc_SetInterruptEnable(ZERO_VALUE);


	            /* Start Conversion  */
	            Adc_StartConversion();



	            /* wait =polling for conversion */
	            while( ZERO_VALUE == Adc_IsConversionCompleted() );
	            _delay_us(10);

	            Loc_enuAdcStatus &= Adc_GetResult(Address_Adc->result_format ,Address_ResultDigitalVoltage);

	            /* Return Status Of The Adc Interrupt*/
	            Adc_ClearInterruptFlag();
	            Adc_SetInterruptEnable(Loc_u8AdcInterruptStatus);
	        }

	    return Loc_enuAdcStatus;
}



Adc_StatusErrorType Adc_ConvertResultToVoltage( u16 Copy_u16DigitalValue, f32* Address_ResultAnalogVoltage){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
	    if(NULL == Address_ResultAnalogVoltage){

	    	Loc_enuAdcStatus = ADC_STATUS_NULL_POINTER_ADDRESS;
	    }
	    else{
	           /* Vanalog = Vdigital * step    */
	           /* Step Size = (Vmax-Vmin)/2^n      */
	           *Address_ResultAnalogVoltage = Copy_u16DigitalValue*0.004883F;
	       }

	    return Loc_enuAdcStatus;
}


Adc_StatusErrorType Adc_StartConversionAsync(const Adc_PinConfigType* Address_Adc){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
	    if(NULL == Address_Adc){

	    	Loc_enuAdcStatus = ADC_STATUS_NULL_POINTER_ADDRESS;
	    }
	    else{
	    	 /* You can't start A new Conversion Unless The old One Is Done*/
	    	        while( ZERO_VALUE == Adc_IsConversionCompleted() );

	    	        Global_AdcInterruptIndex = (u8)Address_Adc->channel_number;
	    	        current_format = Address_Adc->result_format;
	    	        /* Choose Selected Channel */
	    	        Adc_SelectChannel(Address_Adc->channel_number);


	    	        /* Start Conversion  */
	    	        Adc_StartConversion();
	    }

	    return Loc_enuAdcStatus;
}


Adc_StatusErrorType Adc_enuEnableInterrupt(void){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
	Adc_EnableInterrupt();

		    return Loc_enuAdcStatus;
}


Adc_StatusErrorType Adc_enuDisableInterrupt(void){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
	Adc_DisableInterrupt();

		    return Loc_enuAdcStatus;
}





////////////////////////////////////////////////Helpers Functions ///////////////////////////
static Adc_StatusErrorType Adc_GetResult(const Adc_ResultFormartType Copy_enuResultFormat, u16* Address_Result){

	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
	    if(NULL == Address_Result){

	    	Loc_enuAdcStatus = ADC_STATUS_NULL_POINTER_ADDRESS;
	    }

	    	else{
	    	        switch(Copy_enuResultFormat){

	    	        case ADC_RIGHT_JUSTIFIED:



	    	                *Address_Result = (ADCL) | (ADCH <<8) ;
	    	                break;

	    	            default:
	    	            	*Address_Result = (ADCHL>>6) & 0x3FF;

	    	        }
	    	    }


	    return Loc_enuAdcStatus;
}

Adc_StatusErrorType Adc_SetCallbackFunction(const Adc_PinConfigType* Address_Adc, void (*callback)(u16)){
	Adc_StatusErrorType Loc_enuAdcStatus = ADC_STATUS_OK;
		    if(NULL == Address_Adc){
		    	Loc_enuAdcStatus = ADC_STATUS_NULL_POINTER_ADDRESS;
		    }
		    else{
		    	Adc_InterruptHandlerArr[Address_Adc->channel_number] = callback;
		    }
		    return Loc_enuAdcStatus;
}

// ISR function For ADC
void __vector_16(void) __attribute__((signal));

void __vector_16(void){

	    u16 Loc_u16Result;
	    Adc_StatusErrorType Loc_enuAdcStatus  = ADC_STATUS_OK;

	    Loc_enuAdcStatus = Adc_GetResult(current_format,&Loc_u16Result);
	    if(NULL != Adc_InterruptHandlerArr[Global_AdcInterruptIndex]){
	        Adc_InterruptHandlerArr[Global_AdcInterruptIndex](Loc_u16Result);
	    }
	    else {/* do nothing , error in declaration */ }

}


