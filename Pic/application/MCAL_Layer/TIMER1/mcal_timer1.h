/* 
 * File:   mcal_timer1.h
 * Author: isammar93
 *
 * Created on 05 ?????, 2023, 02:42 ?
 */

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H

/********************************** Includes *****************************************/
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/********************************** Macros Declarations *******************************/
#define TIMER1_COUNTER_MODE_AND_TIMER1_OSCILLATOR                        1
#define TIMER1_TIMER_MODE_WITH_INTERNAL_OSCILLATOR                       0

/********************************** Macros Function Declarations *******************************/

/* Enable/Disable Timer 0 */
#define Timer1_Enable()                                   (T1CONbits.TMR1ON = 1)
#define Timer1_Disable()                                  (T1CONbits.TMR1ON = 0)

/* Choose Clock source */
#define Timer1_SetClockSource(_x_)                          (T1CONbits.TMR1CS = (_x_))
 
/* choose synchronization counter mode with timer1 clock */
#define Timer1_SetCounterModeSync(_x_)                     (T1CONbits.T1SYNC = (_x_))
#define Timer1_EnableSyncWithTimer1Oscillator()          (T1CONbits.T1SYNC = 0)
#define Timer1_DisableSyncWithTimer1Oscillator()         (T1CONbits.T1SYNC = 1)

/* enable / disable Timer1 clock */
#define Timer1_EnableTimer1Oscillator()                   (T1CONbits.T1OSCEN = 1)
#define Timer1_DisableTimer1Oscillator()                  (T1CONbits.T1OSCEN = 0)
#define Timer1_SetTimer1Oscillator(_x_)                     (T1CONbits.T1OSCEN = (_x_))

/*to enable or disable prescaler */
#define Timer1_SetPrescalerValue(_x_)                       (T1CONbits.T1CKPS = (_x_))

/* return flag of timer1 clock is enable or not */
#define Timer1_IsTimer1OscillatorEnabled()                (T1CONbits.T1RUN == 1)

/* set read/write in 8 or 16 bit instruciton */
#define Timer1_EnableWR16Operation()                      (T1CONbits.RD16 = 1)
#define Timer1_EnableWR8Operation()                       (T1CONbits.RD16 = 0)
#define Timer1_SetWRnBitOperation(_x_)                    (T1CONbits.RD16 = (_x_))


/********************************** Data Type Declarations *******************************/
typedef enum {
    TIMER1_SOURCE_TIMER_MODE_WITH_INTERNAL_OSCILLIATOR,
    TIMER1_SOURCE_TIMER_MODE_WITH_TIMER1_OSCILLIATOR,
    TIMER1_SOURCE_COUNTER_MODE_SYNC_WITH_TIMER_OSCILLIATOR,
    TIMER1_SOURCE_COUNTER_MODE_ASYNC,
            
}Timer1_SourceType;

typedef enum {
    TIMER1_PRESCALER_DIV_1,
    TIMER1_PRESCALER_DIV_2,
    TIMER1_PRESCALER_DIV_4,
    TIMER1_PRESCALER_DIV_8
            
}Timer1_PrescaleType;

typedef struct{
    Timer1_PrescaleType prescaler_value;
    Timer1_SourceType source_type;
    uint16                init_value;
    void (*Timer1_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Timer1_ConfigType;


/********************************** Software Interfaces Declarations *******************************/
Std_ReturnType Timer1_Init(const Timer1_ConfigType* _timer1);
Std_ReturnType Timer1_DeInit(const Timer1_ConfigType* _timer1);
Std_ReturnType Timer1_SetValue(const Timer1_ConfigType* _timer1, uint16 _value);
Std_ReturnType Timer1_GetTimeElapsed(const Timer1_ConfigType* _timer1, uint16* _value);
Std_ReturnType Timer1_GetRemaining(const Timer1_ConfigType* _timer1, uint16* _value);

/* For General use in the whole system */
Std_ReturnType Timer1_ActivateTimer1Oscillator(void);
Std_ReturnType Timer1_DeactivateTimer1Oscillator(void);


#endif	/* MCAL_TIMER1_H */

