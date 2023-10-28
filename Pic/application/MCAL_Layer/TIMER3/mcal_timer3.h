/* 
 * File:   mcal_timer3.h
 * Author: 
 *
 * Created on 20 ?????, 2023, 09:07 ?
 */

#ifndef MCAL_TIMER3_H
#define	MCAL_TIMER3_H

/********************************** Includes *****************************************/
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/********************************** Macros Declarations *******************************/
#define TIMER3_COUNTER_MODE_AND_TIMER1_OSCILLATOR                        1
#define TIMER3_TIMER_MODE_WITH_INTERNAL_OSCILLATOR                       0

/********************************** Macros Function Declarations *******************************/

/* Enable/Disable Timer 3 */
#define Timer3_Enable()                                   (T3CONbits.TMR3ON = 1)
#define Timer3_Disable()                                  (T3CONbits.TMR3ON = 0)

/* Choose Clock source */
#define Timer3_SetClockSource(_x_)                        (T3CONbits.TMR3CS = (_x_))

/* choose synchronization counter mode with timer1 clock */
#define Timer3_SetCounterModeSync(_x_)                   (T3CONbits.T3SYNC = (_x_))
#define Timer3_EnableSyncWithTimer1Oscillator()          (T3CONbits.T3SYNC = 0)
#define Timer3_DisableSyncWithTimer1Oscillator()         (T3CONbits.T3SYNC = 1)

/*to enable or disable prescaler */
#define Timer3_SetPrescalerValue(_x_)                       (T3CONbits.T3CKPS = (_x_))

/* set read/write in 8 or 16 bit instruciton */
#define Timer3_EnableWR16Operation()                      (T3CONbits.RD16 = 1)
#define Timer3_EnableWR8Operation()                       (T3CONbits.RD16 = 0)
#define Timer3_SetWRnBitOperation(_x_)                    (T3CONbits.RD16 = (_x_))

/********************************** Data Type Declarations *******************************/

typedef enum {
    TIMER3_SOURCE_TIMER_MODE_WITH_INTERNAL_OSCILLIATOR,
    TIMER3_SOURCE_TIMER_MODE_WITH_TIMER1_OSCILLIATOR,
    TIMER3_SOURCE_COUNTER_MODE_SYNC_WITH_TIMER_OSCILLIATOR,
    TIMER3_SOURCE_COUNTER_MODE_ASYNC,
            
}Timer3_SourceType;


typedef enum {
    TIMER3_PRESCALER_DIV_1,
    TIMER3_PRESCALER_DIV_2,
    TIMER3_PRESCALER_DIV_4,
    TIMER3_PRESCALER_DIV_8
            
}Timer3_PrescaleType;

typedef struct{
    Timer3_PrescaleType prescaler_value;
    Timer3_SourceType source_type;
    uint16                init_value;
    void (*Timer3_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Timer3_ConfigType;

/********************************** Software Interfaces Declarations *******************************/
Std_ReturnType Timer3_Init(const Timer3_ConfigType* _timer3);
Std_ReturnType Timer3_DeInit(const Timer3_ConfigType* _timer3);
Std_ReturnType Timer3_SetValue(const Timer3_ConfigType* _timer3, uint16 _value);
Std_ReturnType Timer3_GetTimeElapsed(const Timer3_ConfigType* _timer3, uint16* _value);
Std_ReturnType Timer3_GetRemaining(const Timer3_ConfigType* _timer3, uint16* _value);

#endif	/* MCAL_TIMER3_H */

