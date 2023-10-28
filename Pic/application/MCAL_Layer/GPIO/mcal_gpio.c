/* 
 * File:   gpio.c
 * Author: Ammar
 *
 * Created on 24 ??????, 2022, 01:29 ?
 */


#include "mcal_gpio.h"

#if DIO_CONFIG == CONFIG_ENABLE

static volatile uint8* Dio_TrisRegistersArr[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
static volatile uint8* Dio_PortRegistersArr[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
static volatile uint8* Dio_LatRegistersArr[] = {&LATA, &LATB, &LATC, &LATD, &LATE};


/**
 * @brief Initialize the pin configuratio 
 * @param _PinConfig is a pointer to configuration @ref Dio_PinConfigType
 * @return Status of the function 
 *          (E_OK) : The function done successfully 
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType Dio_InitChannel(const Dio_PinConfigType* _PinConfig) {

    Std_ReturnType ret = E_OK;
    

    if (NULL == _PinConfig ||
            DIO_PORT_MAX_INDEX < _PinConfig->port || DIO_PIN_MAX_INDEX < _PinConfig->pin) {

        ret = E_NOT_OK;
    } 
        else{
            ret = Dio_InitChannelDirection(_PinConfig);
            ret = ret & Dio_WriteChannel(_PinConfig, _PinConfig->logic);
        }


    return ret;
}

/**
 * 
 * @param _PinConfig
 * @return 
 */
Std_ReturnType Dio_InitChannelDirection(const Dio_PinConfigType* _PinConfig) {

    Std_ReturnType ret = E_OK;

    if (NULL == _PinConfig ||
            DIO_PORT_MAX_INDEX < _PinConfig->port || DIO_PIN_MAX_INDEX < _PinConfig->pin) {

        ret = E_NOT_OK;
    } else {

        switch (_PinConfig->direction) {

            case DIO_DIRECTION_OUTPUT:
                CLEAR_BIT((*Dio_TrisRegistersArr[_PinConfig->port]), _PinConfig->pin);
                break;


            case DIO_DIRECTION_INPUT:
                SET_BIT((*Dio_TrisRegistersArr[_PinConfig->port]), _PinConfig->pin);
                break;

            default:
                ret = E_NOT_OK;

        }


    }

    return ret;

}

Std_ReturnType Dio_ReadChannelDirection(const Dio_PinConfigType* _PinConfig, Dio_DirectionType* DirectionStatus) {

    Std_ReturnType ret = E_OK;
    
    if (NULL == _PinConfig || NULL == DirectionStatus ||
            DIO_PORT_MAX_INDEX < _PinConfig->port || DIO_PIN_MAX_INDEX < _PinConfig->pin){
        
        ret = E_NOT_OK;
        
    }
    
    else{
        *DirectionStatus =  READ_BIT((*Dio_TrisRegistersArr[_PinConfig->port]), _PinConfig->pin);
    }


    return ret;

}

Std_ReturnType Dio_WriteChannel(const Dio_PinConfigType* _PinConfig, Dio_LogicPinType Logic) {
    Std_ReturnType ret = E_OK;

    if (NULL == _PinConfig ||
            DIO_PORT_MAX_INDEX < _PinConfig->port || DIO_PIN_MAX_INDEX < _PinConfig->pin) {

        ret = E_NOT_OK;
    } else {

        switch (Logic) {
            case DIO_LOW:
                CLEAR_BIT((*Dio_LatRegistersArr[_PinConfig->port]), _PinConfig->pin);
                break;

            case DIO_HIGH:
                SET_BIT((*Dio_LatRegistersArr[_PinConfig->port]), _PinConfig->pin);
                break;

            default:
                ret = E_NOT_OK;
        }
    }


    return ret;

}

Std_ReturnType Dio_ReadChannel(const Dio_PinConfigType* _PinConfig, Dio_LogicPinType* Logic) {
    Std_ReturnType ret = E_OK;
    if (NULL == _PinConfig || NULL == Logic ||
            DIO_PORT_MAX_INDEX < _PinConfig->port || DIO_PIN_MAX_INDEX < _PinConfig->pin){
        
        ret = E_NOT_OK;
        
    }
    else{
        (*Logic) =  READ_BIT((*Dio_PortRegistersArr[_PinConfig->port]), _PinConfig->pin);
    }

    return ret;

}

Std_ReturnType Dio_ToggleChannel(const Dio_PinConfigType* _PinConfig) {

    Std_ReturnType ret = E_OK;

     if (NULL == _PinConfig ||
            DIO_PORT_MAX_INDEX < _PinConfig->port || DIO_PIN_MAX_INDEX < _PinConfig->pin) {

        ret = E_NOT_OK;
    } else {
         TOGGLE_BIT((*Dio_LatRegistersArr[_PinConfig->port]), _PinConfig->pin);
    }


    return ret;
}

Std_ReturnType Dio_InitPortDirection(Dio_PortIndexType port, uint8 Direction) {

    Std_ReturnType ret = E_OK;
    
     if (DIO_PORT_MAX_INDEX < port ) {

        ret = E_NOT_OK;
    } else {
         
         *Dio_TrisRegistersArr[port] = Direction;  
    }
    


    return ret;
}

Std_ReturnType Dio_ReadPortDirection(Dio_PortIndexType port, uint8* DirectionStatus) {

    Std_ReturnType ret = E_OK;
    
     if (DIO_PORT_MAX_INDEX < port || NULL == DirectionStatus) {

        ret = E_NOT_OK;
    } else {
         
         *DirectionStatus =  *Dio_PortRegistersArr[port];
         
    }


    return ret;
}

Std_ReturnType Dio_WritePort(Dio_PortIndexType port, uint8 Logic) {
    Std_ReturnType ret = E_OK;

     if (DIO_PORT_MAX_INDEX < port ) {

        ret = E_NOT_OK;
    } else {
         
         *Dio_LatRegistersArr[port] = Logic; 
    }

    return ret;

}

Std_ReturnType Dio_ReadPort(Dio_PortIndexType port, uint8* Logic) {

    Std_ReturnType ret = E_OK;


     if (DIO_PORT_MAX_INDEX < port || NULL == Logic ) {

        ret = E_NOT_OK;
    } else {
         
         *Logic = *Dio_PortRegistersArr[port]; 
         
    }

    return ret;
    
}

Std_ReturnType Dio_TogglePort(Dio_PortIndexType port) {
    Std_ReturnType ret = E_OK;

    
     if (DIO_PORT_MAX_INDEX < port ) {

        ret = E_NOT_OK;
    } else {
         
         (*Dio_LatRegistersArr[port]) ^= DIO_PORTC_MASK_FULL; 
    }


    return ret;

}


#endif