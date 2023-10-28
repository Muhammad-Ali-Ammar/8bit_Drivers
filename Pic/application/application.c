/* 
 * File:   application.c
 * Author: Muhammad Ammar
 *
 * Created on 24 ??????, 2022, 01:29 ?
 */

#include "application.h"

 
uint8 received_data = 0;
void I2cReceiveSlaveMode_AppIsr(void);

 Led_ConfigType led1 ={.led_connection = LED_SOURCE_CURRENT,
                      .led_status = LED_OFF,
                      .led_pin.direction = DIO_DIRECTION_OUTPUT,
                      .led_pin.logic =DIO_LOW,
                      .led_pin.pin = DIO_PIN0,
                      .led_pin.port = DIO_PORTD_INDEX
};


 I2c_ConfigType i2c_obj = {
   .master_slave_config = I2C_MASTER_MODE,
   .master_mode_clock = 100000,
   .SMBus_config = I2C_SMBUS_DISABLE,
   .slew_rate = I2C_SLEW_RATE_DISABLE_CLK_100KHz,
   .I2cReceiveOverflow_InterruptHandler = NULL,
   .I2cWriteCollision_InterruptHandler = NULL,
   .I2c_InterruptHandler = NULL


 };
 
Rtc_Type rtc_obj1;

uint8 x =0;

int main() {
    
    Std_ReturnType ret= E_OK;
    
    Application_Init(); 
   
    ret = Led_Init(&led1);
    ret &= I2c_Init(&i2c_obj);
    
    

    while(1){
        
        ret &= Tc74_ReadTemp(&i2c_obj,TC74A7_ADDRESS,&x);
        __delay_ms(500);   
        
        
        
       
      }




    return (EXIT_SUCCESS);
}


void Application_Init(void){
    
    Std_ReturnType ret = E_OK;

    
    Mcal_Init();
    Ecu_Init();
    
  
}

void I2cReceiveSlaveMode_AppIsr(void){
    

        if (I2c_DoesMasterWantToReadFromMe_SalveMode() == 1){
            /* Slave Transmit, Send Data Here */
        }
        else { 

                received_data = SSPBUF;

        }
    
    
}
