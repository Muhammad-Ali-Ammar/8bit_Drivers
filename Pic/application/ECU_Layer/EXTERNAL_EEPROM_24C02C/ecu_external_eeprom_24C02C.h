/* 
 * File:   ecu_external_eeprom_24C02C.h
 * Author: Muhammad (Ali) Ammar
 *
 * Created on 16 ????, 2023, 02:10 ?
 */

#ifndef ECU_EXTERNAL_EEPROM_24C02C_H
#define	ECU_EXTERNAL_EEPROM_24C02C_H

/********************************** Includes *****************************************/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "../../MCAL_Layer/I2C/mcal_i2c.h"
#include "ecu_external_eeprom_24C02C_cfg.h"

/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/



/********************************** Software Interfaces Declarations *******************************/
Std_ReturnType ExternalEeprom_WriteByte(const I2c_ConfigType* _i2c, uint8 _eeprom_slave_address, uint8 _position_address, uint8 _data);
Std_ReturnType ExternalEeprom_ReadByte(const I2c_ConfigType* _i2c, uint8 _eeprom_slave_address, uint8 _position_address, uint8* _data);




#endif	/* ECU_EXTERNAL_EEPROM_24C02C_H */

