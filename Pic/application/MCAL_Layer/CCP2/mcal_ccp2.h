/* 
 * File:   mcal_ccp2.h
 * Author: isammar93
 *
 * Created on 22 ?????, 2023, 07:51 ?
 */

#ifndef MCAL_CCP2_H
#define	MCAL_CCP2_H

/********************************** Includes *****************************************/
#include "../mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "mcal_ccp2_cfg.h"

/********************************** Macros Declarations *******************************/

#if CCP2_CFG_CAPTURE_MODE_SELECTED == CCP2_MODULE_ENABLE

#elif CCP2_CFG_COMPARE_MODE_SELECTED == CCP2_MODULE_ENABLE

#elif CCP2_CFG_PWM_MODE_SELECTED == CCP2_MODULE_ENABLE

#else 

#endif 

/********************************** Macros Function Declarations *******************************/
#if CCP2_CFG_CAPTURE_MODE_SELECTED == CCP2_MODULE_ENABLE

#define CAPTURE2_SET_EDGE(_X_)          (CCP2CONbits.CCP2M = (_X_))
#define Capture2_IsReady()              (PIR1bits.CCP2IF == 1)

#elif CCP2_CFG_COMPARE_MODE_SELECTED == CCP2_MODULE_ENABLE
#define COMPARE2_SET_MODE(_X_)          (CCP2CONbits.CCP2M = (_X_))
#define Compare2_IsReady()              (PIR1bits.CCP2IF == 1)

#elif CCP2_CFG_PWM_MODE_SELECTED == CCP2_MODULE_ENABLE

#define PWM2_ENABLE()                    (CCP2CONbits.CCP2M = (0b1100))
#define PWM2_DISABLE()                   (CCP2CONbits.CCP2M = (0b0000))


#else 

#endif 



/********************************** Data Type Declarations *******************************/
#if CCP2_CFG_CAPTURE_MODE_SELECTED == CCP2_MODULE_ENABLE
    
typedef enum{
    CAPTURE2_EDGE_DISABLE_MODULE = 0,
    CAPTURE2_EDGE_FALLING = 0b0100,
    CAPTURE2_EDGE_RISING,
    CAPTURE2_EDGE_4TH_RISING,
    CAPTURE2_EDGE_16TH_RISING
      
}Capture2_EdgeType;

typedef enum{
    CAPTURE2_TIMER1_CCP1_CCP2 = 0,
    CAPTURE2_TIMER1_CCP1_TIMER2_CCP2 ,
    CAPTURE2_TIMER3_CCP1_CCP2
      
}Capture2_TimerSouceType;


typedef struct {
    Capture2_EdgeType edge;
    Capture2_TimerSouceType timer_source;
    void (*Capture2_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Capture2_Type;


#elif CCP2_CFG_COMPARE_MODE_SELECTED == CCP2_MODULE_ENABLE
typedef enum{
    COMPARE2_MODE_DISABLE = 0,
    COMPARE2_MODE_TOGGLE_CCP2 = 0b0010,
    COMPARE2_MODE_SET_CCP2_HIGH = 0b1000,
    COMPARE2_MODE_SET_CCP2_LOW,
    COMPARE2_MODE_FIRE_INTERRUPT,
    COMPARE2_MODE_CLEAR_TIMER_START_ADC,
      
}Compare2_ModeType;

typedef enum{
    COMPARE2_TIMER1_CCP1_CCP2 = 0,
    COMPARE2_TIMER1_CCP1_TIMER2_CCP2 ,
    COMPARE2_TIMER3_CCP1_CCP2
      
}Compare2_TimerSouceType;



typedef struct {
    Compare2_ModeType mode;
    Compare2_TimerSouceType timer_source;
    uint16          init_value;
    void (*Compare2_InterruptHandler)(void);
    Interrupt_PrioityType priority;
}Compare2_ConfigType;




#elif CCP2_CFG_PWM_MODE_SELECTED == CCP2_MODULE_ENABLE

typedef enum{
    
    PWM2_TIMER2_PRESCALER_DIV_1 =1,
    PWM2_TIMER2_PRESCALER_DIV_4 =4,
    PWM2_TIMER2_PRESCALER_DIV_16 =16
    
}Pwm2_PrescalerType;

typedef struct {
    
    uint32      frequancy;
    Pwm2_PrescalerType timer2_prescaler;
    
}Pwm2_ConfigType;

#else 
        /* None of them is used... */
#endif 




/********************************** Software Interfaces Declarations *******************************/

#if CCP2_CFG_CAPTURE_MODE_SELECTED == CCP2_MODULE_ENABLE

Std_ReturnType Capture2_Init(const Capture2_Type* _capture);
Std_ReturnType Capture2_DeInit(const Capture2_Type* _capture);
Std_ReturnType Capture2_GetValue(const Capture2_Type* _capture, uint16* _value);
Std_ReturnType Capture2_ChangeEdge(const Capture2_ConfigType* _capture, Capture2_EdgeType _edge);

        
#elif CCP2_CFG_COMPARE_MODE_SELECTED == CCP2_MODULE_ENABLE
Std_ReturnType Compare2_Init(const Compare2_ConfigType* _compare);
Std_ReturnType Compare2_DeInit(const Compare2_ConfigType* _compare);
Std_ReturnType Compare2_SetValue(const Compare2_ConfigType* _compare, uint16 _value);

#elif CCP2_CFG_PWM_MODE_SELECTED == CCP2_MODULE_ENABLE
Std_ReturnType Pwm2_Init(const Pwm2_ConfigType* _pwm);
Std_ReturnType Pwm2_DeInit(const Pwm2_ConfigType* _pwm);
Std_ReturnType Pwm2_SetDutyCycle(const Pwm2_ConfigType* _pwm, uint8 _duty_cycle_precentage);
Std_ReturnType Pwm2_Stop(const Pwm2_ConfigType* _pwm);

#else 

#endif 




#endif	/* MCAL_CCP2_H */

