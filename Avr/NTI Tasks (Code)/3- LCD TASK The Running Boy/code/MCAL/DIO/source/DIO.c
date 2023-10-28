/*
 * DIO.c
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */



/********************************** Includes *****************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"


#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/HELPERS.h"

#include "../include/DIO_private.h"
#include "../include/DIO_config.h"
#include "../include/DIO.h"


static volatile u8* Dio_DdraRegsiterArr[] = {&DDRA, &DDRB, &DDRC, &DDRD};
static volatile u8* Dio_PortRegistersArr[] = {&PORTA, &PORTB, &PORTC, &PORTD};
static volatile u8* Dio_PinRegistersArr[] = {&PINA, &PINB, &PINC, &PIND};


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/


/********************************** Macros Declarations *******************************/



/********************************** Software Interfaces Declarations *******************************/

Dio_ErrorStatusType	Dio_enuWriteChannel(u8 Copy_u8ChannelId,u8 Copy_u8Level){

	Dio_ErrorStatusType Loc_enuState = DIO_STATUS_OK;
	u8 Loc_PinNumber = Copy_u8ChannelId %8;
	u8 Loc_PortNumber = Copy_u8ChannelId /8;

	if(Copy_u8ChannelId > DIO_MAX_INDEX_OF_CHANNEL_ID ){
		Loc_enuState = DIO_STATUS_WRONG_PIN_CHANNEL_ID;
	}

	else if( (READ_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber)) != DIO_PIN_OUTPUT ){
			Loc_enuState = DIO_STATUS_WRONG_DIRECTION;
		}

	else{

		WRITE_BIT( (*Dio_PortRegistersArr[Loc_PortNumber]), Loc_PinNumber  ,  (Copy_u8Level) );

}

	return Loc_enuState;
}
Dio_ErrorStatusType	Dio_enuReadChannel(u8 Copy_u8ChannelId,pu8 Address_pu8ChannelLevel){

	Dio_ErrorStatusType Loc_enuState = DIO_STATUS_OK;
		u8 Loc_PinNumber = Copy_u8ChannelId %8;
		u8 Loc_PortNumber = Copy_u8ChannelId /8;

		if(Copy_u8ChannelId > DIO_MAX_INDEX_OF_CHANNEL_ID ){
			Loc_enuState = DIO_STATUS_WRONG_PIN_CHANNEL_ID;
		}

		else if(  (READ_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber)) != DIO_PIN_INPUT){
				Loc_enuState = DIO_STATUS_WRONG_DIRECTION;
			}

		else if(Address_pu8ChannelLevel == NULL){
			Loc_enuState = DIO_STATUS_NULL_POINTER_ADDRESS;

		}

		else{

			*Address_pu8ChannelLevel = READ_BIT(*Dio_PinRegistersArr[Loc_PortNumber],Loc_PinNumber);


	}

		return Loc_enuState;

}



Dio_ErrorStatusType	Dio_enuWritePort(u8 Copy_u8PortId,u8 Copy_u8Value){
	Dio_ErrorStatusType Loc_enuState = DIO_STATUS_OK;


		if(Copy_u8PortId > DIO_MAX_INDEX_OF_PORT ){
			Loc_enuState = DIO_STATUS_WRONG_PORT_ID;
		}

		else if( *Dio_DdraRegsiterArr[Copy_u8PortId] != DIO_PORT_OUTPUT ){
				Loc_enuState = DIO_STATUS_WRONG_DIRECTION;
			}

		else{

			ASSIGN_REG(*Dio_PortRegistersArr[Copy_u8PortId], Copy_u8Value);

	}

		return Loc_enuState;



}


Dio_ErrorStatusType	Dio_enuReadPort(u8 Copy_u8PortId,pu8 Address_pu8PortVAlue){
	Dio_ErrorStatusType Loc_enuState = DIO_STATUS_OK;


			if(Copy_u8PortId > DIO_MAX_INDEX_OF_PORT ){
				Loc_enuState = DIO_STATUS_WRONG_PORT_ID;
			}

			else if( *Dio_DdraRegsiterArr[Copy_u8PortId] != DIO_PORT_INPUT ){
					Loc_enuState = DIO_STATUS_WRONG_DIRECTION;
				}

			else if(Address_pu8PortVAlue == NULL){
				Loc_enuState = DIO_STATUS_NULL_POINTER_ADDRESS;
			}
			else{

				*Address_pu8PortVAlue = *Dio_PinRegistersArr[Copy_u8PortId];

		}

			return Loc_enuState;

}
Dio_ErrorStatusType	Dio_enuFlipChannel(u8 Copy_u8ChannelId){

	Dio_ErrorStatusType Loc_enuState = DIO_STATUS_OK;
		u8 Loc_PinNumber = Copy_u8ChannelId %8;
		u8 Loc_PortNumber = Copy_u8ChannelId /8;

		if(Copy_u8ChannelId > DIO_MAX_INDEX_OF_CHANNEL_ID ){
			Loc_enuState = DIO_STATUS_WRONG_PIN_CHANNEL_ID;
		}

		else if( (READ_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber)) != DIO_PIN_OUTPUT ){
				Loc_enuState = DIO_STATUS_WRONG_DIRECTION;
			}

		else{

			TOGGLE_BIT( (*Dio_PortRegistersArr[Loc_PinNumber]), Loc_PinNumber);

	}

		return Loc_enuState;
}
