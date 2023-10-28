/* 
 * File:   mcal_gpio.h
 * Author: Ammar
 *
 * Created on 24 ??????, 2022, 10:50 ?
 */

#ifndef MCAL_GPIO_H
#define	MCAL_GPIO_H

/**********************************Includes *******************************/
#include "../mcal_std_types.h"
#include "../mcal_device_config.h"
#include "pic18f4620.h"
#include "mcal_gpio_cfg.h"
/********************************** Macros Function Declarations *******************************/

#define SET_BIT(REG_ADDR, BIT_POSN)             ( (REG_ADDR) |= (DIO_BIT0_MASK<< (BIT_POSN)))
#define CLEAR_BIT(REG_ADDR, BIT_POSN)           ( (REG_ADDR) &= ~ (DIO_BIT0_MASK<< (BIT_POSN)))
#define TOGGLE_BIT(REG_ADDR, BIT_POSN)          ( (REG_ADDR) ^= (DIO_BIT0_MASK<< (BIT_POSN)))
#define READ_BIT(REG_ADDR, BIT_POSN)            (( (REG_ADDR)>>(BIT_POSN) ) & (DIO_BIT0_MASK))


/********************************** Data Type Declarations *******************************/
typedef enum {
    
    DIO_LOW=0,
    DIO_HIGH
    
}Dio_LogicPinType;

typedef enum {
    
    DIO_DIRECTION_OUTPUT=0,
    DIO_DIRECTION_INPUT
    
}Dio_DirectionType;

typedef enum {
    
    DIO_PIN0=0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7
            
}Dio_PinIndexType;


typedef enum {
    
    DIO_PORTA_INDEX=0,
    DIO_PORTB_INDEX,
    DIO_PORTC_INDEX,
    DIO_PORTD_INDEX,
    DIO_PORTE_INDEX
            
}Dio_PortIndexType;


typedef struct{
    Dio_PortIndexType port;     
    Dio_PinIndexType pin;
    Dio_DirectionType direction;
    Dio_LogicPinType logic;
    
}Dio_PinConfigType;



/********************************** Macros Declarations *******************************/


#define DIO_BIT0_MASK            ((uint8)1)

#define DIO_PORT_MAX_INDEX      ((Dio_PortIndexType)4)
#define DIO_PIN_MAX_INDEX       ((Dio_PinIndexType)7)
#define DIO_LOGIC_MAX_LEVEL     ((Dio_LogicPinType)1)

#define DIO_PORTC_MASK_FULL     ((uint8)0xFF) 

/********************************** Software Interfaces Declarations *******************************/


/*For channels */
Std_ReturnType Dio_InitChannel(const Dio_PinConfigType* _PinConfig);

Std_ReturnType Dio_InitChannelDirection(const Dio_PinConfigType* _PinConfig);
Std_ReturnType Dio_ReadChannelDirection(const Dio_PinConfigType* _PinConfig, Dio_DirectionType* DirectionStatus );

Std_ReturnType Dio_WriteChannel(const Dio_PinConfigType* _PinConfig, Dio_LogicPinType Logic);
Std_ReturnType Dio_ReadChannel(const Dio_PinConfigType* _PinConfig, Dio_LogicPinType* Logic);
Std_ReturnType Dio_ToggleChannel(const Dio_PinConfigType* _PinConfig);


/*******For Ports *********/
Std_ReturnType Dio_InitPortDirection(Dio_PortIndexType port, uint8 Direction);
Std_ReturnType Dio_ReadPortDirection(Dio_PortIndexType port, uint8* DirectionStatus);


Std_ReturnType Dio_WritePort(Dio_PortIndexType port, uint8 Logic);
Std_ReturnType Dio_ReadPort(Dio_PortIndexType port, uint8* Logic);
Std_ReturnType Dio_TogglePort(Dio_PortIndexType port);





#endif	/* MCAL_GPIO_H */

