/* 
 * File:   mcal_eusart.c
 * Author: 
 *
 * Created on 24 ?????, 2023, 11:14 ?
 */



/********************************** Includes *****************************************/
#include "mcal_eusart.h"

/********************************** Private  definition  and declaration  *****************************************/

#if INTERRUPT_EUSART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EusartTx_InterruptHandler)( void);
#endif

#if INTERRUPT_EUSART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EusartRx_InterruptHandler)(uint8 _data);
static void (*EusartFrammingError_InterruptHandler)( void);
static void (*EusartOverRun_InterruptHandler)( void);
#endif




static Std_ReturnType Eusart_ConfigureInterrupt(const Eusart_ConfigType* _eusart);
static Std_ReturnType Eusart_ConfigureBaudRateMode(const Eusart_ConfigType* _eusart);
static Std_ReturnType Eusart_ConfigurePins(const Eusart_ConfigType* _eusart);
/********************************** Public Function Implementation  *****************************************/

Std_ReturnType Eusart_Init(const Eusart_ConfigType* _eusart){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        
        /* Disable Uart Peripheral */
        Eusart_DisableSerialPin();
        Eusart_DisableTx();
        Eusart_DisableRx();
        
        /* Configure Baud rate */
        ret &= Eusart_ConfigureBaudRateMode(_eusart);
        
        /* configure the 9bit of transmitter and receiver */
        Eusart_Select9bitTransmission(_eusart->eusart_9bit_data_select);
        Eusart_Select9bitReceiving(_eusart->eusart_9bit_data_select);
        
        /*Configure Pins Of serial */
        ret &=Eusart_ConfigurePins(_eusart);
        
        /* Configure the Interrupt */
        ret &=Eusart_ConfigureInterrupt(_eusart);
        
        /* Enable Usart Peripheral*/
        Eusart_EnableSerialPin();
        Eusart_EnableTx();
        Eusart_EnableRx();
    }
    
    return ret;
}
Std_ReturnType Eusart_DeInit(const Eusart_ConfigType* _eusart){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        /*Disable */
        Eusart_DisableSerialPin();
        Eusart_DisableTx();
        Eusart_DisableRx();
        
#if INTERRUPT_EUSART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        EusartTx_DisableInterrupt();
#endif
        
#if INTERRUPT_EUSART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        EusartRx_DisableInterrupt();
#endif
    }
    
    return ret;
}
Std_ReturnType Eusart_TransmitBlocking(const Eusart_ConfigType* _eusart, uint8 _data){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        while(Eusart_IsShiftRegEmpty() == EUSART_FALSE);
        TXREG = _data;
    }
    
    return ret;
}
Std_ReturnType Eusart_ReceiveBlocking(const Eusart_ConfigType* _eusart, uint8* _data){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart || NULL == _data ){
        ret = E_NOT_OK;
    }
    else{
        Eusart_EnableRx();
        while(Eusart_IsRecevingDone() == EUSART_FALSE);
        *_data = RCREG;
    }
    
    return ret;
}

Std_ReturnType Eusart_TransmitStringBlocking(const Eusart_ConfigType* _eusart, uint8* _data_ptr){
    Std_ReturnType ret = E_OK;
    uint16 l_counter = ZERO_VALUE;
    if(NULL == _eusart || NULL == _data_ptr ){
        ret = E_NOT_OK;
    }
    else{
        for(l_counter = ZERO_VALUE; _data_ptr[l_counter] != 0; l_counter++){
            Eusart_TransmitBlocking(_eusart,_data_ptr[l_counter]);
        }
    }
    
    return ret;
}

Std_ReturnType Eusart_ReceiveNonBlocking(const Eusart_ConfigType* _eusart){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _eusart) {
        ret = E_NOT_OK;
    }
    
    else{
        
        Eusart_EnableRx();
    }
    
    return ret;
}

/********************************** Private Function Implementation  *****************************************/
static Std_ReturnType Eusart_ConfigureBaudRateMode(const Eusart_ConfigType* _eusart){
    Std_ReturnType ret = E_OK;
    uint16 l_baud_rate_value =0;
    uint8 l_baudrate_mode = (uint8)_eusart->baud_rate_mode;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        
        Eusart_SelectSynchronizationMode( ((l_baudrate_mode>>2)&0x01) );
        Eusart_SelectAsyncSpeed( ((l_baudrate_mode>>1)&0x01) );
        Eusart_Select16bitBaueRateMode( ((l_baudrate_mode)&0x01) );
        
        switch(_eusart->baud_rate_mode){
            
            case EUSART_BAUD_RATE_ASYNC_8bit_LOW_SPEED:
                /* baud rate = Fosc/[64*(n+1)] */
                l_baud_rate_value = (uint16)((((float32)_XTAL_FREQ/_eusart->baud_rate_value)/64)-1);
                break;
            
            case EUSART_BAUD_RATE_ASYNC_8bit_HIGH_SPEED:
            case EUSART_BAUD_RATE_ASYNC_16bit_LOW_SPEED:
                 /* baud rate = Fosc/[16*(n+1)] */
                l_baud_rate_value = (uint16)((((float32)_XTAL_FREQ/_eusart->baud_rate_value)/16)-1);
                break;
                
            case EUSART_BAUD_RATE_ASYNC_16bit_HIGH_SPEED:
            case EUSART_BAUD_RATE_SYNC_8bit:
            case EUSART_BAUD_RATE_SYNC_16bit:
                 /* baud rate = Fosc/[4*(n+1)] */
                l_baud_rate_value = (uint16)((((float32)_XTAL_FREQ/_eusart->baud_rate_value)/4)-1);
                break;
                
            default : 
                ret = E_NOT_OK;
        }
        
        SPBRG = (uint8)(l_baud_rate_value &0xFF);
        SPBRGH = (uint8)((l_baud_rate_value>>8) &0xFF);
    }
    
    return ret;
}


static Std_ReturnType Eusart_ConfigurePins(const Eusart_ConfigType* _eusart){
    Std_ReturnType ret = E_OK;
    Dio_PinConfigType l_tx_pin ={
                .direction = DIO_DIRECTION_INPUT,
                .logic = DIO_LOW,
                .port = DIO_PORTC_INDEX,
                .pin = DIO_PIN6
                         };
    Dio_PinConfigType l_rx_pin ={
                .direction = DIO_DIRECTION_INPUT,
                .logic = DIO_LOW,
                .port = DIO_PORTC_INDEX,
                .pin = DIO_PIN7 };
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else{
        
        ret &= Dio_InitChannelDirection(&l_tx_pin);
        ret &= Dio_InitChannelDirection(&l_rx_pin);
    }
    
    return ret;
}

static Std_ReturnType Eusart_ConfigureInterrupt (const Eusart_ConfigType* _eusart){
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart ){
        
        ret = E_NOT_OK;
    }
    else{
 
 /* Transmitter*/
 #if INTERRUPT_EUSART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        EusartTx_InterruptHandler = _eusart->EusartTx_InterruptHandler;
        EusartTx_EnableInterrupt();
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 EusartTx_SetPrioirty(_eusart->tx_interrupt_priority);
                 Interrupt_EnablePrioirtyOfTheSystem();
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
    #else 
            Interrupt_EnableGlobalInterrupt();
            Interrupt_EnablePeripheralInterrupt();
    #endif
        
        
#endif  
            
 #if INTERRUPT_EUSART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        EusartRx_InterruptHandler = _eusart->EusartRx_InterruptHandler;
        EusartFrammingError_InterruptHandler = _eusart->EusartFrammingError_InterruptHandler;
        EusartOverRun_InterruptHandler = _eusart->EusartOverRunError_InterruptHandler;
        EusartRx_EnableInterrupt();
        Eusart_DisableRx();
    #if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                 EusartRx_SetPrioirty(_eusart->rx_interrupt_priority);
                 Interrupt_EnablePrioirtyOfTheSystem();
                 Interrupt_EnableHighGlobalInterrupt();
                 Interrupt_EnableLowGlobalInterrupt();
    #else 
            Interrupt_EnableGlobalInterrupt();
            Interrupt_EnablePeripheralInterrupt();
    #endif
        
        
#endif  
            
}
    return ret;
}


 #if INTERRUPT_EUSART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Interrupt Handler */
void EusartTx_ISR(){
//    EusartTx_ClearFlag();  //  done by HW ( after sending start bit )
    Std_ReturnType ret = E_OK;
    EusartTx_DisableInterrupt();
    if(NULL != EusartTx_InterruptHandler){
        EusartTx_InterruptHandler();
    }
    else {/* do nothing , error in declaration */ }
    
    EusartTx_EnableInterrupt();
}
#endif

 #if INTERRUPT_EUSART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* Interrupt Handler */
void EusartRx_ISR(){
    Std_ReturnType ret = E_OK;
    uint8 l_data_value = RCREG;
//    EusartRx_ClearFlag();//  done by HW ( after Reading RCREG, previous line )
    
    if(NULL != EusartRx_InterruptHandler){
        EusartRx_InterruptHandler(l_data_value);
    }
    else {/* do nothing , error in declaration */ }
    
    
    if(NULL != EusartFrammingError_InterruptHandler){
        EusartFrammingError_InterruptHandler();
    }
    else {/* do nothing */ }
    
    
    if(NULL != EusartOverRun_InterruptHandler){
        EusartOverRun_InterruptHandler();
    }
    
    else {/* do nothing */ }
    
    Eusart_DisableRx();
}
#endif
