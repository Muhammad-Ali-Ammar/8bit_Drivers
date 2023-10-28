/* 
 * File:   mcal_initialize.h
 * Author: isammar93
 *
 * Created on 01 ????, 2023, 09:40 ?
 */

#ifndef MCAL_INITIALIZE_H
#define	MCAL_INITIALIZE_H

/********************************** Includes *****************************************/

#include"GPIO/mcal_gpio.h"
#include "INTERRUPT/mcal_external_interrupt.h"
#include "ADC/mcal_adc.h"
#include "TIMER0/mcal_timer0.h"
#include "TIMER1/mcal_timer1.h"
#include "TIMER2/mcal_timer2.h"
#include "TIMER3/mcal_timer3.h"
#include "CCP1/mcal_ccp1.h"
#include "CCP2/mcal_ccp2.h"
#include "EUSART/mcal_eusart.h"
#include "I2C/mcal_i2c.h"

/********************************** Macros Declarations *******************************/
#define Pin_SelectAnalogOrDigitalMode(x)     (ADCON1bits.PCFG = (x))


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/

typedef enum{
    PIN_CONFIG_AN0_TO_AN12_ANALOG = 0b0010,
    PIN_CONFIG_AN0_TO_AN11_ANALOG,
    PIN_CONFIG_AN0_TO_AN10_ANALOG,
    PIN_CONFIG_AN0_TO_AN9_ANALOG,
    PIN_CONFIG_AN0_TO_AN8_ANALOG,
    PIN_CONFIG_AN0_TO_AN7_ANALOG,
    PIN_CONFIG_AN0_TO_AN6_ANALOG,
    PIN_CONFIG_AN0_TO_AN5_ANALOG,
    PIN_CONFIG_AN0_TO_AN4_ANALOG,
    PIN_CONFIG_AN0_TO_AN3_ANALOG,
    PIN_CONFIG_AN0_TO_AN2_ANALOG,
    PIN_CONFIG_AN0_TO_AN1_ANALOG,
    PIN_CONFIG_AN0_TO_AN0_ANALOG,
    PIN_CONFIG_ALL_DIGITAL
            
}Pin_ConfigDigitalOrAnalogType;


/********************************** Software Interfaces Declarations *******************************/

void Mcal_Init(void);


#endif	/* MCAL_INITIALIZE_H */

