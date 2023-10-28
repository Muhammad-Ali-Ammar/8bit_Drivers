/* 
 * File:   ecu_initialize.h
 * Author: isammar93
 *
 * Created on 31 ?????, 2023, 11:10 ?
 */

#ifndef ECU_INITIALIZE_H
#define	ECU_INITIALIZE_H

/********************************** Includes *****************************************/

#include "LED/ecu_led.h"
#include "BUTTON/ecu_button.h"
#include "RELAY/ecu_relay.h"
#include "DC_MOTOR/ecu_dc_motor.h"
#include "seven_segment/ecu_seven_segment.h"
#include "KEYPAD/ecu_keypad.h"
#include "LCD/ecu_lcd.h"
#include "RTC_DS1307/ecu_rtc.h"
#include "EXTERNAL_EEPROM_24C02C/ecu_external_eeprom_24C02C.h"
#include "TC74_TEMP_SENSOR/ecu_tc74_temp_sensor.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/




/********************************** Software Interfaces Declarations *******************************/

void Ecu_Init(void);

#endif	/* ECU_INITIALIZE_H */

