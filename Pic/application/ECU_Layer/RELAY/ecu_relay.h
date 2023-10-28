/* 
 * File:   ecu_relay.h
 * Author: isammar93
 *
 * Created on 28 ?????, 2023, 09:38 ?
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


/********************************** Includes *****************************************/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_relay_cfg.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/

typedef enum {
    RELAY_OFF,
    RELAY_ON
}Relay_StatusType;

typedef struct{
    Dio_PinConfigType relay_pin;
    Relay_StatusType relay_state;
    
}Relay_ConfigType;

/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Relay_Init(const Relay_ConfigType* _relay);
Std_ReturnType Relay_TurnOn(const Relay_ConfigType* _relay);
Std_ReturnType Relay_TurnOff(const Relay_ConfigType* _relay);



#endif	/* ECU_RELAY_H */

