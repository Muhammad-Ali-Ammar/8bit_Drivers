/* 
 * File:   mcal_ccp1.h
 * Author: isammar93
 *
 * Created on 22 ?????, 2023, 07:51 ?
 */

#ifndef MCAL_CCP1_H
#define	MCAL_CCP1_H

/********************************** Includes *****************************************/
#include "../mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "mcal_ccp1_cfg.h"

/********************************** Macros Declarations *******************************/

#if CCP1_CFG_CAPTURE_MODE_SELECTED == CCP1_MODULE_ENABLE

#elif CCP1_CFG_COMPARE_MODE_SELECTED == CCP1_MODULE_ENABLE

#elif CCP1_CFG_PWM_MODE_SELECTED == CCP1_MODULE_ENABLE

#else 

#endif 

/********************************** Macros Function Declarations *******************************/

#if CCP1_CFG_CAPTURE_MODE_SELECTED == CCP1_MODULE_ENABLE

#define CAPTURE1_SET_EDGE(_X_)          (CCP1CONbits.CCP1M = (_X_))
#define Capture1_IsReady()              (PIR1bits.CCP1IF == 1)

#elif CCP1_CFG_COMPARE_MODE_SELECTED == CCP1_MODULE_ENABLE
#define COMPARE1_SET_MODE(_X_)          (CCP1CONbits.CCP1M = (_X_))
#define Compare1_IsReady()              (PIR1bits.CCP1IF == 1)

#elif CCP1_CFG_PWM_MODE_SELECTED == CCP1_MODULE_ENABLE

#define PWM1_ENABLE()                    (CCP1CONbits.CCP1M = (0b1100))
#define PWM1_DISABLE()                   (CCP1CONbits.CCP1M = (0b0000))


#else 

#endif 



/********************************** Data Type Declarations *******************************/
#if CCP1_CFG_CAPTURE_MODE_SELECTED == CCP1_MODULE_ENABLE
    
typedef enum{
    CAPTURE1_EDGE_DISABLE_MODULE = 0,
    CAPTURE1_EDGE_FALLING = 0b0100,
    CAPTURE1_EDGE_RISING = 0b0101,
    CAPTURE1_EDGE_4TH_RISING,
    CAPTURE1_EDGE_16TH_RISING
      
}Capture1_EdgeType;

    
typedef enum{
    CAPTURE1_TIMER1_CCP1_CCP2 = 0,
    CAPTURE1_TIMER1_CCP1_TIMER2_CCP2 ,
    CAPTURE1_TIMER3_CCP1_CCP2
      
}Capture1_TimerSouceType;



typedef struct {
    Capture1_EdgeType edge;
    Capture1_TimerSouceType timer_source;
    void (*Capture1_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Capture1_ConfigType;


#elif CCP1_CFG_COMPARE_MODE_SELECTED == CCP1_MODULE_ENABLE
typedef enum{
    COMPARE1_MODE_DISABLE = 0,
    COMPARE1_MODE_TOGGLE_CCP1 = 0b0010,
    COMPARE1_MODE_SET_CPP1_HIGH = 0b1000,
    COMPARE1_MODE_SET_CPP1_LOW,
    COMPARE1_MODE_FIRE_INTERRUPT,
    COMPARE1_MODE_CLEAR_TIMER,
      
}Compare1_ModeType;

typedef enum{
    COMPARE1_TIMER1_CCP1_CCP2 = 0,
    COMPARE1_TIMER1_CCP1_TIMER2_CCP2 ,
    COMPARE1_TIMER3_CCP1_CCP2
      
}Compare1_TimerSouceType;


typedef struct {
    Compare1_ModeType mode;
    Compare1_TimerSouceType timer_source;
    uint16          init_value;
    void (*Compare1_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Compare1_ConfigType;




#elif CCP1_CFG_PWM_MODE_SELECTED == CCP1_MODULE_ENABLE

typedef enum{
    
    PWM1_TIMER2_PRESCALER_DIV_1 =1,
    PWM1_TIMER2_PRESCALER_DIV_4 =4,
    PWM1_TIMER2_PRESCALER_DIV_16 =16
    
}Pwm1_PrescalerType;

typedef struct {
    
    uint32      frequancy;
    Pwm1_PrescalerType timer2_prescaler;
    
}Pwm1_ConfigType;

#else 
        /* None of them is used... */
#endif 




/********************************** Software Interfaces Declarations *******************************/

#if CCP1_CFG_CAPTURE_MODE_SELECTED == CCP1_MODULE_ENABLE

Std_ReturnType Capture1_Init(const Capture1_ConfigType* _capture);
Std_ReturnType Capture1_DeInit(const Capture1_ConfigType* _capture);
Std_ReturnType Capture1_GetValue(const Capture1_ConfigType* _capture, uint16* _value);
Std_ReturnType Capture1_ChangeEdge(const Capture1_ConfigType* _capture, Capture1_EdgeType _edge);

        
#elif CCP1_CFG_COMPARE_MODE_SELECTED == CCP1_MODULE_ENABLE
Std_ReturnType Compare1_Init(const Compare1_ConfigType* _compare);
Std_ReturnType Compare1_DeInit(const Compare1_ConfigType* _compare);
Std_ReturnType Compare1_SetValue(const Compare1_ConfigType* _compare, uint16 _value);

#elif CCP1_CFG_PWM_MODE_SELECTED == CCP1_MODULE_ENABLE
Std_ReturnType Pwm1_Init(const Pwm1_ConfigType* _pwm);
Std_ReturnType Pwm1_DeInit(const Pwm1_ConfigType* _pwm);
Std_ReturnType Pwm1_SetDutyCycle(const Pwm1_ConfigType* _pwm, uint8 _duty_cycle_precentage);
Std_ReturnType Pwm1_Stop(const Pwm1_ConfigType* _pwm);

#else 

#endif 




#endif	/* MCAL_CCP1_H */

