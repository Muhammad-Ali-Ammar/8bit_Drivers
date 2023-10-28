/* 
 * File:   mcal_eusart.h
 * Author: 
 *
 * Created on 24 ?????, 2023, 11:14 ?
 */

#ifndef MCAL_EUSART_H
#define	MCAL_EUSART_H

/********************************** Includes *****************************************/
#include "../mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"


/********************************** Macros Declarations *******************************/
#define EUSART_FALSE                     ((uint8)0)


/********************************** Macros Function Declarations *******************************/

/* Enable/disable Eusart Trnsmiter*/
#define Eusart_EnableTx()                             (TXSTAbits.TXEN = 1)
#define Eusart_DisableTx()                            (TXSTAbits.TXEN = 0)


/* Enable 9bit Transmit bit */
#define Eusart_Enable9bitTransmission()              (TXSTAbits.TX9 = 1)
#define Eusart_Disable9bitTransmission()             (TXSTAbits.TX9 = 0)
#define Eusart_Select9bitTransmission(_X_)           (TXSTAbits.TX9 = (_X_))


/* Enable Async or Sync mode */
#define Eusart_EnableAsyncMode()                     (TXSTAbits.SYNC = 0)
#define Eusart_EnableSyncMode()                      (TXSTAbits.SYNC = 1)
#define Eusart_SelectSynchronizationMode(_X_)        (TXSTAbits.SYNC = (_X_))

/* Select High or Low Async Speed  */
#define Eusart_SelectAsyncSpeed(_X_)                 (TXSTAbits.BRGH = (_X_))  

/* check if shift register is empty to put another data to send */
#define Eusart_IsShiftRegEmpty()                     (TXSTAbits.TRMT ==1 )


/* Write 9bit data of transmission  */
#define Eusart_Write9bitDataValueTx(_X_)            (TXSTAbits.TX9D = (_X_) )


/* Enable/disable serial pin Tx and Rx*/
#define Eusart_EnableSerialPin()                    (RCSTAbits.SPEN = 1)
#define Eusart_DisableSerialPin()                   (RCSTAbits.SPEN = 0)




/////////////////////////////////////////////////////////////////////////////////
/* Enable 9bit Transmit bit */
#define Eusart_Enable16bitBaueRate()                 (BAUDCONbits.BRG16 = 1)
#define Eusart_Disable16bitBaueRate()                (BAUDCONbits.BRG16 = 0)
#define Eusart_Select16bitBaueRateMode(_X_)          (BAUDCONbits.BRG16 = (_X_))


/////////////////////////////////////////////////////////////////////////////
/* Enable/disable Eusart Receiver*/
#define Eusart_EnableRx()                             (RCSTAbits.CREN = 1)
#define Eusart_DisableRx()                            (RCSTAbits.CREN = 0)

/* Enable 9bit for Receiving */
#define Eusart_Enable9bitReceiving()               (RCSTAbits.RX9 = 1)
#define Eusart_Disable9bitReceiving()              (RCSTAbits.RX9 = 0)
#define Eusart_Select9bitReceiving(_X_)            (RCSTAbits.RX9 = (_X_))


/* Read 9bit data of Receiving  */
#define Eusart_Get9bitDataValueRx()                (RCSTAbits.RX9D)

/* check if Frame Error Happens ( stop bit is 1 not 0 ) */
#define Eusart_IsFrameErrorHappened()              (RCSTAbits.FERR ==1 )

/* check if Overrun Happens ( receiving more than 2 bytes ) */
#define Eusart_IsOverRunErrorHappened()            (RCSTAbits.OERR ==1 )

/* check if there received Data  */
#define Eusart_IsRecevingDone()                     (PIR1bits.RCIF == 1)




/********************************** Data Type Declarations *******************************/

typedef enum{
    
    EUSART_BAUD_RATE_ASYNC_8bit_LOW_SPEED,
    EUSART_BAUD_RATE_ASYNC_16bit_LOW_SPEED = 1 ,
    EUSART_BAUD_RATE_ASYNC_8bit_HIGH_SPEED = 2,
    EUSART_BAUD_RATE_ASYNC_16bit_HIGH_SPEED =3,
    EUSART_BAUD_RATE_SYNC_8bit=4,
    EUSART_BAUD_RATE_SYNC_16bit=5
}Eusart_BaudRateType;

typedef enum{
    EUSART_9BIT_DATA_DISABLE,
    EUSART_9BIT_DATA_ENABLE
}Eusart_9bitDataSelectType;

typedef struct {
   uint32              baud_rate_value; 
   Eusart_BaudRateType baud_rate_mode;
   Eusart_9bitDataSelectType eusart_9bit_data_select;
   void (*EusartTx_InterruptHandler)(void);
   void (*EusartRx_InterruptHandler)(uint8 _data);
   void (*EusartFrammingError_InterruptHandler)(void);
   void (*EusartOverRunError_InterruptHandler)(void);
    Interrupt_PrioityType tx_interrupt_priority;
    Interrupt_PrioityType rx_interrupt_priority;

    
    
}Eusart_ConfigType;

/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Eusart_Init(const Eusart_ConfigType* _eusart);
Std_ReturnType Eusart_DeInit(const Eusart_ConfigType* _eusart);
Std_ReturnType Eusart_TransmitBlocking(const Eusart_ConfigType* _eusart, uint8 _data);
Std_ReturnType Eusart_TransmitStringBlocking(const Eusart_ConfigType* _eusart, uint8* _data_ptr);
Std_ReturnType Eusart_ReceiveBlocking(const Eusart_ConfigType* _eusart, uint8* _data);
Std_ReturnType Eusart_ReceiveNonBlocking(const Eusart_ConfigType* _eusart);


#endif	/* MCAL_EUSART_H */

