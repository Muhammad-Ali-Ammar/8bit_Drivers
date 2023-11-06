/**************************************************************************/
/* Filename						: EXTERNAL_EEPROM_24C02C.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef HAL_INCLUDE_EXTERNAL_EEPROM_EXTERNAL_EEPROM_H_
#define HAL_INCLUDE_EXTERNAL_EEPROM_EXTERNAL_EEPROM_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


typedef enum{
	EXTERNAL_EEPROM_STATUS_OK,
	EXTERNAL_EEPROM_STATUS_FAIL,
	EXTERNAL_EEPROM_STATUS_NULL_POINTER_ADDRESS
}ExternalEeprom_StatusErrorType;


/********************************** Software Interfaces Declarations *******************/
ExternalEeprom_StatusErrorType ExternalEeprom_WriteByte(u8 Copy_u8SlaveAddress,u8 Copy_u8PositionAddressInsideEerpom,u8 Copy_u8Data);
ExternalEeprom_StatusErrorType ExternalEeprom_ReadByte(u8 Copy_u8SlaveAddress,u8 Copy_u8PositionAddressInsideEerpom,u8* Address_Result);
//ExternalEeprom_StatusErrorType ExternalEeprom_ReadBytesNumber(u8 Copy_u8PositionAddressInsideEerpom,u8* Address_Result, u8 Copy_u8NumberOfBytes);
ExternalEeprom_StatusErrorType ExternalEeprom_WriteU8Array(u8 Copy_u8SlaveAddress,u8 Copy_u8StartPositionAddressInsideEerpom,u8 Array[], u8 Copy_u8NumbersOfByte);

#endif /* HAL_INCLUDE_EXTERNAL_EEPROM_EXTERNAL_EEPROM_H_ */
