/* 
 * File:   LCD_relay.c
 * Author: Ammar
 *
 * Created on 28 1 2022, 10:40 ?
 */


#include "ecu_lcd.h"

/* private functions declarations */
static Std_ReturnType Lcd_4bit_Set4BitsOnPins(const Lcd_4bitType* _lcd, uint8 _data_4bits);
static Std_ReturnType Lcd_4bit_SendEnableSignal(const Lcd_4bitType* _lcd);
static Std_ReturnType Lcd_4bit_SetCursor(const Lcd_4bitType* _lcd,uint8 _row, uint8 _col  );


static Std_ReturnType Lcd_8bit_SendEnableSignal(const Lcd_8bitType* _lcd);
static Std_ReturnType Lcd_8bit_SetCursor(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col );


/* Interfaces of 4bit mode */
Std_ReturnType Lcd_4bit_Init(const Lcd_4bitType* _lcd){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret  = Dio_InitChannel(&(_lcd->lcd_enable_pin));
        ret &= Dio_InitChannel(&(_lcd->lcd_rs_pin));
        ret &= Dio_InitChannel(&(_lcd->lcd_rw_pin));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[0]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[1]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[2]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[3]));
        
        __delay_ms(20);
        ret &= Lcd_4bit_SendCommand(_lcd,_LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
        __delay_ms(5);
       ret &= Lcd_4bit_SendCommand(_lcd,_LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
       __delay_us(150);
       ret &= Lcd_4bit_SendCommand(_lcd,_LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
       


       /*the next are optional */
       
       ret &= Lcd_4bit_SendCommand(_lcd,_LCD_CLEAR_COMMAND);
       ret &= Lcd_4bit_SendCommand(_lcd,_LCD_CURSOR_HOME);
       ret &= Lcd_4bit_SendCommand(_lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
       ret &= Lcd_4bit_SendCommand(_lcd,_LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF);
       ret &= Lcd_4bit_SendCommand(_lcd,_LCD_FUNCTION_SET_4_BIT_2_LINE_8_DOTS);
       ret &= Lcd_4bit_SendCommand(_lcd,0x80);
    }


    return ret;
}


Std_ReturnType Lcd_4bit_SendCommand(const Lcd_4bitType* _lcd, uint8 _command){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret  = Dio_WriteChannel(&(_lcd->lcd_rs_pin),DIO_LOW);
        ret &= Dio_WriteChannel(&(_lcd->lcd_rw_pin),DIO_LOW);
        
        ret &= Lcd_4bit_Set4BitsOnPins(_lcd,(_command>>4) &0xF);  // higher nibble first 
        ret &= Lcd_4bit_SendEnableSignal(_lcd);

        ret &= Lcd_4bit_Set4BitsOnPins(_lcd,_command);  // lower nibble 
        ret &= Lcd_4bit_SendEnableSignal(_lcd);
    }


    return ret;
}
Std_ReturnType Lcd_4bit_ReadCommand(const Lcd_4bitType* _lcd, uint8* _command){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  || NULL==_command){

        ret = E_NOT_OK;
    } 
     
     else{
        
    }


    return ret;
}



Std_ReturnType Lcd_4bit_SendChar(const Lcd_4bitType* _lcd, uint8 _data){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret  = Dio_WriteChannel(&(_lcd->lcd_rs_pin),DIO_HIGH);
        ret &= Dio_WriteChannel(&(_lcd->lcd_rw_pin),DIO_LOW);
        
        ret &= Lcd_4bit_Set4BitsOnPins(_lcd,(_data>>4) &0xF);  // higher nibble first 
        ret &= Lcd_4bit_SendEnableSignal(_lcd);

        ret &= Lcd_4bit_Set4BitsOnPins(_lcd,_data);  // lower nibble 
        ret &= Lcd_4bit_SendEnableSignal(_lcd);
    }


    return ret;
}

Std_ReturnType Lcd_4bit_ReadData(const Lcd_4bitType* _lcd, uint8* _data){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  || NULL==_data){

        ret = E_NOT_OK;
    } 
     
     else{
        
    }


    return ret;
}


Std_ReturnType Lcd_4bit_SendCharWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8 _data){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret &=Lcd_4bit_SetCursor(_lcd, _row, _col);
        ret &=Lcd_4bit_SendChar(_lcd,_data);
    }


    return ret;
}
Std_ReturnType Lcd_4bit_ReadDataWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _data){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  || NULL==_data){

        ret = E_NOT_OK;
    } 
     
     else{
        
    }


    return ret;
}

Std_ReturnType Lcd_4bit_SendString(const Lcd_4bitType* _lcd, uint8* _str){
    Std_ReturnType ret = E_OK;
    uint32 l_counter=ZERO_VALUE;

    if (NULL == _lcd  || NULL==_str){

        ret = E_NOT_OK;
    } 
     
     else{
        
        while(_str[l_counter] !=0){
            ret &= Lcd_4bit_SendChar(_lcd,_str[l_counter]);
            l_counter++;
        }
    }


    return ret;
}
Std_ReturnType Lcd_4bit_SendStringWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _str){
    Std_ReturnType ret = E_OK;
    uint32 l_counter=ZERO_VALUE;

    if (NULL == _lcd  || NULL==_str){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret &=Lcd_4bit_SetCursor(_lcd,_row,_col);
        while(_str[l_counter] !=0){
            ret &= Lcd_4bit_SendChar(_lcd,_str[l_counter]);
            l_counter++;
        }
    }


    return ret;
}


Std_ReturnType Lcd_4bit_SendStringWithPositionWithShiftLeftAndRight(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _str, uint8 _shift_times){
     Std_ReturnType ret = E_OK;
     uint8 l_counter=ZERO_VALUE;
     uint8 l_sizeof =ZERO_VALUE;
     uint8 l_new_col;
     
    if (NULL == _lcd  || NULL==_str){

        ret = E_NOT_OK;
    } 
     
     else{
        ret &= Lcd_4bit_SendStringWithPosition(_lcd,_row,_col,_str);
        while(_str[l_counter] !=0){
            l_counter++;
            l_sizeof++;
        }
        
        for(l_counter=1;l_counter<=_shift_times;l_counter++){
            
            l_new_col = l_counter+_col;
            
             ret &= Lcd_4bit_SendStringWithPosition(_lcd,_row,l_new_col,_str);
             ret &= Lcd_4bit_SendCharWithPosition(_lcd,_row,l_new_col-1,' ');
            __delay_ms(150);
        }
        
        while(_shift_times--){
            
            l_new_col --;
            
             ret &= Lcd_4bit_SendStringWithPosition(_lcd,_row,l_new_col,_str);
             ret &= Lcd_4bit_SendCharWithPosition(_lcd,_row,l_sizeof+l_new_col,' ');
            __delay_ms(150);
        }
        
    }


    return ret;
}

Std_ReturnType Lcd_4bit_CreateCustomChar(const Lcd_4bitType* _lcd, uint8* _str, uint8 _memory_pos){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = ZERO_VALUE;
     
    if (NULL == _lcd  || NULL==_str){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret &= Lcd_4bit_SendCommand(_lcd,(_LCD_CGRAM_START+(_memory_pos*8)));
        for(l_counter = ZERO_VALUE;l_counter<8;l_counter++){
            Lcd_4bit_SendChar(_lcd, _str[l_counter]);
        }
        
    }


    return ret;
}

Std_ReturnType Lcd_4bit_SendCustomCharWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col,  uint8 _memory_pos){
    Std_ReturnType ret = E_OK;

    if (NULL == _lcd ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret &= Lcd_4bit_SendCommand(_lcd,_LCD_CGRAM_START);
        ret &= Lcd_4bit_SendCharWithPosition(_lcd, _row, _col,_memory_pos);
    }


    return ret;
    
}

Std_ReturnType Lcd_4bit_BlinkStringWithPosition(const Lcd_4bitType* _lcd, uint8 _row, uint8 _col, uint8* _str, uint8 _blink_times){
    Std_ReturnType ret = E_OK;
    uint8 l_counter=ZERO_VALUE;
    
    uint8 spaces[100];
    
    
    if (NULL == _lcd  || NULL==_str){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret &= Lcd_4bit_SendStringWithPosition(_lcd,_row,_col,_str);
        while(_str[l_counter] !=0){
            spaces[l_counter]=' ';
            l_counter++;
        }
        
         spaces[l_counter]='\0';
        for(l_counter=1;l_counter<=_blink_times;l_counter++){
            
            __delay_ms(80);
            ret &= Lcd_4bit_SendStringWithPosition(_lcd,_row,_col,spaces);
            __delay_ms(80);
             ret &= Lcd_4bit_SendStringWithPosition(_lcd,_row,_col,_str);
            
            
        }
      }
    


    return ret;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Interface of 8bit mode*/
Std_ReturnType Lcd_8bit_Init(const Lcd_8bitType* _lcd){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret  = Dio_InitChannel(&(_lcd->lcd_enable_pin));
        ret &= Dio_InitChannel(&(_lcd->lcd_rs_pin));
        ret &= Dio_InitChannel(&(_lcd->lcd_rw_pin));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[0]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[1]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[2]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[3]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[4]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[5]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[6]));
        ret &= Dio_InitChannel(&(_lcd->lcd_data_pins[7]));
        
        __delay_ms(16);
        ret &= Lcd_8bit_SendCommand(_lcd,_LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
        __delay_ms(5);
       ret &= Lcd_8bit_SendCommand(_lcd,_LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
       __delay_us(101);
       ret &= Lcd_8bit_SendCommand(_lcd,_LCD_FUNCTION_SET_8_BIT_2_LINE_8_DOTS);
       
       /*the next are optional */
       ret &= Lcd_8bit_SendCommand(_lcd,_LCD_CLEAR_COMMAND);
       ret &= Lcd_8bit_SendCommand(_lcd,_LCD_CURSOR_HOME);
       ret &= Lcd_8bit_SendCommand(_lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
       ret &= Lcd_8bit_SendCommand(_lcd,_LCD_DISPLAY_ON_UNDER_LINE_CURSOR_OFF_BLOCK_CURSOR_OFF);
       
       

       
    }


    return ret;
}

Std_ReturnType Lcd_8bit_SendCommand(const Lcd_8bitType* _lcd, uint8 _command){
    
    Std_ReturnType ret = E_OK;
    uint8 l_counter =ZERO_VALUE;

    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret  = Dio_WriteChannel(&(_lcd->lcd_rs_pin),DIO_LOW);
        ret &= Dio_WriteChannel(&(_lcd->lcd_rw_pin),DIO_LOW);
        
        for(l_counter =ZERO_VALUE;l_counter<8;l_counter++){
            
            ret &=Dio_WriteChannel(&(_lcd->lcd_data_pins[l_counter]),(_command>>l_counter)&0x01);
        }
        
         ret &=Lcd_8bit_SendEnableSignal(_lcd);

    }



    return ret;
}

Std_ReturnType Lcd_8bit_ReadCommand(const Lcd_8bitType* _lcd, uint8* _command){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ||  NULL == _command){

        ret = E_NOT_OK;
    } 
     
     else{
        
    }


    return ret;
}

Std_ReturnType Lcd_8bit_SendChar(const Lcd_8bitType* _lcd, uint8 _data){
    Std_ReturnType ret = E_OK;
    uint8 l_counter =ZERO_VALUE;


    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret  = Dio_WriteChannel(&(_lcd->lcd_rs_pin),DIO_HIGH);
        ret &= Dio_WriteChannel(&(_lcd->lcd_rw_pin),DIO_LOW);
        
        for(l_counter =ZERO_VALUE;l_counter<8;l_counter++){
            
            ret &=Dio_WriteChannel(&(_lcd->lcd_data_pins[l_counter]),(_data>>l_counter)&0x01);
        }
        
        ret &=Lcd_8bit_SendEnableSignal(_lcd);


    }



    return ret;
}

Std_ReturnType Lcd_8bit_ReadChar(const Lcd_8bitType* _lcd, uint8* _data){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ||  NULL == _data){

        ret = E_NOT_OK;
    } 
     
     else{
        
    }


    return ret;
}

Std_ReturnType Lcd_8bit_SendCharWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8 _data){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret &= Lcd_8bit_SetCursor( _lcd,_row, _col);
        ret &= Lcd_8bit_SendChar(_lcd,_data);
    }


    return ret;
}

Std_ReturnType Lcd_8bit_ReadCharWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8* _data){
    Std_ReturnType ret = E_OK;
    

    if (NULL == _lcd  ||  NULL== _data){

        ret = E_NOT_OK;
    } 
     
     else{
        
    }


    return ret;
}

Std_ReturnType Lcd_8bit_SendString(const Lcd_8bitType* _lcd, uint8* _str){
    Std_ReturnType ret = E_OK;
    uint32 l_counter=ZERO_VALUE;

    if (NULL == _lcd || NULL==_str ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        while(_str[l_counter] != 0){
            ret &= Lcd_8bit_SendChar(_lcd,_str[l_counter]);
            l_counter++;
        }
        
        
    }


    return ret;
}
Std_ReturnType Lcd_8bit_SendStringWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8* _str){
    Std_ReturnType ret = E_OK;
    uint32 l_counter=ZERO_VALUE;

    if (NULL == _lcd || NULL==_str ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret &= Lcd_8bit_SetCursor( _lcd,_row, _col);
        while(_str[l_counter] != 0){
            ret &= Lcd_8bit_SendChar(_lcd,_str[l_counter]);
            l_counter++;
        }
    }


    return ret;
}

/* https://maxpromer.github.io/LCD-Character-Creator/ */
/**
 * 

 * @brief : _memory_pos : 0 to 7 
 * @return 
 */


Std_ReturnType Lcd_8bit_CreateCustomChar(const Lcd_8bitType* _lcd, uint8* _str, uint8 _memory_pos){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = ZERO_VALUE;
     
    if (NULL == _lcd  || NULL==_str){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret &= Lcd_8bit_SendCommand(_lcd,(_LCD_CGRAM_START+(_memory_pos*8)));
        
        for(l_counter = ZERO_VALUE;l_counter<8;l_counter++){
            Lcd_8bit_SendChar(_lcd, _str[l_counter]);
        }
        
        
    }


    return ret;
}

Std_ReturnType Lcd_8bit_SendCustomCharWithPosition(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col,  uint8 _memory_pos){
    Std_ReturnType ret = E_OK;

    if (NULL == _lcd ){

        ret = E_NOT_OK;
    } 
     
     else{
        ret &= Lcd_8bit_SendCommand(_lcd,_LCD_CGRAM_START);
        ret &= Lcd_8bit_SendCharWithPosition(_lcd, _row, _col,_memory_pos);
    }


    return ret;
    
}

Std_ReturnType Lcd_8bit_SendStringWithPositionWithShiftLeftAndRight(const Lcd_8bitType* _lcd, uint8 _row, uint8 _col, uint8* _str, uint8 _shift_times){
     Std_ReturnType ret = E_OK;
     uint8 l_counter=ZERO_VALUE;
     uint8 l_sizeof =ZERO_VALUE;
     uint8 l_new_col;
     
    if (NULL == _lcd  || NULL==_str){

        ret = E_NOT_OK;
    } 
     
     else{
        ret &= Lcd_8bit_SendStringWithPosition(_lcd,_row,_col,_str);
        while(_str[l_counter] !=0){
            l_counter++;
            l_sizeof++;
        }
        
        for(l_counter=1;l_counter<=_shift_times;l_counter++){
            
            l_new_col = l_counter+_col;
            
             ret &= Lcd_8bit_SendStringWithPosition(_lcd,_row,l_new_col,_str);
             ret &= Lcd_8bit_SendCharWithPosition(_lcd,_row,l_new_col-1,' ');
            __delay_ms(150);
        }
        
        while(_shift_times--){
            
            l_new_col --;
            
             ret &= Lcd_8bit_SendStringWithPosition(_lcd,_row,l_new_col,_str);
             ret &= Lcd_8bit_SendCharWithPosition(_lcd,_row,l_sizeof+l_new_col,' ');
            __delay_ms(150);
        }
        
    }


    return ret;
}


/***************************************** Helper Functions **************************************************/
Std_ReturnType Convert_IntToString (uint32 _number, uint8* _str){
    Std_ReturnType ret = E_OK;
    uint8 l_idx = 0;

    if ( NULL==_str ){

        ret = E_NOT_OK;
    } 
     
     else{
//        while(_number !=0){
//
//            
//            _str[l_idx]=(_number%10)+'0';
//            l_idx++;
//            _number/=10;
//        }
//        
//        _str[l_idx]='\0';
        
        sprintf(_str, "%lu", _number);
    }


    return ret;
}

Std_ReturnType Convert_FloatToString (float32 _number, uint8* _str){
    Std_ReturnType ret = E_OK;

    if ( NULL==_str ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        sprintf(_str, "%f", _number);
    }


    return ret;
}


static Std_ReturnType Lcd_4bit_Set4BitsOnPins(const Lcd_4bitType* _lcd, uint8 _data_4bits){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = ZERO_VALUE;

    if ( NULL==_lcd ){

        ret = E_NOT_OK;
    } 
     
     else{
        for(l_counter =ZERO; l_counter<4;l_counter++){
            
            ret &=Dio_WriteChannel(&(_lcd->lcd_data_pins[l_counter]),(_data_4bits>>l_counter)&0x01);
        }
    }


    return ret;
}

static Std_ReturnType Lcd_4bit_SendEnableSignal(const Lcd_4bitType* _lcd){
    Std_ReturnType ret = E_OK;

    if ( NULL==_lcd ){

        ret = E_NOT_OK;
    } 
     
     else{
           
        ret = Dio_WriteChannel(&(_lcd->lcd_enable_pin), DIO_HIGH);
        __delay_us(5);
        ret = Dio_WriteChannel(&(_lcd->lcd_enable_pin), DIO_LOW);
        
    }


    return ret;
}

static Std_ReturnType Lcd_8bit_SendEnableSignal(const Lcd_8bitType* _lcd){
    Std_ReturnType ret = E_OK;

    if ( NULL==_lcd ){

        ret = E_NOT_OK;
    } 
     
     else{
           
        ret = Dio_WriteChannel(&(_lcd->lcd_enable_pin), DIO_HIGH);
        __delay_us(5);
        ret = Dio_WriteChannel(&(_lcd->lcd_enable_pin), DIO_LOW);
        
    }


    return ret;
}

static Std_ReturnType Lcd_8bit_SetCursor(const Lcd_8bitType* _lcd,uint8 _row, uint8 _col  ){
    Std_ReturnType ret = E_OK;

    if ( NULL==_lcd ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        /* decrement col because use it as row1 col 1 which means col 0*/
        _col--;
           
        switch(_row){
            
            case LCD_ROW1:
                ret &= Lcd_8bit_SendCommand(_lcd,(0x80+_col));
                break;
                
            case LCD_ROW2:
                ret &= Lcd_8bit_SendCommand(_lcd,(0xc0+_col));
                break;
                
            case LCD_ROW3: 
                ret &= Lcd_8bit_SendCommand(_lcd,(0x94+_col));
                break;
                
            case LCD_ROW4:
                ret &= Lcd_8bit_SendCommand(_lcd,(0xd4+_col));
                break;
                
            default :
                ret = E_NOT_OK;
        }
    }


    return ret;
}

static Std_ReturnType Lcd_4bit_SetCursor(const Lcd_4bitType* _lcd,uint8 _row, uint8 _col  ){
    Std_ReturnType ret = E_OK;

    if ( NULL==_lcd ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        /* decrement col because use it as row1 col 1 which means col 0*/
        _col--;
           
        switch(_row){
            
            case LCD_ROW1:
                ret &= Lcd_4bit_SendCommand(_lcd,(0x80+_col));
                break;
                
            case LCD_ROW2:
                ret &= Lcd_4bit_SendCommand(_lcd,(0xc0+_col));
                break;
                
            case LCD_ROW3: 
                ret &= Lcd_4bit_SendCommand(_lcd,(0x94+_col));
                break;
                
            case LCD_ROW4:
                ret &= Lcd_4bit_SendCommand(_lcd,(0xd4+_col));
                break;
                
            default :
                ret = E_NOT_OK;
        }
    }


    return ret;
    
}

