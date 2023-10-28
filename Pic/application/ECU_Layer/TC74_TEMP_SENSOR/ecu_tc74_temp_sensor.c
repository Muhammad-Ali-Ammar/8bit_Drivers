
/* 
 * File:   ecu_tc74_temp_sensor.c
 * Author:  Muhammad Ammar
 *
 * Created on 24 ?????, 2023, 11:14 ?
 */



/********************************** Includes *****************************************/
#include "ecu_tc74_temp_sensor.h"

/********************************** Private  definition  and declaration  *****************************************/


/********************************** Public Function Implementation  *****************************************/

Std_ReturnType Tc74_ReadTemp (const I2c_ConfigType* _i2c, uint8 _tc74_slave_address,uint8* _data){
    Std_ReturnType ret = E_OK;
    uint8 l_ack = 0;
    
    if(NULL == _i2c || NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (_tc74_slave_address<<1) ), &l_ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,TC74_REG_READ_ADDRESS, &l_ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (_tc74_slave_address<<1) |1 ), &l_ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _data, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    
    return ret;
}

/********************************** Private Function Implementation  *****************************************/
