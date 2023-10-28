/* 
 * File:   mcal_interrupt_manager.c
 * Author: Muhammad Ammar
 *
 * Created on 07 ????, 2023, 04:57 ?
 */


#include "mcal_interrupt_manager.h"


#if INTERRUPT_PRIOIRTY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

void __interrupt() ISR_High(void){
    
    #if INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    if(Int0_IsInterruptEnabled() == INTERRUPT_ENABLE && Int0_IsInterruptFired() == INTERRUPT_FIRED){
        INT0_ISR();
    }
    else {/* do nothing */}
    
    if(Int2_IsInterruptEnabled() == INTERRUPT_ENABLE && Int2_IsInterruptFired() == INTERRUPT_FIRED){
        INT2_ISR();
    }
    else {/* do nothing */}
    
    
    #endif

    
////////////////////////////////////////////////////////////////////////////////////////////////
    /* this is interrupt on change */
    #if INTERRUPT_IOC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        if(Ioc_IsInterruptEnabled() == INTERRUPT_ENABLE && Ioc_IsInterruptFired() == INTERRUPT_FIRED){
        IOC_ISR();
        
    }
    else {/* do nothing */}
//////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    
    
    #endif
}


void __interrupt(low_priority) ISR_Low(void){
    
    #if INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    if(Int1_IsInterruptEnabled() == INTERRUPT_ENABLE && Int1_IsInterruptFired() == INTERRUPT_FIRED){
        INT1_ISR();
    }
    else {/* do nothing */}
    
    #endif

}

#else 

void __interrupt() ISR(void){
    
    
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    #if INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    if(Int0_IsInterruptEnabled() == INTERRUPT_ENABLE && Int0_IsInterruptFired() == INTERRUPT_FIRED){
        INT0_ISR();
    }
    else {/* do nothing */}
    
    if(Int1_IsInterruptEnabled() == INTERRUPT_ENABLE && Int1_IsInterruptFired() == INTERRUPT_FIRED){
        INT1_ISR();
    }
    else {/* do nothing */}
    
    if(Int2_IsInterruptEnabled() == INTERRUPT_ENABLE && Int2_IsInterruptFired() == INTERRUPT_FIRED){
        INT2_ISR();
    }
    else {/* do nothing */}
    
    
    
    
    
    #endif  

    
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    #if INTERRUPT_IOC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        if(Ioc_IsInterruptEnabled() == INTERRUPT_ENABLE && Ioc_IsInterruptFired() == INTERRUPT_FIRED){
        IOC_ISR();

        
    }
    else {/* do nothing */}
    #endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////

     #if INTERRUPT_ADC_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        if(Adc_IsInterruptEnabled() == INTERRUPT_ENABLE && Adc_IsInterruptFired() == INTERRUPT_FIRED){
        Adc_ISR();

        
    }
    else {/* do nothing */}
    #endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if INTERRUPT_TIMER0_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Timer0_IsInterruptEnabled() == INTERRUPT_ENABLE && Timer0_IsInterruptFired() == INTERRUPT_FIRED){
        Timer0_ISR();
    }
    else {/* do nothing */}
    
#endif
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
#if INTERRUPT_TIMER1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Timer1_IsInterruptEnabled() == INTERRUPT_ENABLE && Timer1_IsInterruptFired() == INTERRUPT_FIRED){
        Timer1_ISR();
    }
    else {/* do nothing */}
    
#endif
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
#if INTERRUPT_TIMER2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Timer2_IsInterruptEnabled() == INTERRUPT_ENABLE && Timer2_IsInterruptFired() == INTERRUPT_FIRED){
        Timer2_ISR();
    }
    else {/* do nothing */}
    
#endif
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
#if INTERRUPT_TIMER3_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Timer3_IsInterruptEnabled() == INTERRUPT_ENABLE && Timer3_IsInterruptFired() == INTERRUPT_FIRED){
        Timer3_ISR();
    }
    else {/* do nothing */}
    
#endif
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
               
#if INTERRUPT_COMPARE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Compare1_IsInterruptEnabled() == INTERRUPT_ENABLE && Compare1_IsInterruptFired() == INTERRUPT_FIRED){
        Compare1_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   
                
#if INTERRUPT_CAPTURE1_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Capture1_IsInterruptEnabled() == INTERRUPT_ENABLE && Capture1_IsInterruptFired() == INTERRUPT_FIRED){
        Capture1_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                  
#if INTERRUPT_COMPARE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Compare2_IsInterruptEnabled() == INTERRUPT_ENABLE && Compare2_IsInterruptFired() == INTERRUPT_FIRED){
        Compare2_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   
                
#if INTERRUPT_CAPTURE2_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(Capture2_IsInterruptEnabled() == INTERRUPT_ENABLE && Capture2_IsInterruptFired() == INTERRUPT_FIRED){
        Capture2_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                  
#if INTERRUPT_EUSART_TX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(EusartTx_IsInterruptEnabled() == INTERRUPT_ENABLE && EusartTx_IsInterruptFired() == INTERRUPT_FIRED){
        EusartTx_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                 
#if INTERRUPT_EUSART_RX_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(EusartRx_IsInterruptEnabled() == INTERRUPT_ENABLE && EusartRx_IsInterruptFired() == INTERRUPT_FIRED){
        EusartRx_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                 
#if INTERRUPT_I2C_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(I2c_IsInterruptEnabled() == INTERRUPT_ENABLE && I2c_IsInterruptFired() == INTERRUPT_FIRED){
        I2c_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                 
#if INTERRUPT_I2C_WRITE_COLLISION_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

    
if(I2cWriteCollision_IsInterruptEnabled() == INTERRUPT_ENABLE && I2cWriteCollision_IsInterruptFired() == INTERRUPT_FIRED){
        I2cWriteCollision_ISR();
    }
    else {/* do nothing */}
    
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////// 

}




#endif