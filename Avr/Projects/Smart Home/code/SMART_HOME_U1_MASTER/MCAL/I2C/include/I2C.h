/**************************************************************************/
/* Filename						: I2C.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_I2C_INCLUDE_I2C_H_
#define MCAL_I2C_INCLUDE_I2C_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

/*
 *	(F_CPU - 16 *Clock ) / (2*Clock *4 ^TWPS)
 *	where that TWPS = 0,1,2,3
 *
 */
typedef enum{
	I2C_SELECT_PRESCALER_VALUE_1 = 0,
	I2C_SELECT_PRESCALER_VALUE_4,
	I2C_SELECT_PRESCALER_VALUE_16,
	I2C_SELECT_PRESCALER_VALUE_64
}I2c_SelectPrescalerValueTWPSType;

typedef struct{
	u32 clock_freq;
	I2c_SelectPrescalerValueTWPSType select_prescale_value_twps;
	s16 slave_address_or_minus_one_for_master_mode;

}I2c_ConfigType;

typedef enum{
	I2C_STATUS_FAIL,
	I2C_STATUS_OK,

	I2C_STATUS_ACK,
	I2C_STATUS_NACK,
	I2C_STATUS_NULL_POINTER_ADDRESS
}I2c_StatusErrorType;

typedef enum{
	I2c_IS_WRITE_COLLISION_HAPPENED_FALSE,
	I2c_IS_WRITE_COLLISION_HAPPENED_TRUE
}I2c_IsWriteCollisionHappenedType;


typedef enum{
	I2c_NACK_VALUE,
	I2c_ACK_VALUE
}I2c_AckNackValueType;



/********************************** Software Interfaces Declarations *******************/

I2c_StatusErrorType I2c_enuInit(const I2c_ConfigType* I2c_StatusErrorType);
I2c_StatusErrorType I2c_DeInit(const I2c_ConfigType* I2c_StatusErrorType);


I2c_StatusErrorType I2c_enuEnableInterrupt(void);
I2c_StatusErrorType I2c_enuDisableInterrupt(void);
I2c_StatusErrorType I2c_enuSetCallbackFunction(void (*callback)(u8 Copy_u8Status));

I2c_StatusErrorType I2c_enuIsWriteCollisionHappened(I2c_IsWriteCollisionHappenedType* Address_Result);



I2c_StatusErrorType I2c_enuMasterTransmitStartConditionBlocking(void);
I2c_StatusErrorType I2c_enuMasterTransmitStopConditionBlocking(void);
I2c_StatusErrorType I2c_enuMasterTransmitRepeatedStartConditionBlocking(void);

/* send data/address */
I2c_StatusErrorType I2c_enuMasterTransmitAddressReadingBlocking(u8 Copy_u8SlaveAddress, u8* Address_ReceivedAck);
I2c_StatusErrorType I2c_enuMasterTransmitAddressWritingBlocking(u8 Copy_u8SlaveAddress, u8* Address_ReceivedAck);

I2c_StatusErrorType I2c_enuMasterTransmitDataWritingBlocking(u8 Copy_u8Data, u8* Address_ReceivedAck);
I2c_StatusErrorType I2c_enuMasterReceiveDataBlocking(u8* Address_ResultData, u8 Copy_u8SendAck);


I2c_StatusErrorType I2c_enuSlaveTransmitDataBlocking(u8 Copy_u8Data, u8* Address_ReceivedAck);
I2c_StatusErrorType I2c_enuSlaveReceiveDataBlocking(u8* Address_ResultData, u8 Copy_u8SendAck);


/* receive data from buffer
 you've send sla +R before
 */


///* S + SLA + W + Data + Stop*/
//I2c_StatusErrorType I2c_enuMasterTransmitFrame_WriteBlocking(u8 _slave_address_7bit, u8 Copy_u8Data, u8* Address_ReceivedAck);
//
//
///* S + SLA + R + ReceiveData + Stop*/
//I2c_StatusErrorType I2c_enuMasterTransmitFrame_Receivelocking(u8 _slave_address_7bit, u8* Address_ResultData,
//							u8* Address_AckReceivedForSlaveAddress,u8 Copy_u8SendAck ); // s + SLA + w + data + stop





#endif /* MCAL_I2C_INCLUDE_I2C_H_ */


/*
 *
 * To configure AVR ATmega32 as a master or a slave in I2C, you need to follow these steps:

Initialize the TWI (Two-Wire Interface) module by setting the bit rate and the prescaler values in the TWBR (Two-Wire Bit Rate Register) and TWSR (Two-Wire Status Register) respectively. The formula for calculating the SCL (Serial Clock Line) frequency is:
[ SCL = \frac{{F_{\text{CPU}}}}{{16 + 2 \cdot \text{{TWBR}} \cdot 4^{\text{{TWPS}}}}} ]

Where (F_{\text{CPU}}) is the CPU clock frequency, (TWBR) is the bit rate value, and (TWPS) is the prescaler value.

Set the TWAR (Two-Wire Address Register) with the slave address and the general call recognition enable bit (TWGCE). This is only required for the slave mode, as the master does not need an address.

Enable the TWI by setting the TWEN bit in the TWCR (Two-Wire Control Register). This will activate the SDA (Serial Data Line) and SCL pins as I/O ports.

To start a communication, the master needs to send a START condition by setting the TWSTA bit in the TWCR. This will generate a high-to-low transition on the SDA line while the SCL line is high.

After sending the START condition, the master needs to load the TWDR (Two-Wire Data Register) with the slave address and the read/write bit. Then, it needs to clear the TWINT (Two-Wire Interrupt Flag) bit in the TWCR to start transmission.

The slave will receive the address and compare it with its own address in the TWAR. If they match, or if a general call is received, the slave will return an ACK (acknowledge) bit by pulling the SDA line low.

The master will check the TWSR for the ACK status. If an ACK is received, it means that a valid slave has been addressed and communication can proceed. If a NACK (not acknowledge) is received, it means that no slave has responded and communication should be terminated.

Depending on the read/write bit, the master or the slave will become a transmitter or a receiver. The transmitter will load data into the TWDR and clear the TWINT bit to start transmission. The receiver will wait for data to arrive in the TWDR and then send an ACK or NACK bit depending on whether more data is expected or not.

To end a communication, the master needs to send a STOP condition by setting the TWSTO bit in the TWCR. This will generate a low-to-high transition on the SDA line while the SCL line is high.
 */
