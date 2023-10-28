    /* 
 * File:   mcal_external_interrupt.h
 * Author: Muhammad Ammar
 *
 * Created on 07 ????, 2023, 04:57 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H


/********************************** Includes *****************************************/
#include "mcal_interrupt_cfg.h"
#include "../GPIO/mcal_gpio.h"
/********************************** Macros Declarations *******************************/

#if INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/*  Macros For INT0         */
#define Int0_EnableInterrupt()              (INTCONbits.INT0E = 1)
#define Int0_DisableInterrupt()             (INTCONbits.INT0E = 0)
#define Int0_IsInterruptEnabled()           (INTCONbits.INT0E == 1)

#define Int0_ClearFlag()                    (INTCONbits.INT0IF = 0)
#define Int0_IsInterruptFired()             (INTCONbits.INT0IF == 1)

#define Int0_SetInterruptToRisingEdge()     (INTCON2bits.INTEDG0 = 1)
#define Int0_SetInterruptToFalingEdge()     (INTCON2bits.INTEDG0 = 0)
#define Int0_SetInterruptEdge(x)            (INTCON2bits.INTEDG0 = (x))


/*  Macros For INT1         */
#define Int1_EnableInterrupt()              (INTCON3bits.INT1E = 1)
#define Int1_DisableInterrupt()             (INTCON3bits.INT1E = 0)
#define Int1_IsInterruptEnabled()           (INTCON3bits.INT1E == 1)

#define Int1_ClearFlag()                    (INTCON3bits.INT1IF = 0)
#define Int1_IsInterruptFired()             (INTCON3bits.INT1IF == 1)

#define Int1_SetInterruptToRisingEdge()     (INTCON2bits.INTEDG1 = 1)
#define Int1_SetInterruptToFalingEdge()     (INTCON2bits.INTEDG1 = 0)
#define Int1_SetInterruptEdge(x)            (INTCON2bits.INTEDG1 = (x))



/*  Macros For INT2          */
#define Int2_EnableInterrupt()              (INTCON3bits.INT2E = 1)
#define Int2_DisableInterrupt()             (INTCON3bits.INT2E = 0)
#define Int2_IsInterruptEnabled()           (INTCON3bits.INT2E == 1)

#define Int2_ClearFlag()                    (INTCON3bits.INT2IF = 0)
#define Int2_IsInterruptFired()             (INTCON3bits.INT2IF == 1)

#define Int2_SetInterruptToRisingEdge()     (INTCON2bits.INTEDG2 = 1)
#define Int2_SetInterruptToFalingEdge()     (INTCON2bits.INTEDG2 = 0)
#define Int2_SetInterruptEdge(x)            (INTCON2bits.INTEDG2 = (x))

/*   This section for Prioity */
#if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Int1_SetHighPrioirty()              (INTCON3bits.INT1IP = 1)
#define Int1_SetLowPrioirty()               (INTCON3bits.INT1IP = 0)
#define Int1_SetPrioirty(x)                 (INTCON3bits.INT1IP = (x))


#define Int2_SetHighPrioirty()              (INTCON3bits.INT2IP = 1)
#define Int2_SetLowPrioirty()               (INTCON3bits.INT2IP = 0)
#define Int2_SetPrioirty(x)                 (INTCON3bits.INT2IP = (x))
#endif

#endif

///////////////////////////////////////////////////////////////////////////////

#if INTERRUPT_IOC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Ioc_EnableInterrupt()              (INTCONbits.RBIE = 1)
#define Ioc_DisableInterrupt()             (INTCONbits.RBIE = 0)
#define Ioc_IsInterruptEnabled()           (INTCONbits.RBIE == 1)


#define IOC_ClearFlag()                    (INTCONbits.RBIF = 0)
#define Ioc_IsInterruptFired()             (INTCONbits.RBIF == 1)



/*   This section for Prioity */
#if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Ioc_SetHighPrioirty()           (INTCON2bits.RBIP = 1)
#define Ioc_SetLowPrioirty()            (INTCON2bits.RBIP = 0)
#define Ioc_SetPrioirty(x)              (INTCON2bits.RBIP = (x))


#endif


#endif

/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/
#if INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

typedef enum {
 
    INTx_INT0,
    INTx_INT1,
    INTx_INT2
}Intx_PinIndexType;

typedef enum {
 
    INTx_FAILING_EDGE,
    INTx_RISING_EDGE
}Intx_EdgeType;

typedef struct{
    Dio_PinConfigType pin;
    void (*Intx_InterruptHandler)(void);
    Intx_EdgeType edge;
    Intx_PinIndexType intx_number;
    
    Interrupt_PrioityType priority;

    
}Intx_ConfigPinType;



#endif


#if INTERRUPT_IOC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE


typedef enum{
    IOC_KBI0,
    IOC_KBI1,
    IOC_KBI2,
    IOC_KBI3
            
}Ioc_NumberType;


typedef struct{
    Dio_PinConfigType pin;
    void (*Ioc_UserInterruptHandler)(void);
    Interrupt_PrioityType priority;
    Ioc_NumberType number;

    
}Ioc_ConfigPinType;

#endif


/********************************** Software Interfaces Declarations *******************************/

#if INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

Std_ReturnType Intx_Init(const Intx_ConfigPinType* _intx_obj);
Std_ReturnType Intx_DeInit(const Intx_ConfigPinType* _intx_obj);

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

#endif



#if INTERRUPT_IOC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE


Std_ReturnType Ioc_Init(const Ioc_ConfigPinType* _ioc_obj);
Std_ReturnType Ioc_DeInit(const Ioc_ConfigPinType* _ioc_obj);

void IOC_ISR(void);
void IOC0_ISR(void);
void IOC1_ISR(void);
void IOC2_ISR(void);
void IOC3_ISR(void);

#endif






#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

