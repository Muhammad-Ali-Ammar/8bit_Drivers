/*
 * PORT_private.h
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */



#ifndef MCAL_PORT_INCLUDE_PORT_PRIVATE_H_
#define MCAL_PORT_INCLUDE_PORT_PRIVATE_H_



/********************************** Macros Declarations *******************************/

/* private regsiters for PORT A */

#define PORTA		(*(volatile u8*)(0x3B))
#define DDRA		(*(volatile u8*)(0x3A))
#define PINA		(*(volatile u8*)(0x39))


/* private regsiters for PORT B */

#define PORTB		(*(volatile u8*)(0x38))
#define DDRB		(*(volatile u8*)(0x37))
#define PINB		(*(volatile u8*)(0x36))


/* private regsiters for PORT A */

#define PORTC		(*(volatile u8*)(0x35))
#define DDRC		(*(volatile u8*)(0x34))
#define PINC		(*(volatile u8*)(0x33))


/* private regsiters for PORT B */

#define PORTD		(*(volatile u8*)(0x32))
#define DDRD		(*(volatile u8*)(0x31))
#define PIND		(*(volatile u8*)(0x30))




#define PORT_REGISTER_SIZE			8
#define PORT_MAX_INDEX_OF_CHANNEL_ID	31
#define PORT_MAX_INDEX_OF_PORT	3
#define PORT_MAX_INDEX_OF_DIRECTION	1
#define PORT_MAX_INDEX_OF_PIN_MODE		3





#endif /* MCAL_PORT_INCLUDE_PORT_PRIVATE_H_ */
