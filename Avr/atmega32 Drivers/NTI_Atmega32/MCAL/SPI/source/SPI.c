/**************************************************************************/
/* Filename						: SPI.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 28 Oct 2023  	           	 	      	 */
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
#include "../include/SPI_config.h"
#include "../include/SPI_private.h"
#include "../include/SPI.h"

/*********************************** Static/ private part ****************************/
static void (*Spi_InterruptHandler)( u8 Copy_u8Result);

static u8 Global_StaticU8SlavePin;
static Spi_SelectMasterSlaveType Global_StaticEnuMode;


/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


/********************************** Software Interfaces Declarations *******************/

Spi_StatusErrorType Spi_enuInit(const Spi_ConfigType* Address_Spi){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;
	if(NULL == Address_Spi){
		Loc_enuSpiStatus = SPI_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		/* Disable During Configuration */
		Spi_Disable();

		/* Select MasterSlaveType */
		Spi_SelectMasterSlave(Address_Spi->select_master_or_slave);

		/* Select data ording */
		Spi_SelectDataOrding(Address_Spi->select_data_ording);

		/* Select Polarity */
		Spi_SelectPolarity(Address_Spi->select_polarity);

		/* Select Phase */
		Spi_SelectPhase(Address_Spi->select_phase);

		/* Select Clock Speed */
		Spi_SelectClkSpeed(Address_Spi->select_clk_speed);

		/* Enable During Configuration */
		Spi_Enable();

	}

	return Loc_enuSpiStatus;
}

Spi_StatusErrorType Spi_enuDeInit(void){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;

	/* Disable  */
	Spi_Disable();

	return Loc_enuSpiStatus;
}

Spi_StatusErrorType Spi_enuEnableInterrupt(void){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;

	Spi_EnableInterrupt();

	return Loc_enuSpiStatus;
}

Spi_StatusErrorType Spi_enuDisableInterrupt(void){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;

	Spi_DisableInterrupt();

	return Loc_enuSpiStatus;
}

Spi_StatusErrorType Spi_enuSetCallbackFunction(void (*callback)(u8 Copy_u8Result)){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;
	if(NULL == callback){
		Loc_enuSpiStatus = SPI_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		Spi_InterruptHandler = callback;
	}

	return Loc_enuSpiStatus;
}



Spi_StatusErrorType Spi_enuChangeClk(Spi_SelectClkSpeedType Copy_enuClkSpeed){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;

	/* Disable During Configuration */
		Spi_Disable();

		/* Select Clock Speed */
		Spi_SelectClkSpeed(Copy_enuClkSpeed);

		/* Enable During Configuration */
		Spi_Enable();


	return Loc_enuSpiStatus;
}

Spi_StatusErrorType Spi_enuIsWriteCollisionHappened(Spi_IsWriteCollisionHappenedType* Address_Result){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuSpiStatus = SPI_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = Spi_isWirteCollisionHappened();
	}

	return Loc_enuSpiStatus;
}


Spi_StatusErrorType Spi_enuReceiveBlocking(pu8 Address_ReceiveDataFromMaster, u8 Copy_u8SendDataToMaster){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;
	if(NULL == Address_ReceiveDataFromMaster){
		Loc_enuSpiStatus = SPI_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		// data that will send to master
		Spi_SetDataRegister(Copy_u8SendDataToMaster); // might cause logical error here
		while(Spi_IsRecevingDone() == ZERO_VALUE);
		*Address_ReceiveDataFromMaster = Spi_GetDataRegister();

	}

	return Loc_enuSpiStatus;
}


Spi_StatusErrorType Spi_enuTransmitBlocking(u8 Copy_u8SlaveSelectPin, u8 Copy_u8SendData, pu8 Address_ReceiveDataFromSlave){
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;
	if(NULL == Address_ReceiveDataFromSlave){
		Loc_enuSpiStatus = SPI_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		Dio_enuWriteChannel(Copy_u8SlaveSelectPin, DIO_LOW);
		Spi_SetDataRegister(Copy_u8SendData);
		while(Spi_IsTransmittingDone() == ZERO_VALUE);
		*Address_ReceiveDataFromSlave = Spi_GetDataRegister();
		Dio_enuWriteChannel(Copy_u8SlaveSelectPin, DIO_HIGH);

	}

	return Loc_enuSpiStatus;
}



Spi_StatusErrorType Spi_enuTransmitNonBlockingMasterMode(u8 Copy_u8SlaveSelectPin, u8 Copy_u8SendDataToSlave){

	// interrupt happens when transmiting is done, so read in ISR
	Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;

	Dio_enuWriteChannel(Copy_u8SlaveSelectPin, DIO_LOW);
	Global_StaticU8SlavePin = Copy_u8SlaveSelectPin;
	Spi_SetDataRegister(Copy_u8SendDataToSlave);


		return Loc_enuSpiStatus;
}

Spi_StatusErrorType Spi_enuRecevingNonBlockingSlaveModeForever( u8 Copy_u8SendDataToMaster){
	// interrupt happens when transmiting is done, so read in ISR


		Spi_StatusErrorType Loc_enuSpiStatus = SPI_STATUS_OK;
		Spi_SetDataRegister(Copy_u8SendDataToMaster);

		return Loc_enuSpiStatus;

}








// ISR function For SPI
void __vector_12(void) __attribute__((signal));

void __vector_12(void){

u8 Loc_u8Result ;
/* don't forget in master mode, to make ss high after reading from slave */

    if(NULL !=Spi_InterruptHandler ){

    	Loc_u8Result = Spi_GetDataRegister();
    	Spi_InterruptHandler(Loc_u8Result);

    	switch (Global_StaticEnuMode){

    	case SPI_SELECT_MASTER_MODE:
    		Dio_enuWriteChannel(Global_StaticU8SlavePin, DIO_HIGH);
    		break;

    	default:
    		break;
    	}

    }
    else {/*  error in declaration */   }

}
