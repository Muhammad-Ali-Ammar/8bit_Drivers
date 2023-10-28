/* 
 * File:   mcal_interrupt_cfg.h
 * Author: isammar93
 *
 * Created on 07 ????, 2023, 04:56 ?
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H


/********************************** Includes *****************************************/
#include "../mcal_std_types.h"
#include "pic18f4620.h"
#include "mcal_interrupt_generated_cfg.h"
/********************************** Macros Declarations *******************************/
#define INTERRUPT_ENABLE        1
#define INTERRUPT_DISABLE       0

#define INTERRUPT_FIRED         1
#define INTERRUPT_NOT_FIRED     0

#define INTERRUPT_PRIOIRTY_ENABLE       1
#define INTERRUPT_PRIOIRTY_DISABLE      0

/********************************** Macros Function Declarations *******************************/

#if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

#define Interrupt_EnablePrioirtyOfTheSystem()            (RCONbits.IPEN = 1)
#define Interrupt_DisablePrioirtyOfTheSystem()           (RCONbits.IPEN = 0)



/*This for  high prioirty global interrupts */
#define Interrupt_EnableHighGlobalInterrupt()            (INTCONbits.GIEH = 1)
#define Interrupt_DisableHighGlobalInterrupt()           (INTCONbits.GIEH = 0)


/*This for  low prioirty global interrupts */
#define Interrupt_EnableLowGlobalInterrupt()            (INTCONbits.GIEL = 1)
#define Interrupt_DisableLowGlobalInterrupt()           (INTCONbits.GIEL = 0)


/* For other peripheral*/
#define Interrupt_GetInterruptStatus()                  (INTCONbits.GIE_GIEH)
#define Interrupt_SetInterruptStatus(x)                 (INTCONbits.GIE_GIEH = (x))
#define Interrupt_Disable()                    (INTCONbits.GIE_GIEH = 0)


#else 

/* this for global enable*/
#define Interrupt_EnableGlobalInterrupt()            (INTCONbits.GIE = 1)
#define Interrupt_DisableGlobalInterrupt()           (INTCONbits.GIE = 0)

/*This for peripheral enable*/
#define Interrupt_EnablePeripheralInterrupt()            (INTCONbits.PEIE = 1)
#define Interrupt_DisablePeripheralInterrupt()           (INTCONbits.PEIE = 0)


/* For other peripheral*/
#define Interrupt_GetInterruptStatus()                  (INTCONbits.GIE_GIEH)
#define Interrupt_SetInterruptStatus(x)                 (INTCONbits.GIE_GIEH = (x))
#define Interrupt_Disable()                             (INTCONbits.GIE_GIEH = 0)

#endif

/********************************** Data Type Declarations *******************************/
typedef enum{
    INTERRUPT_LOW_PRIOIRTY,
    INTERRUPT_HIGH_PRIOIRTY
}Interrupt_PrioityType;


/********************************** Software Interfaces Declarations *******************************/
#endif	/* MCAL_INTERRUPT_CFG_H */

