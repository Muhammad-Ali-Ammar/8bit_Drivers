/**************************************************************************/
/* Filename						: LCD.h                                   */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 21 Oct 2023  	           	 	      	  */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef HAL_INCLUDE_LCD_H_
#define HAL_INCLUDE_LCD_H_


/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define LCD_CLEAR_COMMAND                                                               0x01
#define LCD_CURSOR_HOME                                                                 0x02

#define LCD_ENTRY_MODE_INC_SHIFT_ON                                                     0x07
#define LCD_ENTRY_MODE_INC_SHIFT_OFF                                                    0x06
#define LCD_ENTRY_MODE_DEC_SHIFT_ON                                                     0x05
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF                                                    0x04

#define LCD_DISPLAY_OFF                                                                 0x08
#define LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF                           0x0C
#define LCD_DISPLAY_ON_UNDER_LINE_CURSOR_ON_BLOCK_CURSOR_OFF                            0x0E
#define LCD_DISPLAY_ON_UNDER_LINE_CURSOR_ON_BLOCK_CURSOR_ON                             0x0F
#define LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_ON                            0x0D

#define LCD_MOVE_CURSOR_LEFT                                                            0x10
#define LCD_MOVE_CURSOR_RIGHT                                                           0x14
#define LCD_SHIFT_DISPLAY_LEFT                                                          0x18
#define LCD_SHIFT_DISPLAY_RIGHT                                                         0x1C


#define LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS                                            0x38
#define LCD_FUNCTION_SET_4_BIT_2_LINE_8_DOTS                                            0x28
#define LCD_FUNCTION_SET_8_BIT_2_LINE_11_DOTS                                           0x3C
#define LCD_FUNCTION_SET_4_BIT_2_LINE_11_DOTS                                           0x2C

#define LCD_CGRAM_START                                                                 0x40
#define LCD_DDRAM_START                                                                 0x80

//////////////////////





#define LCD_ROW1    ((u8)1)
#define LCD_ROW2    ((u8)2)
#define LCD_ROW3    ((u8)3)
#define LCD_ROW4    ((u8)4)


#define LCD_COL1	((u8)1)
#define LCD_COL2	((u8)2)
#define LCD_COL3	((u8)3)
#define LCD_COL4	((u8)4)
#define LCD_COL5	((u8)5)
#define LCD_COL6	((u8)6)
#define LCD_COL7	((u8)7)
#define LCD_COL8	((u8)8)
#define LCD_COL9	((u8)9)
#define LCD_COL10	((u8)10)
#define LCD_COL11	((u8)11)
#define LCD_COL12	((u8)12)
#define LCD_COL13	((u8)13)
#define LCD_COL14	((u8)14)
#define LCD_COL15	((u8)15)
#define LCD_COL16	((u8)16)
#define LCD_COL17	((u8)17)
#define LCD_COL18	((u8)18)
#define LCD_COL19	((u8)19)
#define LCD_COL20	((u8)20)


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
typedef struct {

	 u8            lcd_data_pins[4];
     u8            lcd_rs_pin;
     u8            lcd_enable_pin;
     u8            lcd_rw_pin;


}Lcd_4bitType;


typedef struct {
     u8            lcd_data_pins[8];
     u8            lcd_rs_pin;
     u8            lcd_enable_pin;
}Lcd_8bitType;


typedef enum{
	LCD_STATUS_OK,
	LCD_STATUS_FAIL,
	LCD_STATUS_NULL_POINTER_ADDRESS,
	LCD_STATUS_WRONG_CUSTOM_CHAR_INDEX,
	LCD_STATUS_WRONG_COL_INDEX,
	LCD_STATUS_WRONG_ROW_INDEX
}Lcd_ErrorStatusType;



/********************************** Software Interfaces Declarations *******************/

Lcd_ErrorStatusType Lcd_4bit_enuInit(const Lcd_4bitType* Address_lcd);
Lcd_ErrorStatusType Lcd_4bit_enuSendCommand(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Command);
Lcd_ErrorStatusType Lcd_4bit_enuDisplayCharacter(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Data);
Lcd_ErrorStatusType Lcd_4bit_enuDisplayCharacterWithPosition(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Data, u8 Copy_u8Row, u8 Copy_u8Col);
Lcd_ErrorStatusType Lcd_4bit_enuCreateCustomCharacter(const Lcd_4bitType* Address_Lcd, pu8 Address_pu8CustomCharacter, u8 Copy_u8MemoryIndex);
Lcd_ErrorStatusType Lcd_4bit_enuGoToXY(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Row, u8 Copy_u8Col);
Lcd_ErrorStatusType Lcd_4bit_enuDisplayString(const Lcd_4bitType* Address_Lcd, pu8 Address_pu8String);
Lcd_ErrorStatusType Lcd_4bit_enuDisplayNumber(const Lcd_4bitType* Address_Lcd, u8 Copy_u8Number);


Lcd_ErrorStatusType Lcd_8bit_enuInit(const Lcd_8bitType* Address_Lcd);
Lcd_ErrorStatusType Lcd_8bit_enuSendCommand(const Lcd_8bitType* Address_Lcd, u8 Copy_u8Command);
Lcd_ErrorStatusType Lcd_8bit_enuDisplayCharacter(const Lcd_8bitType* Address_Lcd, u8 Copy_u8Data);
Lcd_ErrorStatusType Lcd_8bit_enuCreateCustomCharacter(const Lcd_8bitType* Address_Lcd, pu8 Address_pu8CustomCharacter, u8 Copy_u8MemoryIndex);
Lcd_ErrorStatusType Lcd_8bit_enuGoToXY(const Lcd_8bitType* Address_Lcd, u8 Copy_u8Row, u8 Copy_u8Col);
Lcd_ErrorStatusType Lcd_8bit_enuDisplayString(const Lcd_8bitType* Address_Lcd, pu8 Address_pu8String);
Lcd_ErrorStatusType Lcd_8bit_enuDisplayNumber(const Lcd_8bitType* Address_Lcd, u8 Copy_u8Number);



#endif /* HAL_INCLUDE_LCD_H_ */
