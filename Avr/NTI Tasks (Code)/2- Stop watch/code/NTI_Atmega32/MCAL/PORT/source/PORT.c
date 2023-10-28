/*
 * PORT.c
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */



/********************************** Includes *****************************************/

#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/HELPERS.h"

#include "../include/PORT_private.h"
#include "../include/PORT_config.h"

#include "../include/PORT.h"



/********************************** static functions  *****************************************/

static volatile u8* Dio_DdraRegsiterArr[] = {&DDRA, &DDRB, &DDRC, &DDRD};
static volatile u8* Dio_PortRegistersArr[] = {&PORTA, &PORTB, &PORTC, &PORTD};



/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/


/********************************** Macros Declarations *******************************/



/********************************** Software Interfaces implementation *******************************/


void Port_voidInit(void){

	#undef PORT_STATUS_PIN_MODE_OUTPUT_HIGH
	#undef PORT_STATUS_PIN_MODE_OUTPUT_LOW
	#undef PORT_STATUS_PIN_MODE_INPUT_PULL_UP
	#undef PORT_STATUS_PIN_MODE_INPUT_FLOAT

	#define PORT_STATUS_PIN_MODE_OUTPUT_HIGH			1
	#define PORT_STATUS_PIN_MODE_OUTPUT_LOW				1
	#define PORT_STATUS_PIN_MODE_INPUT_PULL_UP			0
	#define PORT_STATUS_PIN_MODE_INPUT_FLOAT			0

	ASSIGN_REG(DDRA, CONCAT( PORT_u8PinChannel7_PINA7, PORT_u8PinChannel6_PINA6, PORT_u8PinChannel5_PINA5, PORT_u8PinChannel4_PINA4,	 PORT_u8PinChannel3_PINA3,	 PORT_u8PinChannel2_PINA2,	 PORT_u8PinChannel1_PINA1,	 PORT_u8PinChannel0_PINA0));
	ASSIGN_REG(DDRB, CONCAT( PORT_u8PinChannel15_PINB7, PORT_u8PinChannel14_PINB6, PORT_u8PinChannel13_PINB5, PORT_u8PinChannel12_PINB4,	 PORT_u8PinChannel11_PINB3,	 PORT_u8PinChannel10_PINB2,	 PORT_u8PinChannel9_PINB1,	 PORT_u8PinChannel8_PINB0));
	ASSIGN_REG(DDRC, CONCAT( PORT_u8PinChannel23_PINC7, PORT_u8PinChannel22_PINC6, PORT_u8PinChannel21_PINC5, PORT_u8PinChannel20_PINC4,	 PORT_u8PinChannel19_PINC3,	 PORT_u8PinChannel18_PINC2,	 PORT_u8PinChannel17_PINC1,	 PORT_u8PinChannel16_PINC0));

	ASSIGN_REG(DDRD, CONCAT( PORT_u8PinChannel31_PIND7, PORT_u8PinChannel30_PIND6, PORT_u8PinChannel29_PIND5, PORT_u8PinChannel28_PIND4,	 PORT_u8PinChannel27_PIND3,	 PORT_u8PinChannel26_PIND2,	 PORT_u8PinChannel25_PIND1,	 PORT_u8PinChannel24_PIND0));



	#undef PORT_STATUS_PIN_MODE_OUTPUT_LOW
	#undef PORT_STATUS_PIN_MODE_INPUT_PULL_UP


	#define PORT_STATUS_PIN_MODE_OUTPUT_LOW				0
	#define PORT_STATUS_PIN_MODE_INPUT_PULL_UP			1


	ASSIGN_REG(PORTA, CONCAT( PORT_u8PinChannel7_PINA7, PORT_u8PinChannel6_PINA6, PORT_u8PinChannel5_PINA5, PORT_u8PinChannel4_PINA4,	 PORT_u8PinChannel3_PINA3,	 PORT_u8PinChannel2_PINA2,	 PORT_u8PinChannel1_PINA1,	 PORT_u8PinChannel0_PINA0));
	ASSIGN_REG(PORTB, CONCAT( PORT_u8PinChannel15_PINB7, PORT_u8PinChannel14_PINB6, PORT_u8PinChannel13_PINB5, PORT_u8PinChannel12_PINB4,	 PORT_u8PinChannel11_PINB3,	 PORT_u8PinChannel10_PINB2,	 PORT_u8PinChannel9_PINB1,	 PORT_u8PinChannel8_PINB0));
	ASSIGN_REG(PORTC, CONCAT( PORT_u8PinChannel23_PINC7, PORT_u8PinChannel22_PINC6, PORT_u8PinChannel21_PINC5, PORT_u8PinChannel20_PINC4,	 PORT_u8PinChannel19_PINC3,	 PORT_u8PinChannel18_PINC2,	 PORT_u8PinChannel17_PINC1,	 PORT_u8PinChannel16_PINC0));

	ASSIGN_REG(PORTD, CONCAT( PORT_u8PinChannel31_PIND7, PORT_u8PinChannel30_PIND6, PORT_u8PinChannel29_PIND5, PORT_u8PinChannel28_PIND4,	 PORT_u8PinChannel27_PIND3,	 PORT_u8PinChannel26_PIND2,	 PORT_u8PinChannel25_PIND1,	 PORT_u8PinChannel24_PIND0));




#undef PORT_STATUS_PIN_MODE_OUTPUT_HIGH
#undef PORT_STATUS_PIN_MODE_OUTPUT_LOW
#undef PORT_STATUS_PIN_MODE_INPUT_FLOAT
#undef PORT_STATUS_PIN_MODE_INPUT_PULL_UP


#define PORT_STATUS_PIN_MODE_OUTPUT_HIGH				0
#define PORT_STATUS_PIN_MODE_OUTPUT_LOW				1
#define PORT_STATUS_PIN_MODE_INPUT_FLOAT				2
#define PORT_STATUS_PIN_MODE_INPUT_PULL_UP			3


}

Port_ErrorStatusType Port_enuSetPinDirection(u8 Copy_u8PinNumber, u8 Copy_u8PinDirection){

	Port_ErrorStatusType Loc_enuState = PORT_STATUS_OK;
	u8 Loc_PinNumber = Copy_u8PinNumber %8;
	u8 Loc_PortNumber = Copy_u8PinNumber /8;

	if(Copy_u8PinNumber > PORT_MAX_INDEX_OF_CHANNEL_ID ){
		Loc_enuState = PORT_STATUS_WRONG_PIN_CHANNEL_ID;
	}

	else if(Copy_u8PinDirection > PORT_MAX_INDEX_OF_DIRECTION ){
			Loc_enuState = PORT_STATUS_WRONG_DIRECTION;
		}

	else{

			switch(Copy_u8PinDirection){

			case PORT_PIN_DIRECTION_OUTPUT :
					SET_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber);
					break;

			case PORT_PIN_DIRECTION_INPUT :
							CLEAR_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber);
							break;

			default:

				// impossible
					break;

			}



	}



	return Loc_enuState;
}
Port_ErrorStatusType Port_enuSetPinMode(u8 Copy_u8PinNumber, u8 Copy_u8PinMode){

	Port_ErrorStatusType Loc_enuState = PORT_STATUS_OK;
	u8 Loc_PinNumber = Copy_u8PinNumber %8;
	u8 Loc_PortNumber = Copy_u8PinNumber /8;

	if(Copy_u8PinNumber > PORT_MAX_INDEX_OF_CHANNEL_ID ){
		Loc_enuState = PORT_STATUS_WRONG_PIN_CHANNEL_ID;
	}

	else if(Copy_u8PinMode > PORT_MAX_INDEX_OF_PIN_MODE ){
			Loc_enuState = PORT_STATUS_WRONG_DIRECTION;
		}

	else{

			switch(Copy_u8PinMode){

			case PORT_STATUS_PIN_MODE_OUTPUT_HIGH :
					SET_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber);
					SET_BIT(*Dio_PortRegistersArr[Loc_PortNumber],Loc_PinNumber);
					break;

			case PORT_STATUS_PIN_MODE_OUTPUT_LOW :
						SET_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber);
						CLEAR_BIT(*Dio_PortRegistersArr[Loc_PortNumber],Loc_PinNumber);
							break;

			case PORT_STATUS_PIN_MODE_INPUT_FLOAT :
								CLEAR_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber);
								CLEAR_BIT(*Dio_PortRegistersArr[Loc_PortNumber],Loc_PinNumber);
								break;
			case PORT_STATUS_PIN_MODE_INPUT_PULL_UP :
								CLEAR_BIT(*Dio_DdraRegsiterArr[Loc_PortNumber],Loc_PinNumber);
								SET_BIT(*Dio_PortRegistersArr[Loc_PortNumber],Loc_PinNumber);
								break;



			default:

				// impossible
					break;

			}



	}

	return Loc_enuState;
}
