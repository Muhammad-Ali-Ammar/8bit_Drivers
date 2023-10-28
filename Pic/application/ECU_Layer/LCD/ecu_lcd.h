/* 
 * File:   ecu_lcd.h
 * Author: isammar93
 *
 * Created on 08 ??????, 2023, 10:40 ?
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H


/********************************** Includes *****************************************/
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_lcd_cfg.h"

/********************************** Macros Declarations *******************************/

/************************ Commands ***************************************/
#define _LCD_CLEAR_COMMAND                                                               0x01
#define _LCD_CURSOR_HOME                                                                 0x02 

#define _LCD_ENTRY_MODE_INC_SHIFT_ON                                                     0x07
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF                                                    0x06
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON                                                     0x05
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF                                                    0x04

#define _LCD_DISPLAY_OFF                                                                 0x08
#define _LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF                           0x0C
#define _LCD_DISPLAY_ON_UNDER_LINE_CURSOR_ON_BLOCK_CURSOR_OFF                            0x0E
#define _LCD_DISPLAY_ON_UNDER_LINE_CURSOR_ON_BLOCK_CURSOR_ON                             0x0F
#define _LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_ON                            0x0D

#define _LCD_MOVE_CURSOR_LEFT                                                            0x10
#define _LCD_MOVE_CURSOR_RIGHT                                                           0x14
#define _LCD_SHIFT_DISPLAY_LEFT                                                          0x18
#define _LCD_SHIFT_DISPLAY_RIGHT                                                         0x1C


#define _LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS                                            0x38
#define _LCD_FUNCTION_SET_4_BIT_2_LINE_8_DOTS                                            0x28
#define _LCD_FUNCTION_SET_8_BIT_2_LINE_11_DOTS                                           0x3C
#define _LCD_FUNCTION_SET_4_BIT_2_LINE_11_DOTS                                           0x2C

#define _LCD_CGRAM_START                                                                 0x40
#define _LCD_DDRAM_START                                                                 0x80

//////////////////////

#define LCD_ROW1    ((uint8)1)
#define LCD_ROW2    ((uint8)2)
#define LCD_ROW3    ((uint8)3)
#define LCD_ROW4    ((uint8)4)


/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/

typedef struct {
    
     Dio_PinConfigType            lcd_data_pins[4];
     Dio_PinConfigType            lcd_rs_pin;
     Dio_PinConfigType            lcd_enable_pin;
     Dio_PinConfigType            lcd_rw_pin;

     
}Lcd_4bitType;


typedef struct {
     Dio_PinConfigType            lcd_data_pins[8];
     Dio_PinConfigType            lcd_rs_pin;
     Dio_PinConfigType            lcd_enable_pin;
     Dio_PinConfigType            lcd_rw_pin;
}Lcd_8bitType;


/********************************** Software Interfaces Declarations *******************************/

/* Interfaces of 4bit mode */
Std_ReturnType Lcd_4bit_Init(const Lcd_4bitType* _lcd);
Std_ReturnType Lcd_4bit_SendCommand(const Lcd_4bitType* _lcd, uint8 _command);
Std_ReturnType Lcd_4bit_ReadCommand(const Lcd_4bitType* _lcd, uint8* _command);

Std_ReturnType Lcd_4bit_SendChar(const Lcd_4bitType* _lcd, uint8 _data);
Std_ReturnType Lcd_4bit_ReadChar(const Lcd_4bitType* _lcd, uint8* _data);

Std_ReturnType Lcd_4bit_SendCharWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8 _data);
Std_ReturnType Lcd_4bit_ReadCharWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _data);


Std_ReturnType Lcd_4bit_SendString(const Lcd_4bitType* _lcd, uint8* _str);
Std_ReturnType Lcd_4bit_SendStringWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _str);

Std_ReturnType Lcd_4bit_SendStringWithPositionWithShiftLeftAndRight(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _str, uint8 _shift_times);
Std_ReturnType Lcd_4bit_CreateCustomChar(const Lcd_4bitType* _lcd, uint8* _str, uint8 _memory_pos);
Std_ReturnType Lcd_4bit_SendCustomCharWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col,  uint8 _memory_pos);
Std_ReturnType Lcd_4bit_BlinkStringWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _str, uint8 _blink_times);

/* Interface of 8bit mode*/
Std_ReturnType Lcd_8bit_Init(const Lcd_8bitType* _lcd);
Std_ReturnType Lcd_8bit_SendCommand(const Lcd_8bitType* _lcd, uint8 _command);
Std_ReturnType Lcd_8bit_ReadCommand(const Lcd_8bitType* _lcd, uint8* _command);

Std_ReturnType Lcd_8bit_SendChar(const Lcd_8bitType* _lcd, uint8 _data);
Std_ReturnType Lcd_8bit_ReadChar(const Lcd_8bitType* _lcd, uint8* _data);

Std_ReturnType Lcd_8bit_SendCharWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8 _data);
Std_ReturnType Lcd_8bit_ReadCharWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8* _data);


Std_ReturnType Lcd_8bit_SendString(const Lcd_8bitType* _lcd, uint8* _str);
Std_ReturnType Lcd_8bit_SendStringWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8* _str);
Std_ReturnType Lcd_8bit_SendStringWithPositionWithShiftLeftAndRight(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8* _str, uint8 _shift_times);
Std_ReturnType Lcd_8bit_CreateCustomChar(const Lcd_8bitType* _lcd, uint8* _str, uint8 _memory_pos);
Std_ReturnType Lcd_8bit_SendCustomCharWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col,  uint8 _memory_pos);

/* Helper Functions */
 Std_ReturnType Convert_IntToString (uint32 _number, uint8* str);
 Std_ReturnType Convert_FloatToString (float32 _number, uint8* str);

#endif	/* ECU_LCD_H */

