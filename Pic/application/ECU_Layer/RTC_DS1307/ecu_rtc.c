/* 
 * File:   ecu_rtc.c
 * Author:  Muhammad Ammar
 *
 * Created on 24 ?????, 2023, 11:14 ?
 */



/********************************** Includes *****************************************/
#include "ecu_rtc.h"

/********************************** Private  definition  and declaration  *****************************************/


/********************************** Public Function Implementation  *****************************************/
Std_ReturnType Rtc_GetSecond(const I2c_ConfigType* _i2c, uint8* _second){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c || NULL == _second){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,RTC_SECOND_REG_ADDRESS, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) |1 ), &ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _second, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    
    return ret;
}
Std_ReturnType Rtc_GetMinute(const I2c_ConfigType* _i2c, uint8* _minute){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c || NULL == _minute){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,RTC_MINUTE_REG_ADDRESS, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) |1 ), &ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _minute, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    
    return ret;
}
Std_ReturnType Rtc_GetHour(const I2c_ConfigType* _i2c, uint8* _hour){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c || NULL == _hour){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,RTC_HOUR_REG_ADDRESS, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) |1 ), &ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _hour, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    
    return ret;
}


Std_ReturnType Rtc_GetDay(const I2c_ConfigType* _i2c, uint8* _day){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c || NULL == _day){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,RTC_DAY_REG_ADDRESS, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) |1 ), &ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _day, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    
    return ret;
}
Std_ReturnType Rtc_GetMonth(const I2c_ConfigType* _i2c, uint8* _month){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c || NULL == _month){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,RTC_MONTH_REG_ADDRESS, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) |1 ), &ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _month, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    
    return ret;
}
Std_ReturnType Rtc_GetYear(const I2c_ConfigType* _i2c, uint8* _year){
    Std_ReturnType ret = E_OK;
    uint8 ack =0;
    if(NULL == _i2c || NULL == _year){
        ret = E_NOT_OK;
    }
    else{
        ret &= I2c_MasterTransmitStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) ), &ack); /* address + W */
        ret &= I2c_MasterTransmitDataBlocking(_i2c,RTC_YEAR_REG_ADDRESS, &ack);     /* register name */ 
        ret &= I2c_MasterTransmitRepeatedStartConditionBlocking(_i2c);
        ret &= I2c_MasterTransmitDataBlocking(_i2c,(uint8)( (RTC_ADDRESS_7BIT<<1) |1 ), &ack); /* address + R*/
        ret &= I2c_MasterReceiveDataBlocking(_i2c, _year, 1);
        ret &= I2c_MasterTransmitStopConditionBlocking(_i2c);
    }
    
    return ret;
}

Std_ReturnType Rtc_GetTimeAndDate(const I2c_ConfigType* _i2c, Rtc_Type* _rtc_data){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _i2c || NULL == _rtc_data){
        ret = E_NOT_OK;
    }
    else{
        
        ret &= Rtc_GetSecond(_i2c, &(_rtc_data->second));
        ret &= Rtc_GetMinute(_i2c, &(_rtc_data->minute));
        ret &= Rtc_GetHour  (_i2c, &(_rtc_data->hour));
        
        ret &= Rtc_GetDay   (_i2c, &(_rtc_data->day));
        ret &= Rtc_GetMonth (_i2c, &(_rtc_data->month));
        ret &= Rtc_GetYear  (_i2c, &(_rtc_data->year));
    }
    
    return ret;
}


Std_ReturnType Convert_BCDToInt(uint8 _bcd_data, uint8* _answer){
    Std_ReturnType ret = E_OK;
    uint8 l_answer = 0;
    
    if( NULL == _answer){
        ret = E_NOT_OK;
    }
    else{
        while(_bcd_data != 0){
            
            *_answer = (*_answer*10) + (_bcd_data &0xF);
            _bcd_data>>=4;
        }
        
    }
    
    return ret; 
}

/********************************** Private Function Implementation  *****************************************/















