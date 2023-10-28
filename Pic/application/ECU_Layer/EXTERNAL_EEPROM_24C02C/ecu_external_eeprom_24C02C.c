/* 
 * File:   ecu_external_eeprom_24C02C.c
 * Author:  Muhammad Ammar
 *
 * Created on 24 ?????, 2023, 11:14 ?
 */



/********************************** Includes *****************************************/
#include "ecu_external_eeprom_24C02C.h"

/********************************** Private  definition  and declaration  *****************************************/


/********************************** Public Function Implementation  *****************************************/
Std_ReturnType ExternalEeprom_WriteByte(const I2c_ConfigType* _i2c, uint8 _eeprom_slave_address, uint8 _position_address, uint8 _data){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (_eeprom_slave_address<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,_position_address, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitDataBlocking(_i2c,_data, &ack); 
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    return ret;
}

Std_ReturnType ExternalEeprom_ReadByte(const I2c_ConfigType* _i2c, uint8 _eeprom_slave_address, uint8 _position_address, uint8* _data){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c || NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (_eeprom_slave_address<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,_position_address, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (_eeprom_slave_address<<1) |1 ), &ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _data, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
        
    }
    return ret;
}


/********************************** Private Function Implementation  *****************************************/
