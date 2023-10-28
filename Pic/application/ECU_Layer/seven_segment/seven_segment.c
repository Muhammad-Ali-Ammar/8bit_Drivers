



#include "ecu_seven_segment.h"

static uint8 seven_segment_cathod_arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};



Std_ReturnType  Seven_Segment_InitNormalConnection(const Seven_Segment_NormalType* _seven_segment){

    Std_ReturnType ret = E_OK;
    

    if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret =  Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_A_IDX]));
        ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_B_IDX]));
        ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_C_IDX]));
        ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_D_IDX]));
        ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_E_IDX]));
        ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_F_IDX]));
        ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_G_IDX]));
        
        if(SEVEN_SEGMENT_DP_ON ==_seven_segment->seven_segment_dp_is_used){
            ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_DP_IDX]));
        }
        
        else{
            /* do nothing*/
        }
        
        if(SEVEN_SEGMENT_OFF == _seven_segment->seven_segment_state){
            ret &= Seven_Segment_TurnOffNormalConnection(_seven_segment);
            ret &= Seven_Segment_TurnOffDecimalPointNormalConnection(_seven_segment);
        }
        
        else {
            /* do nothing*/
        }
        
        
    }


    return ret;
}


Std_ReturnType  Seven_Segment_WriteNormalConnection(const Seven_Segment_NormalType* _seven_segment, uint8 _value){
    
    Std_ReturnType ret = E_OK;
    Dio_LogicPinType final_bit = DIO_LOW;
    
    Seven_Segment_ConnectionType flag = _seven_segment->seven_segment_connection;
    uint8 real_value = seven_segment_cathod_arr[_value];
    
    
    int idx = 0;

    if (NULL == _seven_segment  || _value>9){

        ret = E_NOT_OK;
    } 
    
    else{
        real_value = flag*real_value + (!flag)*(~real_value);
        for(idx=0;idx<8;idx++){
            final_bit = (real_value>>idx)& (DIO_BIT0_MASK);
            ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[idx]), final_bit );
        }
    }
    
    return ret;

    
}

Std_ReturnType  Seven_Segment_TurnOffNormalConnection(const Seven_Segment_NormalType* _seven_segment){
    
    Std_ReturnType ret = E_OK;
    
    Dio_LogicPinType final_bit = DIO_LOW;
    Seven_Segment_ConnectionType flag = _seven_segment->seven_segment_connection;
    uint8 real_value = SEVEN_SEGMENT_TURN_OFF_VALUE_CATHOD;
    
    
    int idx = 0;
    
     if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
    
     else {
         
        real_value = flag*real_value + (!flag)*(~real_value);
        for(idx=0;idx<8;idx++){
            final_bit = (real_value>>idx)& (DIO_BIT0_MASK);
            ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[idx]), final_bit );
        }
         
        ret &= Seven_Segment_TurnOffDecimalPointNormalConnection(_seven_segment);
     }
    return ret;
}

Std_ReturnType  Seven_Segment_TurnOffDecimalPointNormalConnection(const Seven_Segment_NormalType* _seven_segment){
    
    Std_ReturnType ret = E_OK;
    
    Dio_LogicPinType final_bit = (_seven_segment->seven_segment_connection)== SEVEN_SEGMENT_COMMON_ANODE ;
    

    if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
    
     else {
        
        if(SEVEN_SEGMENT_DP_ON == _seven_segment->seven_segment_dp_is_used){
        
                ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_DP_IDX]), final_bit );
            
        }
        
        else {
            /* do nothing*/
        }
     }
    
    return ret;
    
}
Std_ReturnType  Seven_Segment_TurnOnDecimalPointNormalConnection(const Seven_Segment_NormalType* _seven_segment){
    
    Std_ReturnType ret = E_OK;
    
    Dio_LogicPinType final_bit = (_seven_segment->seven_segment_connection)== SEVEN_SEGMENT_COMMON_CATHOD ;
    

    if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
    
     else {
        
        if(SEVEN_SEGMENT_DP_ON == _seven_segment->seven_segment_dp_is_used){
        
                ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_NORMAL_DP_IDX]), final_bit );
            
        }
        
        else {
            /* do nothing*/
        }
     }
    
    return ret;
    
}



/****************************************** for BCB seven segment *************************************************/


Std_ReturnType  Seven_Segment_InitBCDConnection(const Seven_Segment_BCDType* _seven_segment){
    
    Std_ReturnType ret = E_OK;
    

    if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
        ret =  Dio_InitChannelDirection(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_BCD_A_IDX]));
        ret &= Dio_InitChannelDirection(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_BCD_B_IDX]));
        ret &= Dio_InitChannelDirection(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_BCD_C_IDX]));
        ret &= Dio_InitChannelDirection(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_BCD_D_IDX]));

        
        if(SEVEN_SEGMENT_DP_ON ==_seven_segment->seven_segment_dp_is_used){
            ret &= Dio_InitChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_BCD_DP_IDX]));
        }
        
        else{
            /* do nothing*/
        }
        
        if(SEVEN_SEGMENT_OFF == _seven_segment->seven_segment_state){
            ret &= Seven_Segment_TurnOffBCDConnection(_seven_segment);
            ret &= Seven_Segment_TurnOffDecimalPointBCDConnection(_seven_segment);
        }
        
        else {
            /* do nothing*/
        }
        
        
    }


    return ret;
}


Std_ReturnType  Seven_Segment_WriteBCDConnection(const Seven_Segment_BCDType* _seven_segment, uint8 _value){
    
    Std_ReturnType ret = E_OK;
    Dio_LogicPinType final_bit = DIO_LOW;
    
    int idx = 0;

    if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
    
    else{

        for(idx=0;idx<4;idx++){
            final_bit = (_value>>idx)& (DIO_BIT0_MASK);
            ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[idx]), final_bit );
        }
    }
    
    return ret;
}

Std_ReturnType  Seven_Segment_TurnOffBCDConnection(const Seven_Segment_BCDType* _seven_segment){
    
    Std_ReturnType ret = E_OK;
    
    Dio_LogicPinType final_bit = DIO_LOW;
    uint8 real_value = 0xff;
    
    
    int idx = 0;
    
     if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
    
     else {
         
        for(idx=0;idx<4;idx++){
            final_bit = (real_value>>idx)& (DIO_BIT0_MASK);
            ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[idx]), final_bit );
        }
         
        ret &= Seven_Segment_TurnOffDecimalPointBCDConnection(_seven_segment);
     }
    return ret;
}


Std_ReturnType  Seven_Segment_TurnOnDecimalPointBCDConnection(const Seven_Segment_BCDType* _seven_segment){
    
    Std_ReturnType ret = E_OK;
    
    Dio_LogicPinType final_bit = (_seven_segment->seven_segment_connection)== SEVEN_SEGMENT_COMMON_CATHOD ;
    

    if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
    
     else {
        
        if(SEVEN_SEGMENT_DP_ON == _seven_segment->seven_segment_dp_is_used){
        
                ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_BCD_DP_IDX]), final_bit );
            
        }
        
        else {
            /* do nothing*/
        }
     }
    
    return ret;
    
}

Std_ReturnType  Seven_Segment_TurnOffDecimalPointBCDConnection(const Seven_Segment_BCDType* _seven_segment){
    
    Std_ReturnType ret = E_OK;
    
    Dio_LogicPinType final_bit = (_seven_segment->seven_segment_connection)== SEVEN_SEGMENT_COMMON_ANODE ;
    

    if (NULL == _seven_segment  ){

        ret = E_NOT_OK;
    } 
    
     else {
        
        if(SEVEN_SEGMENT_DP_ON == _seven_segment->seven_segment_dp_is_used){
        
                ret &= Dio_WriteChannel(&(_seven_segment->seven_segment_pins[SEVEN_SEGMENT_BCD_DP_IDX]), final_bit );
            
        }
        
        else {
            /* do nothing*/
        }
     }
    
    return ret;
    
}


