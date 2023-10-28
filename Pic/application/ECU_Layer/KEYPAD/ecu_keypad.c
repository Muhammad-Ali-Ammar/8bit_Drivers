
#include "ecu_keypad.h"


static const uint8 Keypad_Matrix[KEYPAD_ROWS_NUMBER][KEYPAD_COLS_NUMBER]={
                                                {7,8,9,'/'},
                                                {4,5,6,'*'},
                                                {1,2,3,'-'},
                                                {'#',0,'=','+'}};





/*******************************************Static functions ************************************/

static Std_ReturnType Keypad_DisableControlPins(const Keypad_ConfigType* _keypad){
    
    Std_ReturnType ret = E_OK;
    uint8 l_counter = ZERO_VALUE;

    if (NULL == _keypad  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        switch(_keypad->keypad_control_pins){
            case KEYPAD_ROW_CONTROL:
                
                for(l_counter=ZERO_VALUE;l_counter<KEYPAD_ROWS_NUMBER;l_counter++){
                    ret &= Dio_WriteChannel(&(_keypad->keypad_rows_pins[l_counter]), (Dio_LogicPinType)_keypad->keypad_idle_volt);
                }
                
                break;
                
            case KEYPAD_COL_CONTROL :
                
                for(l_counter=ZERO_VALUE;l_counter<KEYPAD_COLS_NUMBER;l_counter++){
                    ret &= Dio_WriteChannel(&(_keypad->keypad_cols_pins[l_counter]), (Dio_LogicPinType)_keypad->keypad_idle_volt);
                }
                break;
                
            default : 
                ret = E_NOT_OK;
        }
        
    }


    return ret;
}

/******************************* public interfaces */
Std_ReturnType Keypad_Init(const Keypad_ConfigType* _keypad){
    
    Std_ReturnType ret = E_OK;
    uint8 l_counter = ZERO_VALUE;

    if (NULL == _keypad  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        for(l_counter=ZERO_VALUE;l_counter<KEYPAD_ROWS_NUMBER;l_counter++){
            
            ret&= Dio_InitChannel(&(_keypad->keypad_rows_pins[l_counter]));
        }
        
        for(l_counter=ZERO_VALUE;l_counter<KEYPAD_COLS_NUMBER;l_counter++){
            
            ret&= Dio_InitChannel(&(_keypad->keypad_cols_pins[l_counter]));
        }
        
        ret &= Keypad_DisableControlPins(_keypad);
        
    }


    return ret;
}
Std_ReturnType Keypad_Read(const Keypad_ConfigType* _keypad, uint8 * _value){
    
    Std_ReturnType ret = E_OK;
    uint8 l_rows = ZERO_VALUE;
    uint8 l_cols = ZERO_VALUE;
    Dio_LogicPinType l_check;
    if (NULL == _keypad || (NULL == _value ) ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret = Keypad_DisableControlPins(_keypad);

        switch(_keypad->keypad_control_pins){
            case KEYPAD_ROW_CONTROL:
                
                /* first thing : active row */
                for(l_rows=ZERO_VALUE;l_rows<KEYPAD_ROWS_NUMBER;l_rows++){
                    ret &= Dio_WriteChannel(&(_keypad->keypad_rows_pins[l_rows]), (Dio_LogicPinType) !(_keypad->keypad_idle_volt ) );
                    
                    /* second thing : read col */
                    for(l_cols= ZERO_VALUE;l_cols<KEYPAD_COLS_NUMBER;l_cols++){
                        ret &= Dio_ReadChannel(&(_keypad->keypad_cols_pins[l_cols]), &l_check);
                        
                        if( l_check != _keypad->keypad_idle_volt )
                        {
                             *_value = Keypad_Matrix[l_rows][l_cols];
                        }
                        else {
                            /* nothing*/
                        }
                    }
                    
                    
                    
                     ret &= Dio_WriteChannel(&(_keypad->keypad_rows_pins[l_rows]), (Dio_LogicPinType) _keypad->keypad_idle_volt  );
                }
                
                break;
                
            case KEYPAD_COL_CONTROL :
                
                 /* first thing : active col */
                for(l_cols=ZERO_VALUE;l_cols<KEYPAD_COLS_NUMBER;l_cols++){
                    ret &= Dio_WriteChannel(&(_keypad->keypad_cols_pins[l_cols]), (Dio_LogicPinType) !(_keypad->keypad_idle_volt ) );
                    
                    /* second thing : read row */
                    for(l_rows= ZERO_VALUE;l_rows<KEYPAD_COLS_NUMBER;l_rows++){
                        ret &= Dio_ReadChannel(&(_keypad->keypad_rows_pins[l_rows]),&l_check );
                        
                        if(l_check != _keypad->keypad_idle_volt )
                        {
                            *_value = Keypad_Matrix[l_rows][l_cols];
                        }
                        else {
                            /* nothing*/
                        }
                    }
                    
                    
                    
                     ret &= Dio_WriteChannel(&(_keypad->keypad_cols_pins[l_cols]), (Dio_LogicPinType) _keypad->keypad_idle_volt  );
                }
                
                break;
                
            default : 
                ret = E_NOT_OK;
        }
        
        
    }

    return ret;
}
