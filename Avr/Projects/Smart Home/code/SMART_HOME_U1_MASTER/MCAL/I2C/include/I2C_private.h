/**************************************************************************/
/* Filename						: I2C_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 30 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_I2C_INCLUDE_I2C_PRIVATE_H_
#define MCAL_I2C_INCLUDE_I2C_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define TWDR			(*(volatile u8*)(0x23))
#define TWAR			(*(volatile u8*)(0x22))
#define TWSR			(*(volatile u8*)(0x21))
#define TWBR			(*(volatile u8*)(0x20))
#define TWCR			(*(volatile u8*)(0x56))


#define TWCR_TWINT_BIT			(SEVEN_VALUE)
#define TWCR_TWEA_BIT			(SIX_VALUE)

#define TWINT 					(SEVEN_VALUE)
#define TWSTA 					(FIVE_VALUE)
#define TWEN 					(TWO_VALUE)
#define TWSTO					(FOUR_VALUE)

#define I2C_MASTER_INDEX			(-1)

/********************************** Macros Function Declarations *********************/


#define I2c_IsTheJobDone()						    (READ_BIT(TWCR,TWCR_TWINT_BIT) == ONE_VALUE)
#define I2c_ClearFlag()							    (SET_BIT(TWCR,TWCR_TWINT_BIT))



#define I2c_EnableInterrupt()				    (SET_BIT(TWCR,ZERO_VALUE))
#define I2c_DisableInterrupt()				    (CLEAR_BIT(TWCR,ZERO_VALUE))


#define I2c_SendAck()							 (SET_BIT(TWCR,TWCR_TWEA_BIT))
#define I2c_SendNack()							 (CLEAR_BIT(TWCR,TWCR_TWEA_BIT))
#define I2c_SetAck(_ARGU_)						 (WRITE_BIT(TWCR,TWCR_TWEA_BIT,_ARGU_))

#define I2c_StartCondition()					(TWCR = (ONE_VALUE<<TWINT) | (ONE_VALUE<<TWSTA) |(ONE_VALUE<<TWEN))


#define I2c_StopCondition()				  	    (TWCR = (ONE_VALUE<<TWSTO) | ((ONE_VALUE<<TWEN)) | ((ONE_VALUE<<TWINT)))

#define I2c_DoJob()								(TWCR = (ONE_VALUE<<TWINT) | (ONE_VALUE<<TWEN))

#define I2c_isWirteCollisionHappened()		(READ_BIT(TWCR,THREE_VALUE) == ONE_VALUE)


#define I2c_Enable()			(SET_BIT(TWCR,TWO_VALUE))
#define I2c_Disable()			(CLEAR_BIT(TWCR,TWO_VALUE))

////////////////////////////////////////////////////////////////////////////////////////

#define I2c_SelectPrescaler(_ARGU_)					ASSIGN_REG(TWSR,_ARGU_)
#define I2c_ConfigClock(_SCL_,_PRESCALER_)	       (TWBR) =(F_CPU-16*_SCL_)/(_SCL_*(1<<(2*_PRESCALER_+1)))


///////////////////////////////////////////////////////////////////////////////////
#define I2c_SetDataRegister(_ARGU_)				   ASSIGN_REG(TWDR,_ARGU_)
#define I2c_GetDataRegister()				   	   (TWDR)
////////////////////////////////////////////////////////////////////////////////////

#define I2c_SetAddress7Bit(_ARGU_)					((TWAR)= ((TWAR) &0x01) | ((_ARGU_)<<1))

#define I2c_EnableGeneralCallRecognition()			(SET_BIT(TWAR,ZERO_VALUE))
#define I2c_DisableGeneralCallRecognition()			(Clear_BIT(TWAR,ZERO_VALUE))

////////////////////////////////////////////////////////////////////////////////////

#define I2c_IsStartConditionHasBeenTransmitted()					((TWSR>>3) == 0x08)
#define I2c_IsRepatedStartConditionHasBeenTransmitted()				((TWSR>>3) == 0x10)
#define I2c_IsAckReceivedAfterSLAandWriteHasBeenTransmitted()		((TWSR>>3) == 0x18)
#define I2c_IsNackReceivedAfterSLAandWriteHasBeenTransmitted()		((TWSR>>3) == 0x20)
#define I2c_IsAckReceivedAfterDataHasBeenTransmitted()				((TWSR>>3) == 0x28)
#define I2c_IsNackReceivedAfterDataHasBeenTransmitted()				((TWSR>>3) == 0x30)
#define I2c_IsArbitrationLostInSLAandWorInData()					((TWSR>>3) == 0x38)
#define I2c_IsAckReceivedAfterSLAandReadHasBeenTransmitted()		((TWSR>>3) == 0x40)
#define I2c_IsNackReceivedAfterSLAandReadHasBeenTransmitted()		((TWSR>>3) == 0x48)

/*0x50	MR_DATA_ACK				Data byte has been received; ACK has been returned
0x58	MR_DATA_NACK			Data byte has been received; NACK has been returned
0xA8	ST_SLA_ACK						Own SLA+R has been received; ACK has been returned
0xB0	ST_ARB_LOST_SLA_ACK					Arbitration lost in SLA+R/W as master; own SLA+R has been received; ACK has been returned
0xB8	ST_DATA_ACK					Data byte in TWDR has been transmitted; ACK has been received
0xC0	ST_DATA_NACK				Data byte in TWDR has been transmitted; NACK has been received
0xC8	ST_LAST_DATA				Last data byte in TWDR has been transmitted (TWEA = 0); ACK has been received
0x60	SR_SLA_ACK						Own SLA+W has been received; ACK has been returned
0x68	SR_ARB_LOST_SLA_ACK				Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned
0x70	SR_GCALL_ACK					General call address has been received; ACK has been returned
0x78	SR_ARB_LOST_GCALL_ACK			Arbitration lost in SLA+R/W as master; general call address has been received; ACK has been returned
0x80	SR_DATA_ACK						Data byte has been received; ACK has been returned
0x88	SR_DATA_NACK					Data byte has been received; NACK has been returned
0x90	SR_GCALL_DATA_ACK					Data byte for general call address has been received; ACK has been returned
0x98	SR_GCALL_DATA_NACK				Data byte for general call address has been received; NACK has been returned
0xA0	SR_STOP_RESTART						A STOP condition or repeated START condition has been received while still addressed as slave

*/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_I2C_INCLUDE_I2C_PRIVATE_H_ */
