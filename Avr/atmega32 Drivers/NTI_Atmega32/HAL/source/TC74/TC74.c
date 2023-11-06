/**************************************************************************/
/* Filename						: TC74.c                            */
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
#include "../../include/TC74/TC74_private.h"

#include "../../include/TC74/TC74_config.h"
#include "../../include/TC74/TC74.h"


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/
Tc74_StatusErrorType Tc74_ReadByte(u8 Copy_u8SlaveAddress,u8* Address_Result){
	Tc74_StatusErrorType Loc_enuTc74Status = TC74_STATUS_OK;
	u8 Loc_u8Temp;
	if(NULL == Address_Result){
		Loc_enuTc74Status = TC74_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressWritingBlocking(Copy_u8SlaveAddress, &Loc_u8Temp);
		I2c_enuMasterTransmitDataWritingBlocking(TC74_REG_READ_ADDRESS, &Loc_u8Temp);
		I2c_enuMasterTransmitStartConditionBlocking();
		I2c_enuMasterTransmitAddressReadingBlocking(Copy_u8SlaveAddress, &Loc_u8Temp);
		I2c_enuMasterReceiveDataBlocking(Address_Result,I2c_NACK_VALUE);
		I2c_enuMasterTransmitStopConditionBlocking();
		_delay_ms(1);
	}

	return Loc_enuTc74Status;
}


