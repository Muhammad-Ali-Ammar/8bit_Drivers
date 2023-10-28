/* 
 * File:   ecu_led.h
 * Author: isammar93
 *
 * Created on 24 ??????, 2022, 11:07 ?
 */

#ifndef ECU_LED_H
#define	ECU_LED_H


/********************************** Includes *****************************************/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_led_cfg.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/

typedef enum{
    LED_OFF,
    LED_ON
}Led_StatueType;

typedef enum{
    LED_SOURCE_CURRENT,
    LED_SINK_CURRENT
            
}Led_ConnectionType;


typedef struct{
    Dio_PinConfigType led_pin;
    Led_StatueType led_status;
    Led_ConnectionType led_connection;
    
}Led_ConfigType;
/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Led_Init(const Led_ConfigType* _led);
Std_ReturnType Led_TurnOff(const Led_ConfigType* _led);
Std_ReturnType Led_TurnOn(const Led_ConfigType* _led);
Std_ReturnType Led_Toggle(const Led_ConfigType* _led);



#endif	/* LED_H */

