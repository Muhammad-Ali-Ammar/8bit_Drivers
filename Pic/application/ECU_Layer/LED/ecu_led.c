/* 
 * File:   ecu_led.c
 * Author: Ammar
 *
 * Created on 24 ??????, 2022, 01:29 ?
 */



#include "ecu_led.h"


/**
 * @brief initialize the pin to output and turn it off
 * @param led
 * @return status of the function 
 *      (E_OK) : 
 *      (E_NOT_OK) : 
 */
Std_ReturnType Led_Init(const Led_ConfigType* _led){
    
     Std_ReturnType ret = E_OK;
    

    if (NULL == _led  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
       ret= Dio_InitChannelDirection(&(_led->led_pin) );
       
       switch(_led->led_connection)
       {
           case LED_SOURCE_CURRENT : 
               ret &= Dio_WriteChannel(&(_led->led_pin), (Dio_LogicPinType)_led->led_status);
               break;
               
           case LED_SINK_CURRENT : 
               ret &= Dio_WriteChannel(&(_led->led_pin), (Dio_LogicPinType)_led->led_status); 
               ret &= Dio_ToggleChannel(&(_led->led_pin));
               break;
               
               
           default : 
               
               ret = E_NOT_OK;
               
       }
    }


    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType Led_TurnOff(const Led_ConfigType* _led){
 
     Std_ReturnType ret = E_OK;
    

    if (NULL == _led  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
            switch(_led->led_connection)
                {
                    case LED_SOURCE_CURRENT : 
                        ret = Dio_WriteChannel(&(_led->led_pin), DIO_LOW);
                        break;

                    case LED_SINK_CURRENT : 
                        ret = Dio_WriteChannel(&(_led->led_pin), DIO_HIGH); 
                        break;


                    default : 

                        ret = E_NOT_OK;

                }
        }


    return ret;
}



/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType Led_TurnOn(const Led_ConfigType* _led){

     Std_ReturnType ret = E_OK;
    

    if (NULL == _led  ){

        ret = E_NOT_OK;
    } 
     
     else{
        
            switch(_led->led_connection)
                {
                    case LED_SOURCE_CURRENT : 
                        ret = Dio_WriteChannel(&(_led->led_pin), DIO_HIGH);
                        break;

                    case LED_SINK_CURRENT : 
                        ret = Dio_WriteChannel(&(_led->led_pin), DIO_LOW); 
                        break;


                    default : 
                        ret = E_NOT_OK;

                }
        }


    return ret;
  
}
/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType Led_Toggle(const Led_ConfigType* _led){
     Std_ReturnType ret = E_OK;
    

    if (NULL == _led  ){

        ret = E_NOT_OK;
    } 
     
          else{
        
            ret = Dio_ToggleChannel(&(_led->led_pin));
        }

    return ret;
}
