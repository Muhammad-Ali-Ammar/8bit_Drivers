/*
 * PORT_config.h
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */

#ifndef MCAL_PORT_INCLUDE_PORT_CONFIG_H_
#define MCAL_PORT_INCLUDE_PORT_CONFIG_H_

/*
 * 	PORT_STATUS_PIN_MODE_OUTPUT_HIGH
 * 	PORT_STATUS_PIN_MODE_OUTPUT_LOW
 * 	PORT_STATUS_PIN_MODE_INPUT_FLOAT
 * 	PORT_STATUS_PIN_MODE_INPUT_PULL_UP
 *
 *
 *
 */
/* PORT A */
#define PORT_u8PinChannel0_PINA0		PORT_STATUS_PIN_MODE_INPUT_FLOAT
#define PORT_u8PinChannel1_PINA1		PORT_STATUS_PIN_MODE_INPUT_FLOAT
#define PORT_u8PinChannel2_PINA2		PORT_STATUS_PIN_MODE_OUTPUT_LOW //segm_Com2 , LCD EN
#define PORT_u8PinChannel3_PINA3		PORT_STATUS_PIN_MODE_OUTPUT_LOW //segm_Com1 ,  LCD RS
#define PORT_u8PinChannel4_PINA4		PORT_STATUS_PIN_MODE_INPUT_FLOAT
#define PORT_u8PinChannel5_PINA5		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel6_PINA6		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel7_PINA7		PORT_STATUS_PIN_MODE_INPUT_FLOAT

/* PORT B */
#define PORT_u8PinChannel8_PINB0	    PORT_STATUS_PIN_MODE_OUTPUT_LOW  // LCD D4
#define PORT_u8PinChannel9_PINB1 		PORT_STATUS_PIN_MODE_OUTPUT_LOW	// LCD D5
#define PORT_u8PinChannel10_PINB2		PORT_STATUS_PIN_MODE_OUTPUT_LOW  // INT2 , LCD D6
#define PORT_u8PinChannel11_PINB3		PORT_STATUS_PIN_MODE_INPUT_FLOAT
#define PORT_u8PinChannel12_PINB4		PORT_STATUS_PIN_MODE_OUTPUT_LOW // LCD D7
#define PORT_u8PinChannel13_PINB5		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel14_PINB6		PORT_STATUS_PIN_MODE_OUTPUT_HIGH //seg_com4
#define PORT_u8PinChannel15_PINB7		PORT_STATUS_PIN_MODE_OUTPUT_HIGH //seg_com3


/* PORT C */
#define PORT_u8PinChannel16_PINC0		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel17_PINC1		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel18_PINC2		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel19_PINC3		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel20_PINC4		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel21_PINC5		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel22_PINC6		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel23_PINC7		PORT_STATUS_PIN_MODE_OUTPUT_LOW


/* PORT D */
#define PORT_u8PinChannel24_PIND0		PORT_STATUS_PIN_MODE_INPUT_FLOAT
#define PORT_u8PinChannel25_PIND1		PORT_STATUS_PIN_MODE_INPUT_FLOAT
#define PORT_u8PinChannel26_PIND2		PORT_STATUS_PIN_MODE_INPUT_PULL_UP // INT0
#define PORT_u8PinChannel27_PIND3		PORT_STATUS_PIN_MODE_INPUT_PULL_UP // INT1
#define PORT_u8PinChannel28_PIND4		PORT_STATUS_PIN_MODE_OUTPUT_LOW
#define PORT_u8PinChannel29_PIND5		PORT_STATUS_PIN_MODE_INPUT_PULL_UP
#define PORT_u8PinChannel30_PIND6		PORT_STATUS_PIN_MODE_INPUT_PULL_UP
#define PORT_u8PinChannel31_PIND7		PORT_STATUS_PIN_MODE_INPUT_PULL_UP





#endif /* MCAL_PORT_INCLUDE_PORT_CONFIG_H_ */
