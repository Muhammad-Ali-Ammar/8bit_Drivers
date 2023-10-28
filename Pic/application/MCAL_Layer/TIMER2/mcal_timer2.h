/* 
 * File:   mcal_timer2.h
 * Author: isammar93
 *
 * Created on 06 ?????, 2023, 01:54 ?
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H

/********************************** Includes *****************************************/
#include "../INTERRUPT/mcal_internal_interrupt.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/
/* Enable/Disable Timer 2 */
#define Timer2_Enable()                      (T2CONbits.TMR2ON = 1)
#define Timer2_Disable()                     (T2CONbits.TMR2ON = 0)

/* to select value of prescaler  */
#define Timer2_SetPrescalerValue(x)          (T2CONbits.T2CKPS = (x))


/* to select value of prescaler  */
#define Timer2_SetPostscalerValue(x)         (T2CONbits.TOUTPS = (x))

/********************************** Data Type Declarations *******************************/

typedef enum{
    
    TIMER2_PRESCALER_DIV_1,
    TIMER2_PRESCALER_DIV_4,
    TIMER2_PRESCALER_DIV_16
    
}Timer2_PrescalerTYpe;


typedef enum{
    
    TIMER2_POSTSCALER_DIV_1,
    TIMER2_POSTSCALER_DIV_2,
    TIMER2_POSTSCALER_DIV_3,
    TIMER2_POSTSCALER_DIV_4,
    TIMER2_POSTSCALER_DIV_5,
    TIMER2_POSTSCALER_DIV_6,
    TIMER2_POSTSCALER_DIV_7,
    TIMER2_POSTSCALER_DIV_8,
    TIMER2_POSTSCALER_DIV_9,
    TIMER2_POSTSCALER_DIV_10,
    TIMER2_POSTSCALER_DIV_11,
    TIMER2_POSTSCALER_DIV_12,
    TIMER2_POSTSCALER_DIV_13,
    TIMER2_POSTSCALER_DIV_14,
    TIMER2_POSTSCALER_DIV_15,
    TIMER2_POSTSCALER_DIV_16
    
}Timer2_PostscalerTYpe;

typedef struct{
    Timer2_PrescalerTYpe prescaler_value;
    Timer2_PostscalerTYpe postscaler_value;

    uint8               init_value;
    
    void (*Timer2_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Timer2_ConfigType;


/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Timer2_Init(const Timer2_ConfigType* _timer2);
Std_ReturnType Timer2_DeInit(const Timer2_ConfigType* _timer2);
Std_ReturnType Timer2_SetValue(const Timer2_ConfigType* _timer2, uint8 _value);
Std_ReturnType Timer2_GetTimeElapsed(const Timer2_ConfigType* _timer2, uint8* _value);
Std_ReturnType Timer2_GetRemaining(const Timer2_ConfigType* _timer2, uint8* _value);


#endif	/* MCAL_TIMER2_H */

