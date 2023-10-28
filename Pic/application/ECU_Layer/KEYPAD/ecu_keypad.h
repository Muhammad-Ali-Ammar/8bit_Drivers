/* 
 * File:   ecu_keypad.h
 * Author: isammar93
 *
 * Created on 31 ?????, 2023, 12:12 ?
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H


/********************************** Includes *****************************************/
#include     "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include    "ecu_keypad_cfg.h"

/********************************** Macros Declarations *******************************/

/* could be changed by the user */
#define KEYPAD_ROWS_NUMBER      4
#define KEYPAD_COLS_NUMBER      4


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/

typedef enum{
    
    KEYPAD_IDLE_VOLTAGE_LOW,
    KEYPAD_IDLE_VOLTAGE_HIGH
}Keypad_IdleVoltageType;


typedef enum{
    
    KEYPAD_ROW_CONTROL,
    KEYPAD_COL_CONTROL
}Keypad_ControllingPinsType;


typedef struct{
    Dio_PinConfigType keypad_rows_pins[KEYPAD_ROWS_NUMBER];
    Dio_PinConfigType keypad_cols_pins[KEYPAD_ROWS_NUMBER];
    Keypad_ControllingPinsType keypad_control_pins;
    Keypad_IdleVoltageType  keypad_idle_volt;
}Keypad_ConfigType;

/********************************** Software Interfaces Declarations *******************************/

/*******************************************Static functions ************************************/

static Std_ReturnType Keypad_DisableControlPins(const Keypad_ConfigType* _keypad);

/******************************* public interfaces */
Std_ReturnType Keypad_Init(const Keypad_ConfigType* _keypad);
Std_ReturnType Keypad_Read(const Keypad_ConfigType* _keypad, uint8* _value);


#endif	/* ECU_KEYPAD_H */

