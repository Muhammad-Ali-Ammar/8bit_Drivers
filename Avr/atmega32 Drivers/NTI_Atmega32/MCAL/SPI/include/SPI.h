/**************************************************************************/
/* Filename						: SPI.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 28 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_SPI_INCLUDE_SPI_H_
#define MCAL_SPI_INCLUDE_SPI_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
typedef enum{
	SPI_SELECT_DATA_MSB_FIRST,
	SPI_SELECT_DATA_LSB_FIRST
}Spi_SelectDataOrdingType;

typedef enum{
	SPI_SELECT_POLARITY_IDLE_LOW_LEADING_EDGE_RISING,
	SPI_SELECT_POLARITY_IDLE_HIGH_LEADING_EDGE_FAILING
}Spi_SelectPolarityType;


typedef enum{
	SPI_SELECT_SLAVE_MODE,
	SPI_SELECT_MASTER_MODE
}Spi_SelectMasterSlaveType;



typedef enum{
	SPI_SELECT_PHASE_SAMPLE_READ_FIRST_AT_LEADING_EDGE,
	SPI_SELECT_PHASE_SETUP_WRITE_FIRST_AT_LEADING_EDGE
}Spi_SelectPhaseType;

typedef enum{
	SPI_SELECT_CLK_FREQ_DIV_4,
	SPI_SELECT_CLK_FREQ_DIV_16,
	SPI_SELECT_CLK_FREQ_DIV_64,
	SPI_SELECT_CLK_FREQ_DIV_128,
	SPI_SELECT_CLK_FREQ_DIV_2,
	SPI_SELECT_CLK_FREQ_DIV_8,
	SPI_SELECT_CLK_FREQ_DIV_32
}Spi_SelectClkSpeedType;

typedef enum{
	SPI_STATUS_FAIL,
	SPI_STATUS_OK,
	SPI_STATUS_NULL_POINTER_ADDRESS
}Spi_StatusErrorType;


typedef struct{
	Spi_SelectMasterSlaveType select_master_or_slave;
	Spi_SelectDataOrdingType select_data_ording;
	Spi_SelectPolarityType select_polarity;
	Spi_SelectPhaseType select_phase;
	Spi_SelectClkSpeedType select_clk_speed;
}Spi_ConfigType;


typedef enum{
	SPI_IS_WRITE_COLLISION_HAPPENED_FALSE,
	SPI_IS_WRITE_COLLISION_HAPPENED_TRUE
}Spi_IsWriteCollisionHappenedType;


/********************************** Software Interfaces Declarations *******************/
Spi_StatusErrorType Spi_enuInit(const Spi_ConfigType* Address_Spi);
Spi_StatusErrorType Spi_enuDeInit(void);

Spi_StatusErrorType Spi_enuEnableInterrupt(void);
Spi_StatusErrorType Spi_enuDisableInterrupt(void);
Spi_StatusErrorType Spi_enuSetCallbackFunction(void (*callback)(u8 Copy_u8Result));



Spi_StatusErrorType Spi_enuChangeClk(Spi_SelectClkSpeedType Copy_enuClkSpeed);
Spi_StatusErrorType Spi_enuIsWriteCollisionHappened(Spi_IsWriteCollisionHappenedType* Address_Result);

Spi_StatusErrorType Spi_enuReceiveBlocking(pu8 Address_ReceiveDataFromMaster, u8 Copy_u8SendDataToMaster);
Spi_StatusErrorType Spi_enuTransmitBlocking(u8 Copy_u8SlaveSelectPin, u8 Copy_u8SendData, pu8 Address_ReceiveDataFromSlave);



Spi_StatusErrorType Spi_enuTransmitNonBlockingMasterMode(u8 Copy_u8SlaveSelectPin, u8 Copy_u8SendDataToSlave);// interrupt happens when transmiting is done, so read in ISR
Spi_StatusErrorType Spi_enuRecevingNonBlockingSlaveModeForever( u8 Copy_u8SendDataToMaster); // interrupt happens when transmiting is done, so read in ISR





#endif /* MCAL_SPI_INCLUDE_SPI_H_ */
