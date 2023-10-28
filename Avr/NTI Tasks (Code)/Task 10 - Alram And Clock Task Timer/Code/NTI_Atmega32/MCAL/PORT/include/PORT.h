/*
 * PORT.h
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */

#ifndef MCAL_PORT_INCLUDE_PORT_H_
#define MCAL_PORT_INCLUDE_PORT_H_


/********************************** Macros Declarations *******************************/

/* PORT A */
#define PORT_PINA0_CHANNEL0			0
#define PORT_PINA1_CHANNEL1			1
#define PORT_PINA2_CHANNEL2			2
#define PORT_PINA3_CHANNEL3			3
#define PORT_PINA4_CHANNEL4			4
#define PORT_PINA5_CHANNEL5			5
#define PORT_PINA6_CHANNEL6			6
#define PORT_PINA7_CHANNEL7			7


/* PORT B */
#define PORT_PINB0_CHANNEL8			    8
#define PORT_PINB1_CHANNEL9		      	9
#define PORT_PINB2_CHANNEL10			10
#define PORT_PINB3_CHANNEL11			11
#define PORT_PINB4_CHANNEL12			12
#define PORT_PINB5_CHANNEL13			13
#define PORT_PINB6_CHANNEL14			14
#define PORT_PINB7_CHANNEL15			15


/* PORT C */
#define PORT_PINC0_CHANNEL16			16
#define PORT_PINC1_CHANNEL17		    17
#define PORT_PINC2_CHANNEL18			18
#define PORT_PINC3_CHANNEL19			19
#define PORT_PINC4_CHANNEL20			20
#define PORT_PINC5_CHANNEL21			21
#define PORT_PINC6_CHANNEL22			22
#define PORT_PINC7_CHANNEL23			23


/* PORT D  */
#define PORT_PIND0_CHANNEL24			24
#define PORT_PIND1_CHANNEL25		    25
#define PORT_PIND2_CHANNEL26			26
#define PORT_PIND3_CHANNEL27			27
#define PORT_PIND4_CHANNEL28			28
#define PORT_PIND5_CHANNEL29			29
#define PORT_PIND6_CHANNEL30			30
#define PORT_PIND7_CHANNEL31			31



#define PORT_STATUS_PIN_MODE_OUTPUT_HIGH				0
#define PORT_STATUS_PIN_MODE_OUTPUT_LOW				1
#define PORT_STATUS_PIN_MODE_INPUT_FLOAT				2
#define PORT_STATUS_PIN_MODE_INPUT_PULL_UP			3


#define PORT_PIN_DIRECTION_INPUT			0
#define PORT_PIN_DIRECTION_OUTPUT			1

/********************************** Data Type Declarations *******************************/

typedef enum {

	PORT_STATUS_OK,
	PORT_STATUS_WRONG_DIRECTION,
	PORT_STATUS_WRONG_PIN_CHANNEL_ID

}Port_ErrorStatusType;

/********************************** Software Interfaces Declarations *******************************/

void Port_voidInit(void);

Port_ErrorStatusType Port_enuSetPinDirection(u8 Copy_u8PinNumber, u8 Copy_u8PinDirection);
Port_ErrorStatusType Port_enuSetPinMode(u8 Copy_u8PinNumber, u8 Copy_u8PinMode);



#endif /* MCAL_PORT_INCLUDE_PORT_H_ */
