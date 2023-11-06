/**************************************************************************/
/* Filename						: USART.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 28 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_USART_INCLUDE_USART_H_
#define MCAL_USART_INCLUDE_USART_H_

/********************************** Includes *********************************************/




/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{
	USART_CHARACTER_SIZE_5_BIT ,
	USART_CHARACTER_SIZE_6_BIT ,
	USART_CHARACTER_SIZE_7_BIT ,
	USART_CHARACTER_SIZE_8_BIT,
	USART_CHARACTER_SIZE_9_BIT = 7
}Usart_CharacterSizeType;


typedef enum{
	USAR_SELECT_ASYNCHRONOUS_MODE,
	USAR_SELET_SYNCHRONOUS_MODE

}Usart_SelectSyncModeType;


typedef enum{
	USART_SELECT_1STOP_BIT,
	USART_SELECT_2STOP_BIT
}Usart_SelectStopBitsType;


typedef enum{
	USART_SELECT_PARITY_DISABLE,
	USART_SELECT_PARITY_EVEN=2,
	USART_SELECT_PARITY_ODD=3
}Usart_SelectParityBitsType;


typedef enum{
	USART_STATUS_FAIL,
	USART_STATUS_OK,
	USART_STATUS_NULL_POINTER_ADDRESS,
}Usart_StatusErrorType;


typedef struct{

	Usart_CharacterSizeType character_size;
	Usart_SelectSyncModeType sync_mode;
	Usart_SelectStopBitsType stop_bits;
	Usart_SelectParityBitsType parity_bits;

	u32 						baude_rate;

}Usart_ConfigType;

/********************************** Software Interfaces Declarations *******************/


Usart_StatusErrorType Usart_enuInit(const Usart_ConfigType* Address_Usart);
Usart_StatusErrorType Usart_enuDeInit(const Usart_ConfigType* Address_Usart);


Usart_StatusErrorType Usart_enuEnableRxInterrupt(void);
Usart_StatusErrorType Usart_enuDisableRxInterrupt(void);
Usart_StatusErrorType Usart_enuSetCallbackRxFunction(void (*callback)(u16 Copy_u16Result));


Usart_StatusErrorType Usart_enuEnableTxInterrupt(void);
Usart_StatusErrorType Usart_enuDisableTxInterrupt(void);
Usart_StatusErrorType Usart_enuSetCallbackTxFunction(void (*callback)(void));


Usart_StatusErrorType Usart_enuEnableDataRegEmptyInterrupt(void);
Usart_StatusErrorType Usart_enuDisableDataRegEmptyInterrupt(void);
Usart_StatusErrorType Usart_enuSetCallbackDataRegEmptyFunction(void (*callback)(void));



Usart_StatusErrorType Usart_enuTransmitCharBlocking(const Usart_ConfigType* Address_Usart, u16 Copy_u8Data);
Usart_StatusErrorType Usart_enuTransmitStringBlocking(const Usart_ConfigType* Address_Usart, u8* Address_Data);

Usart_StatusErrorType Usart_enuReceiveBlocking(const Usart_ConfigType* Address_Usart, u16* Address_Data);





#endif /* MCAL_USART_INCLUDE_USART_H_ */
