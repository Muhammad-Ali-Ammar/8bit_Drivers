/* 
 * File:   mcal_i2c.h
 * Author: Muhammad Ammar
 *
 * Created on 13 ????, 2023, 12:24 ?
 */

#ifndef MCAL_I2C_H
#define	MCAL_I2C_H

/********************************** Includes *****************************************/
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/********************************** Macros Declarations *******************************/

#define I2C_TRUE                     (1)
#define I2C_FALSE                    (0)

/********************************** Macros Function Declarations *******************************/

#define I2c_Enable()                                                   (SSPCON1bits.SSPEN = 1)
#define I2c_Disable()                                                  (SSPCON1bits.SSPEN = 0)
													                  
#define I2c_SelectMasterSlave(_X_)                                     (SSPCON1bits.SSPM = (_X_))
													                  
/* config  SMBus  bit */                                              
#define I2c_EnableSMBus()             				                   (SSPSTATbits.CKE = 1)
#define I2c_DisableSMBus()            				                   (SSPSTATbits.CKE = 0)
#define I2c_SelectSMBus(_X_)          				                   (SSPSTATbits.CKE = (_X_))
													                  
													                  
#define I2c_IsStopBitDetected()      				                   (SSPSTATbits.P == 1)
#define I2c_IsStartBitDetected()     				                   (SSPSTATbits.S == 1)
													                  
													                  
#define I2c_SelectSlewRate(_X_)      				                   (SSPSTATbits.SMP = (_X_))
													                  
#define I2c_ClearFlagBit()           				                   (PIR1bits.SSPIF = 0)
#define I2c_ClearReceieveOverflow()  				                   (SSPCON1bits.SSPOV = 0)
#define I2c_IsReceiveOverflowDetected()                                (SSPCON1bits.SSPOV == 1)
// for master receive mode					                          
													                  
#define I2c_EnableReceiveMasterMode()                                  (SSPCON2bits.RCEN = 1)
#define I2c_DisableReceiveMasterMode()                                 (SSPCON2bits.RCEN = 0)
#define I2c_IsReceiveDataCompleted_MasterMode()                        (SSPSTATbits.BF == 1)
#define I2c_TransmitAckMasterReceiveMode(_X_)   	                   do{ \
													                   SSPCON2bits.ACKDT = (_X_); \
													                   SSPCON2bits.ACKEN = 1; \
													                   }while(0)


// for master transmit
#define I2c_TransmitStartMasterMode()                   			  (SSPCON2bits.SEN = 1)
#define I2c_IsTransmitStartCompletedMasterMode()        			  (SSPCON2bits.SEN == 0)
																	  
#define I2c_TransmitStopMasterMode()                    			  (SSPCON2bits.PEN = 1)
#define I2c_IsTransmitStopCompletedMasterMode()         			  (SSPCON2bits.PEN == 0)


#define I2c_TransmitRepeatedStartMasterMode()                         (SSPCON2bits.RSEN = 1)
#define I2c_IsTransmitRepeatedStartCompletedMasterMode()              (SSPCON2bits.RSEN == 0)
															          
//#define I2c_IsTransmitDataCompletedMasterMode()                       (PIR1bits.SSPIF == 1)
#define I2c_IsTransmitDataCompletedMasterMode()                       (SSPSTATbits.R_NOT_W == 0)
													          
															          
#define I2c_IsAckReceivedFromSlave_MasterTransmitMode()               (SSPCON2bits.ACKSTAT == 0)


// for slave  

#define I2c_DoesMasterWantToReadFromMe_SalveMode()                  (SSPSTATbits.R_NOT_W == 1)

/* config  general call bit */
#define I2c_EnableGeneralCallWithInterruptSlaveMode()                (SSPCON2bits.GCEN = 1)
#define I2c_DisableGeneralCallSlaveMode()                            (SSPCON2bits.GCEN = 0)
#define I2c_SelectGeneralCallWithInterruptSlaveMode(_X_)             (SSPCON2bits.GCEN= (_X_))

/* config  clock stretch */
#define I2c_EnableClockStretchSlaveMode()                            (SSPCON2bits.SEN = 1)
#define I2c_DisableClockStretchSlaveMode()                           (SSPCON2bits.SEN = 0)
#define I2c_SelectClockStretchSlaveMode(_X_)                         (SSPCON2bits.SEN= (_X_))

// slave transmit mode 
#define I2c_ClearWriteCollisionSlaveMode()                           (SSPCON1bits.WCOL = 0)

#define I2c_IsLastByteReceivedOrTransmitedWasDataSlaveMode()         (SSPSTATbits.D_NOT_A == 1)

#define I2c_RelaseClockSlaveMode()                                   (SSPCON1bits.CKP = 1)
#define I2c_HoldClockLowSlaveMode()                                  (SSPCON1bits.CKP = 0)


/********************************** Data Type Declarations *******************************/

typedef enum{
    I2C_SMBUS_DISABLE,
    I2C_SMBUS_ENABLE
}I2c_SMBusType;


typedef enum{
    I2C_SLEW_RATE_DISABLE_CLK_100KHz,
    I2C_SLEW_RATE_ENABLE_CLK_400KHz
}I2c_SlewRateType;


typedef enum{
    I2C_SLAVE_MODE_CLOCK_STRETCH_DISABLE,
    I2C_SLAVE_MODE_CLOCK_STRETCH_ENABLE
}I2c_SlaveMode_ClockStretchingType;

typedef enum{
    I2C_SLAVE_MODE_GENERAL_CALL_DISABLE,
    I2C_SLAVE_MODE_GENERAL_CALL_ENABLE_WITH_INTERRUPT
}I2c_SlaveMode_GeneralCallType;


typedef enum{
    I2C_SLAVE_MODE_7BIT_ADDRESS = 0b0110,
    I2C_SLAVE_MODE_10BIT_ADDRESS,
    I2C_MASTER_MODE,
    I2C_MASTER_MODE_MANUAL_SW_CONTROLLED = 0b1011,
    I2C_SLAVE_MODE_7BIT_ADDRESS_START_STOP_ENABLE=1110 ,
    I2C_SLAVE_MODE_10BIT_ADDRESS_START_STOP_ENABLE=1111
    
}I2c_MasterSlaveType;





typedef struct{
    
    I2c_SMBusType        SMBus_config;
    I2c_MasterSlaveType  master_slave_config;
    I2c_SlewRateType     slew_rate;
    void (*I2c_InterruptHandler)(void);
    void (*I2cWriteCollision_InterruptHandler)(void);
    void (*I2cReceiveOverflow_InterruptHandler)(void);
    Interrupt_PrioityType I2c_interrupt_priority;
    Interrupt_PrioityType I2cWriteCollision_interrupt_priority;
    
    
    I2c_SlaveMode_ClockStretchingType slave_mode_clock_stretch_config;
    I2c_SlaveMode_GeneralCallType slave_mode_general_call_config;
    uint16                slave_address_7bit;
    
    uint32                master_mode_clock;


}I2c_ConfigType;



/********************************** Software Interfaces Declarations *******************************/
Std_ReturnType I2c_Init(const I2c_ConfigType* _i2c);
Std_ReturnType I2c_DeInit(const I2c_ConfigType* _i2c);

Std_ReturnType I2c_MasterTransmitStartConditionBlocking(const I2c_ConfigType* _i2c);
Std_ReturnType I2c_MasterTransmitStopConditionBlocking(const I2c_ConfigType* _i2c);
Std_ReturnType I2c_MasterTransmitRepeatedStartConditionBlocking(const I2c_ConfigType* _i2c);

/* send data/address */
Std_ReturnType I2c_MasterTransmitDataBlocking(const I2c_ConfigType* _i2c, uint8 _data, uint8* _ack_received);


/* receive data from buffer 
 you've send sla +R before 
 */
Std_ReturnType I2c_MasterReceiveDataBlocking(const I2c_ConfigType* _i2c, uint8* _data, uint8 _send_ack);


/* S + SLA + W + Data + Stop*/
Std_ReturnType I2c_MasterTransmitFrame_WriteBlocking(const I2c_ConfigType* _i2c,uint8 _slave_address_7bit, uint8 _data, uint8* _ack_received); 


/* S + SLA + R + ReceiveData + Stop*/
Std_ReturnType I2c_MasterTransmitFrame_Receivelocking(const I2c_ConfigType* _i2c,uint8 _slave_address_7bit, uint8* _data, uint8* _ack_received_for_slave_address,uint8 _ack_send ); // s + SLA + w + data + stop


//Std_ReturnType I2c_SlaveReceiveDataNonBlocking(const I2c_ConfigType* _i2c);


#endif	/* MCAL_I2C_H */

