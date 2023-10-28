/* 
 * File:   ecu_button.h
 * Author: ammar
 *
 * Created on 27 1 2023, 08:39 ?
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/********************************** Includes *****************************************/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_button_cfg.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/

typedef enum{
    BUTTON_NOT_PRESSED,
    BUTTON_PRESSED
}Button_StatusType;


typedef enum{
    BUTTON_PULL_UP,
    BUTTON_PULL_DOWN
}Button_ConnectionType;


typedef struct{
    Dio_PinConfigType button_pin;
    Button_StatusType button_status;
    Button_ConnectionType button_connection;
    
}Button_ConfigType;

/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Button_Init(const Button_ConfigType *_btn);
Std_ReturnType Button_Read(const Button_ConfigType *_btn,Button_StatusType* _state );


#endif	/* ECU_BUTTON_H */

