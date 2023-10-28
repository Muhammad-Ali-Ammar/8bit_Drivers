/* 
 * File:   mcal_internal_interrupt.h
 * Author: isammar93
 *
 * Created on 07 ????, 2023, 04:58 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H


/********************************** Includes *****************************************/
#include "mcal_interrupt_cfg.h"


/********************************** Macros Declarations *******************************/

/////////////////////////////////////
/* Adc Peripheral */



#if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE


#define Adc_EnableInterrupt()              (PIE1bits.ADIE = 1)
#define Adc_DisableInterrupt()             (PIE1bits.ADIE = 0)

#define Adc_IsInterruptEnabled()           (PIE1bits.ADIE == 1)
		
#define Adc_ClearFlag()                    (PIR1bits.ADIF = 0)
#define Adc_IsInterruptFired()             (PIR1bits.ADIF == 1)
		
#define Adc_SetPrioirty(x)                 (IPR1bits.ADIP = (x))

void Adc_ISR();

#endif
///////////////////////////////////////

/* Timer 0 */
#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Timer0_EnableInterrupt()              (INTCONbits.T0IE = 1)
#define Timer0_DisableInterrupt()             (INTCONbits.T0IE = 0)
		
#define Timer0_IsInterruptEnabled()           (INTCONbits.T0IE == 1)
		
#define Timer0_ClearFlag()                    (INTCONbits.T0IF = 0)
#define Timer0_IsInterruptFired()             (INTCONbits.T0IF == 1)
		
#define Timer0_SetPrioirty(x)                 (INTCON2bits.TMR0IP = (x))

void Timer0_ISR(void);
#endif

/* Timer 1 */
#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Timer1_EnableInterrupt()              (PIE1bits.TMR1IE = 1)
#define Timer1_DisableInterrupt()             (PIE1bits.TMR1IE = 0)
		
#define Timer1_IsInterruptEnabled()           (PIE1bits.TMR1IE == 1)
		
#define Timer1_ClearFlag()                    (PIR1bits.TMR1IF = 0)
#define Timer1_IsInterruptFired()             (PIR1bits.TMR1IF == 1)
		
#define Timer1_SetPrioirty(x)                 (IPR1bits.TMR1IP = (x))

void Timer1_ISR(void);
#endif



/* Timer 2 */
#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Timer2_EnableInterrupt()                (PIE1bits.TMR2IE = 1)
#define Timer2_DisableInterrupt()               (PIE1bits.TMR2IE = 0)
		 
#define Timer2_IsInterruptEnabled()             (PIE1bits.TMR2IE == 1)
		
#define Timer2_ClearFlag()                      (PIR1bits.TMR2IF = 0)
#define Timer2_IsInterruptFired()               (PIR1bits.TMR2IF == 1)
		
#define Timer2_SetPrioirty(_x_)                 (IPR1bits.TMR2IP = (_x_))

void Timer2_ISR(void);
#endif


/* Timer 1 */
#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Timer3_EnableInterrupt()              (PIE2bits.TMR3IE = 1)
#define Timer3_DisableInterrupt()             (PIE2bits.TMR3IE = 0)
		
#define Timer3_IsInterruptEnabled()           (PIE2bits.TMR3IE == 1)
		
#define Timer3_ClearFlag()                    (PIR2bits.TMR3IF = 0)
#define Timer3_IsInterruptFired()             (PIR2bits.TMR3IF == 1)
		
#define Timer3_SetPrioirty(_x_)               (IPR2bits.TMR2IP = (_x_))

void Timer3_ISR(void);
#endif

/* Compare 1 */
#if INTERRUPT_COMPARE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Compare1_EnableInterrupt()              (PIE1bits.CCP1IE = 1)
#define Compare1_DisableInterrupt()             (PIE1bits.CCP1IE = 0)
		
#define Compare1_IsInterruptEnabled()           (PIE1bits.CCP1IE == 1)
		
#define Compare1_ClearFlag()                    (PIR1bits.CCP1IF = 0)
#define Compare1_IsInterruptFired()             (PIR1bits.CCP1IF == 1)
		
#define Compare1_SetPrioirty(x)                 (IPR1bits.CCP1IP = (x))

void Compare1_ISR(void);

#endif

/* Capture 1 */
#if INTERRUPT_CAPTURE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Capture1_EnableInterrupt()              (PIE1bits.CCP1IE = 1)
#define Capture1_DisableInterrupt()             (PIE1bits.CCP1IE = 0)
		
#define Capture1_IsInterruptEnabled()           (PIE1bits.CCP1IE == 1)
		
#define Capture1_ClearFlag()                    (PIR1bits.CCP1IF = 0)
#define Capture1_IsInterruptFired()             (PIR1bits.CCP1IF == 1)
		
#define Capture1_SetPrioirty(_x_)                 (IPR1bits.CCP1IP = (_x_))

void Capture1_ISR(void);

#endif


/* Compare 2 */
#if INTERRUPT_COMPARE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Compare2_EnableInterrupt()              (PIE2bits.CCP2IE = 1)
#define Compare2_DisableInterrupt()             (PIE2bits.CCP2IE = 0)
		
#define Compare2_IsInterruptEnabled()           (PIE2bits.CCP2IE == 1)
		
#define Compare2_ClearFlag()                    (PIR2bits.CCP2IF = 0)
#define Compare2_IsInterruptFired()             (PIR2bits.CCP2IF == 1)
		
#define Compare2_SetPrioirty(x)                 (IPR2bits.CCP2IP = (x))

void Compare2_ISR(void);

#endif

/* Capture 2 */
#if INTERRUPT_CAPTURE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Capture2_EnableInterrupt()              (PIE2bits.CCP2IE = 1)
#define Capture2_DisableInterrupt()             (PIE2bits.CCP2IE = 0)
		
#define Capture2_IsInterruptEnabled()           (PIE2bits.CCP2IE == 1)
		
#define Capture2_ClearFlag()                    (PIR2bits.CCP2IF = 0)
#define Capture2_IsInterruptFired()             (PIR2bits.CCP2IF == 1)
		
#define Capture2_SetPrioirty(_x_)                 (IPR2bits.CCP2IP = (_x_))

void Capture2_ISR(void);

#endif

/* EUSART TX */
#if INTERRUPT_EUSART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EusartTx_EnableInterrupt()              (PIE1bits.TXIE = 1)
#define EusartTx_DisableInterrupt()             (PIE1bits.TXIE = 1)
		
#define EusartTx_IsInterruptEnabled()           (PIE1bits.TXIE == 1)
		
//#define EusartTx_ClearFlag()                    (PIR1bits.TXIF = 0)   // done 
#define EusartTx_IsInterruptFired()             (PIR1bits.TXIF == 1)
		
#define EusartTx_SetPrioirty(_x_)               (IPR1bits.TXIP = (_x_))

void EusartTx_ISR(void);

#endif


/* EUSART RX */
#if INTERRUPT_EUSART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EusartRx_EnableInterrupt()              (PIE1bits.RCIE = 1)
#define EusartRx_DisableInterrupt()             (PIE1bits.RCIE = 0)
		
#define EusartRx_IsInterruptEnabled()           (PIE1bits.RCIE == 1)
		
//#define EusartRx_ClearFlag()                    (PIR1bits.RCIF = 0) // done by hardware 
#define EusartRx_IsInterruptFired()             (PIR1bits.RCIF == 1)
		
#define EusartRx_SetPrioirty(_x_)                (IPR1bits.RCIP = (_x_))

void EusartRx_ISR(void);
#endif



/*  I2C */
#if INTERRUPT_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define I2c_EnableInterrupt()              (PIE1bits.SSPIE = 1)
#define I2c_DisableInterrupt()             (PIE1bits.SSPIE = 0)
		
#define I2c_IsInterruptEnabled()           (PIE1bits.SSPIE == 1)
		
#define I2c_ClearFlag()                    (PIR1bits.SSPIF = 0) 
#define I2c_IsInterruptFired()             (PIR1bits.SSPIF == 1)
		
#define I2c_SetPrioirty(_X_)                (IPR1bits.SSPIP = (_X_))

void I2c_ISR(void);
#endif


/*  I2C WRITE COLLISION */

#if INTERRUPT_I2C_WRITE_COLLISION_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define I2cWriteCollision_EnableInterrupt()              (PIE2bits.BCLIE = 1)
#define I2cWriteCollision_DisableInterrupt()             (PIE2bits.BCLIE = 0)
		
#define I2cWriteCollision_IsInterruptEnabled()           (PIE2bits.BCLIE == 1)
		
#define I2cWriteCollision_ClearFlag()                    (PIR2bits.BCLIF = 0) 
#define I2cWriteCollision_IsInterruptFired()             (PIR2bits.BCLIF == 1)
		
#define I2cWriteCollision_SetPrioirty(_X_)                (IPR2bits.BCLIP = (_X_))

void I2cWriteCollision_ISR(void);
#endif




/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/




/********************************** Software Interfaces Declarations *******************************/


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

