/**************************************************************************/
/* Filename						: EXTERNAL_EEPROM_24C02C.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include <util/delay.h>
#include "../../../MCAL/DIO/include/DIO.h"

#include "../../../MCAL/I2C/include/I2C.h"
#include "../../include/EXTERNAL_EEPROM/EXTERNAL_EEPROM.h"

#include "../../include/EXTERNAL_EEPROM/EXTERNAL_EEPROM_config.h"
#include "../../include/EXTERNAL_EEPROM/EXTERNAL_EEPROM_private.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/

ExternalEeprom_StatusErrorType ExternalEeprom_WriteByte(u8 Copy_u8SlaveAddress,u8 Copy_u8PositionAddressInsideEerpom,u8 Copy_u8Data){
	ExternalEeprom_StatusErrorType Loc_enuExternlEepromStatus = EXTERNAL_EEPROM_STATUS_OK;
	u8 Loc_u8Temp;
	I2c_enuMasterTransmitStartConditionBlocking();
	I2c_enuMasterTransmitAddressWritingBlocking(Copy_u8SlaveAddress, &Loc_u8Temp);
	I2c_enuMasterTransmitDataWritingBlocking(Copy_u8PositionAddressInsideEerpom, &Loc_u8Temp);
	I2c_enuMasterTransmitDataWritingBlocking(Copy_u8Data, &Loc_u8Temp);
	I2c_enuMasterTransmitStopConditionBlocking();

	return Loc_enuExternlEepromStatus;

}
ExternalEeprom_StatusErrorType ExternalEeprom_ReadByte(u8 Copy_u8SlaveAddress,u8 Copy_u8PositionAddressInsideEerpom,u8* Address_Result){
	ExternalEeprom_StatusErrorType Loc_enuExternlEepromStatus = EXTERNAL_EEPROM_STATUS_OK;
	u8 Loc_u8Temp;
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(Copy_u8SlaveAddress, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(Copy_u8PositionAddressInsideEerpom, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(Copy_u8SlaveAddress, &Loc_u8Temp);
		_delay_ms(1);
		I2c_enuMasterReceiveDataBlocking(Address_Result,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		_delay_ms(1);
	return Loc_enuExternlEepromStatus;

}
//ExternalEeprom_StatusErrorType ExternalEeprom_ReadBytesNumber(u8 Copy_u8PositionAddressInsideEerpom,u8* Address_Result, u8 Copy_u8NumberOfBytes){
//	ExternalEeprom_StatusErrorType Loc_enuExternlEepromStatus = EXTERNAL_EEPROM_STATUS_OK;
//	u8 Loc_u8Temp;
//		I2c_enuMasterTransmitStartConditionBlocking();
//		I2c_enuMasterTransmitAddressWritingBlocking(0x50, &Loc_u8Temp);
//		I2c_enuMasterTransmitDataWritingBlocking(Copy_u8PositionAddressInsideEerpom, &Loc_u8Temp);
//		I2c_enuMasterTransmitStartConditionBlocking();
//		I2c_enuMasterTransmitAddressReadingBlocking(0x50, &Loc_u8Temp);
//
//		I2c_enuMasterReceiveDataBlocking(Address_Result,I2c_ACK_VALUE);
//		_delay_ms(1);
//		I2c_enuMasterReceiveDataBlocking(Address_Result+1,I2c_NACK_VALUE);
//		I2c_enuMasterTransmitStopConditionBlocking();
//		_delay_ms(1);
//		Address_Result[2]='\0';
//
//	return Loc_enuExternlEepromStatus;
//
//}

ExternalEeprom_StatusErrorType ExternalEeprom_WriteU8Array(u8 Copy_u8SlaveAddress,u8 Copy_u8StartPositionAddressInsideEerpom,u8 Array[], u8 Copy_u8NumbersOfByte){
	ExternalEeprom_StatusErrorType Loc_enuExternlEepromStatus = EXTERNAL_EEPROM_STATUS_OK;
	u8 Loc_u8Temp;
	u8 Loc_u8Counter = ZERO_VALUE;
	I2c_enuMasterTransmitStartConditionBlocking();
	I2c_enuMasterTransmitAddressWritingBlocking(Copy_u8SlaveAddress, &Loc_u8Temp);
	I2c_enuMasterTransmitDataWritingBlocking(Copy_u8StartPositionAddressInsideEerpom, &Loc_u8Temp);

	for(Loc_u8Counter = ZERO_VALUE; Loc_u8Counter<Copy_u8NumbersOfByte;Loc_u8Counter++){
		I2c_enuMasterTransmitDataWritingBlocking(Array[Loc_u8Counter], &Loc_u8Temp);
	}

	I2c_enuMasterTransmitStopConditionBlocking();

	_delay_ms(1);
	return Loc_enuExternlEepromStatus;

}

