/**************************************************************************/
/* Filename						: I2C.c                            */
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
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"

#include "../../DIO/include/DIO.h"
#include "../include/I2C_config.h"
#include "../include/I2C_private.h"
#include "../include/I2C.h"


/********************************** Static / Private Part ****************************/

static void (*I2c_InterruptHandler)( u8 Copy_u8Result);


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/

I2c_StatusErrorType I2c_enuInit(const I2c_ConfigType* Address_I2c){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_I2c){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		/* I2c Disable during Config */
		I2c_Disable();

		/* I2c Set Prescaler */
		I2c_SelectPrescaler(Address_I2c->select_prescale_value_twps);

		/* I2c Set Clock COnfig */
		I2c_ConfigClock(Address_I2c->clock_freq,Address_I2c->select_prescale_value_twps);

		if(Address_I2c->slave_address_or_minus_one_for_master_mode != I2C_MASTER_INDEX){
			I2c_SetAddress7Bit((Address_I2c->slave_address_or_minus_one_for_master_mode));
		}
		else { /* Do nothing */}

		/* I2c Enable */
		I2c_Enable();

		I2c_ClearFlag();
	}

	return Loc_enuI2cStatus;
}

I2c_StatusErrorType I2c_DeInit(const I2c_ConfigType* Address_I2c){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_I2c){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		I2c_Disable();
	}

	return Loc_enuI2cStatus;
}


I2c_StatusErrorType I2c_enuEnableInterrupt(void){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;

	I2c_EnableInterrupt();

	return Loc_enuI2cStatus;
}

I2c_StatusErrorType I2c_enuDisableInterrupt(void){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;

	I2c_DisableInterrupt();

	return Loc_enuI2cStatus;
}

I2c_StatusErrorType I2c_enuSetCallbackFunction(void (*callback)(u8 Copy_u8Status)){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == callback){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		I2c_InterruptHandler = callback;
	}

	return Loc_enuI2cStatus;
}


I2c_StatusErrorType I2c_enuIsWriteCollisionHappened(I2c_IsWriteCollisionHappenedType* Address_Result){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = I2c_isWirteCollisionHappened();
	}

	return Loc_enuI2cStatus;
}



I2c_StatusErrorType I2c_enuMasterTransmitStartConditionBlocking(void){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;

	I2c_StartCondition();
	while(I2c_IsTheJobDone() == ZERO_VALUE);


	return Loc_enuI2cStatus;
}


I2c_StatusErrorType I2c_enuMasterTransmitStopConditionBlocking(void){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;

	I2c_DoJob();
	I2c_StopCondition();


	return Loc_enuI2cStatus;
}
I2c_StatusErrorType I2c_enuMasterTransmitRepeatedStartConditionBlocking(void){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;

	I2c_StartCondition();
	while(I2c_IsTheJobDone() == ZERO_VALUE);


	return Loc_enuI2cStatus;
}

/* send data */
I2c_StatusErrorType I2c_enuMasterTransmitDataWritingBlocking(u8 Copy_u8Data, u8* Address_ReceivedAck){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_ReceivedAck){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		I2c_SetDataRegister(Copy_u8Data);
		I2c_DoJob();
		while(I2c_IsTheJobDone() == ZERO_VALUE);
	}

	return Loc_enuI2cStatus;
}


/* send data/address */
I2c_StatusErrorType I2c_enuMasterTransmitAddressReadingBlocking(u8 Copy_u8SlaveAddress, u8* Address_ReceivedAck){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_ReceivedAck){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		I2c_SetDataRegister(((Copy_u8SlaveAddress<<ONE_VALUE)| ONE_VALUE));
		I2c_DoJob();
		while(I2c_IsTheJobDone() == ZERO_VALUE);
	}

	return Loc_enuI2cStatus;
}

I2c_StatusErrorType I2c_enuMasterTransmitAddressWritingBlocking(u8 Copy_u8SlaveAddress, u8* Address_ReceivedAck){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_ReceivedAck){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		I2c_SetDataRegister(Copy_u8SlaveAddress<<1);
		I2c_DoJob();
		while(I2c_IsTheJobDone() == ZERO_VALUE);
	}
	return Loc_enuI2cStatus;
}


/* receive data from buffer
 you've send sla +R before
 */
I2c_StatusErrorType I2c_enuMasterReceiveDataBlocking(u8* Address_ResultData, u8 Copy_u8SendAck){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_ResultData){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{


		I2c_DoJob();

		while(I2c_IsTheJobDone() == ZERO_VALUE);

		*Address_ResultData = I2c_GetDataRegister();
		I2c_SetAck(Copy_u8SendAck);



	}

	return Loc_enuI2cStatus;
}



I2c_StatusErrorType I2c_enuSlaveTransmitDataBlocking(u8 Copy_u8Data, u8* Address_ReceivedAck){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_ReceivedAck){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		I2c_SetDataRegister(Copy_u8Data);
		I2c_DoJob();
		while(I2c_IsTheJobDone() == ZERO_VALUE);
	}

	return Loc_enuI2cStatus;
}

I2c_StatusErrorType I2c_enuSlaveReceiveDataBlocking(u8* Address_ResultData, u8 Copy_u8SendAck){
	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
	if(NULL == Address_ResultData){
		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		I2c_DoJob();
		while(I2c_IsTheJobDone() == ZERO_VALUE);
		*Address_ResultData = I2c_GetDataRegister();

	}

	return Loc_enuI2cStatus;
}



///* S + SLA + W + Data + Stop*/
//I2c_StatusErrorType I2c_enuMasterTransmitFrame_WriteBlocking(u8 _slave_address_7bit, u8 Copy_u8Data, u8* Address_ReceivedAck){
//	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
//	if(NULL == Address_ReceivedAck){
//		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
//	}
//	else{
//
//	}
//
//	return Loc_enuI2cStatus;
//}
//
//
///* S + SLA + R + ReceiveData + Stop*/
//I2c_StatusErrorType I2c_enuMasterTransmitFrame_Receivelocking(u8 _slave_address_7bit, u8* Address_ResultData,u8* Address_AckReceivedForSlaveAddress,u8 Copy_u8SendAck ){
//	// s + SLA + w + data + stop
//
//	I2c_StatusErrorType Loc_enuI2cStatus = I2C_STATUS_OK;
//	if(NULL == Address_ResultData || NULL == Address_AckReceivedForSlaveAddress){
//		Loc_enuI2cStatus = I2C_STATUS_NULL_POINTER_ADDRESS;
//	}
//	else{
//
//	}
//
//	return Loc_enuI2cStatus;
//}
