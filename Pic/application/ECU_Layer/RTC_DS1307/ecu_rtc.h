/* 
 * File:   ecu_rtc.h
 * Author: Muhammad (Ali) Ammar
 *
 * Created on 16 ????, 2023, 01:35 ?
 */

#ifndef ECU_RTC_H
#define	ECU_RTC_H

/********************************** Includes *****************************************/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "../../MCAL_Layer/I2C/mcal_i2c.h"


/********************************** Macros Declarations *******************************/

#define RTC_ADDRESS_7BIT                ((uint8)(0b1101000))
#define RTC_SECOND_REG_ADDRESS          ((uint8)(0x00))
#define RTC_MINUTE_REG_ADDRESS          ((uint8)(0x01))
#define RTC_HOUR_REG_ADDRESS            ((uint8)(0x02))

#define RTC_DAY_REG_ADDRESS             ((uint8)(0x04))
#define RTC_MONTH_REG_ADDRESS           ((uint8)(0x05))
#define RTC_YEAR_REG_ADDRESS            ((uint8)(0x06))


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/


typedef struct{
    uint8 second;
    uint8 minute;
    uint8 hour;
    
    uint8 day;
    uint8 month;
    uint8 year;
    
}Rtc_Type;


/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Rtc_GetSecond(const I2c_ConfigType* _i2c, uint8* _second);
Std_ReturnType Rtc_GetMinute(const I2c_ConfigType* _i2c, uint8* _minute);
Std_ReturnType Rtc_GetHour(const I2c_ConfigType* _i2c, uint8* _hour);


Std_ReturnType Rtc_GetDay(const I2c_ConfigType* _i2c, uint8* _day);
Std_ReturnType Rtc_GetMonth(const I2c_ConfigType* _i2c, uint8* _month);
Std_ReturnType Rtc_GetYear(const I2c_ConfigType* _i2c, uint8* _year);

Std_ReturnType Rtc_GetTimeAndDate(const I2c_ConfigType* _i2c, Rtc_Type* _rtc_data);

Std_ReturnType Convert_BCDToInt(uint8 _bcd_data, uint8* _answer);


#endif	/* ECU_RTC_H */

