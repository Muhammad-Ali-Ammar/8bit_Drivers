/* 
 * File:   ecu_tc74_temp_sensor.h
 * Author: Muammad (Ali) Ammar
 *
 * Created on 16 ????, 2023, 05:09 ?
 */

#ifndef ECU_TC74_TEMP_SENSOR_H
#define	ECU_TC74_TEMP_SENSOR_H


/********************************** Includes *****************************************/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "../../MCAL_Layer/I2C/mcal_i2c.h"

/********************************** Macros Declarations *******************************/

#define TC74A0_ADDRESS        (0b1001000)
#define TC74A1_ADDRESS        (0b1001001)
#define TC74A2_ADDRESS        (0b1001010)
#define TC74A3_ADDRESS        (0b1001011)
#define TC74A4_ADDRESS        (0b1001100)
#define TC74A5_ADDRESS        (0b1001101)
#define TC74A6_ADDRESS        (0b1001110)
#define TC74A7_ADDRESS        (0b1001111)

#define TC74_REG_READ_ADDRESS  (0x00)

/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/



/********************************** Software Interfaces Declarations *******************************/
Std_ReturnType Tc74_ReadTemp (const I2c_ConfigType* _i2c, uint8 _tc74_slave_address,uint8* _data);




#endif	/* ECU_TC74_TEMP_SENSOR_H */

