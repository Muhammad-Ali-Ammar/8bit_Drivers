/* 
 * File:   mcal_timer0.h
 * Author: isammar93
 *
 * Created on 04 ?????, 2023, 03:12 ?
 */

#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H

/********************************** Includes *****************************************/


#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/********************************** Macros Declarations *******************************/

#define TiMER0_DISABLE_PRESCALER                    1
#define TiMER0_ENABLE_PRESCALER                     0


#define TIMER0_COUNTER_MODE                         1
#define TIMER0_TIMER_MODE                           0
/********************************** Macros Function Declarations *******************************/

/* to select value of prescaler  */
#define Timer0_SetPrescalerValue(x)          (T0CONbits.T0PS = (x))

/*to enable or disable prescaler */
#define Timer0_SetPrescalerState(x)          (T0CONbits.PSA = (x))

/* Choose source edge of counter mode */
#define Timer0_SetEdgeSelect(x)              (T0CONbits.T0SE = (x))

/* Choose Clock source */
#define Timer0_SetClockSource(x)             (T0CONbits.T0CS = (x))

/* Choose Timer resulution */
#define Timer0_SetRegisterResolution(x)      (T0CONbits.T08BIT = (x))


/* Enable/Disable Timer 0 */
#define Timer0_Enable()                      (T0CONbits.TMR0ON = 1)
#define Timer0_Disable()                     (T0CONbits.TMR0ON = 0)


#define Timer0_ClearFlagBit()                   (INTCONbits.T0IF = 0)
#define Timer0_IsFlagFired()                    (INTCONbits.T0IF == 0)
/********************************** Data Type Declarations *******************************/
typedef enum{
    
    TIMER0_PRESCALER_DIV_2,
    TIMER0_PRESCALER_DIV_4,
    TIMER0_PRESCALER_DIV_8,
    TIMER0_PRESCALER_DIV_16,
    TIMER0_PRESCALER_DIV_32,
    TIMER0_PRESCALER_DIV_64,
    TIMER0_PRESCALER_DIV_128,
    TIMER0_PRESCALER_DIV_256,
    TIMER0_PRESCALER_NO_DIV,
    
}Timer0_PrescalerTYpe;

typedef enum{
    TIMER0_SOURCE_COUNTER_MODE_RAISING_EDGE,
    TIMER0_SOURCE_COUNTER_MODE_FAILING_EDGE,
    TIMER0_SOURCE_TIMER_MODE
}Timer0_SourceType;

typedef enum{
    TIMER0_RESOLUTION_16_BIT,
    TIMER0_RESOLUTION_8_BIT,
}Timer0_ResolutionType;

typedef struct{
    Timer0_PrescalerTYpe prescaler_value;
    Timer0_SourceType source_type;
    Timer0_ResolutionType resolution_bits;
    uint16                init_value;
    void (*Timer0_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Timer0_ConfigType;


/********************************** Software Interfaces Declarations *******************************/
Std_ReturnType Timer0_Init(const Timer0_ConfigType* _timer0);
Std_ReturnType Timer0_DeInit(const Timer0_ConfigType* _timer0);
Std_ReturnType Timer0_SetValue(const Timer0_ConfigType* _timer0, uint16 _value);
Std_ReturnType Timer0_GetTimeElapsed(const Timer0_ConfigType* _timer0, uint16* _value);
Std_ReturnType Timer0_GetRemaining(const Timer0_ConfigType* _timer0, uint16* _value);


#endif	/* MCAL_TIMER0_H */

