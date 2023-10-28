 #include "mcal_initialize.h"


//Ioc_ConfigPinType ioc_obj0 ={
//   
//   .number = IOC_KBI0,
//  .priority = INTERRUPT_HIGH_PRIOIRTY,
//  .pin.direction= DIO_DIRECTION_INPUT,
//  .pin.pin = DIO_PIN4,
//  .pin.port = DIO_PORTB_INDEX,
//          
//};


void Mcal_Init(void){
    
    Std_ReturnType ret;
    Pin_SelectAnalogOrDigitalMode(PIN_CONFIG_ALL_DIGITAL);
//    ret= Ioc_Init(&ioc_obj0);

    
   
}

