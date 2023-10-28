/*
 * DIO.h
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */

#ifndef MCAL_DIO_INCLUDE_DIO_H_
#define MCAL_DIO_INCLUDE_DIO_H_

/********************************** Includes *****************************************/





/********************************** Macros Function Declarations *******************************/




/********************************** Macros Declarations *******************************/

/* PORT A */
#define DIO_PINA0_CHANNEL0			0
#define DIO_PINA1_CHANNEL1			1
#define DIO_PINA2_CHANNEL2			2
#define DIO_PINA3_CHANNEL3			3
#define DIO_PINA4_CHANNEL4			4
#define DIO_PINA5_CHANNEL5			5
#define DIO_PINA6_CHANNEL6			6
#define DIO_PINA7_CHANNEL7			7


/* PORT B */
#define DIO_PINB0_CHANNEL8			    8
#define DIO_PINB1_CHANNEL9		      	9
#define DIO_PINB2_CHANNEL10			10
#define DIO_PINB3_CHANNEL11			11
#define DIO_PINB4_CHANNEL12			12
#define DIO_PINB5_CHANNEL13			13
#define DIO_PINB6_CHANNEL14			14
#define DIO_PINB7_CHANNEL15			15


/* PORT C */
#define DIO_PINC0_CHANNEL16			16
#define DIO_PINC1_CHANNEL17		    17
#define DIO_PINC2_CHANNEL18			18
#define DIO_PINC3_CHANNEL19			19
#define DIO_PINC4_CHANNEL20			20
#define DIO_PINC5_CHANNEL21			21
#define DIO_PINC6_CHANNEL22			22
#define DIO_PINC7_CHANNEL23			23


/* PORT D  */
#define DIO_PIND0_CHANNEL24			24
#define DIO_PIND1_CHANNEL25		    25
#define DIO_PIND2_CHANNEL26			26
#define DIO_PIND3_CHANNEL27			27
#define DIO_PIND4_CHANNEL28			28
#define DIO_PIND5_CHANNEL29			29
#define DIO_PIND6_CHANNEL30			30
#define DIO_PIND7_CHANNEL31			31



#define DIO_PORTA					0
#define DIO_PORTB					1
#define DIO_PORTC					2
#define DIO_PORTD					3


#define DIO_PIN_INPUT					0
#define DIO_PIN_OUTPUT					1

#define DIO_HIGH					1
#define DIO_LOW						0


#define DIO_PORT_INPUT					0x00
#define DIO_PORT_OUTPUT					0xFF

/********************************** Data Type Declarations *******************************/
typedef enum{

	    DIO_STATUS_OK,
		DIO_STATUS_WRONG_DIRECTION,
		DIO_STATUS_WRONG_PIN_CHANNEL_ID,
		DIO_STATUS_WRONG_PORT_ID,
		DIO_STATUS_NULL_POINTER_ADDRESS
}Dio_ErrorStatusType;

/********************************** Software Interfaces Declarations *******************************/

Dio_ErrorStatusType	Dio_enuWriteChannel(u8 Copy_u8ChannelId,u8 Copy_u8Level);
Dio_ErrorStatusType	Dio_enuReadChannel(u8 Copy_u8ChannelId,pu8 Address_pu8ChannelLevel);

Dio_ErrorStatusType	Dio_enuWritePort(u8 Copy_u8PortId,u8 Copy_u8Value);
Dio_ErrorStatusType	Dio_enuReadPort(u8 Copy_u8PortId,pu8 Address_pu8PortVAlue);
Dio_ErrorStatusType	Dio_enuFlipChannel(u8 Copy_u8ChannelId);



#endif /* MCAL_DIO_INCLUDE_DIO_H_ */
