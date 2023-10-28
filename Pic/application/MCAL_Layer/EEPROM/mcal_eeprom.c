/* 
 * File:   mcal_eeprom.h
 * Author: Muhammad Ammar
 *
 * Created on 29 ????, 2023, 07:30 ?
 */


#include "mcal_eeprom.h"



Std_ReturnType Eeprom_ReadByte(uint16 _address, uint8* _data){
    Std_ReturnType ret = E_OK;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        
        /* Write address to address reg  */
        EEADRH = (uint8) ((_address>>8) & 0x33);
        EEADR = (uint8)(_address & 0xFF);
        
        /* Select or choose EEPROM Mode*/
        Eeprom_ChooseEepromMode();
        
        /* Initiate Read Cycle,, Read control bit  */
          Eeprom_StartReadCycle();
          
       /* Wait 2 Cycles*/
          Eeprom_WaitTwoCycles();
          
        /* Return Data Value*/
          
         *_data = EEDATA;
    }
     
    
    return ret;
          
}
Std_ReturnType Eeprom_WriteByte(uint16 _address, uint8 _data){
    
    Std_ReturnType ret = E_OK;
    uint8 l_interrupt_status = ZERO_VALUE;
    
    /* Read Status of The interrupt */
    l_interrupt_status = Interrupt_GetInterruptStatus();
    
    /* Write address to address reg  */
    EEADRH = (uint8) ((_address>>8) & 0x33);
    EEADR = (uint8)(_address & 0xFF);
    
    /* Write Data To Data Reg*/
    EEDATA = _data;
    
    /* Select or choose EEPROM Mode*/
    Eeprom_ChooseEepromMode();
    
    /*Enable Write Mode */
    WREN = 1;
    
    /* Disable Interrupt*/
    Interrupt_Disable();
    
    
    /* Write Password code To EECON2*/
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    /* Initiate Write Cycle,, write control bit  */
    Eeprom_StartWriteCycle();
    
    /*wait for writing to be completed*/
    while(Eeprom_IsWriteCycleCompleted() == ZERO_VALUE);
    
    /* Disable EEPRM Write */
    WREN = 0;
    
    /* Return Status of Interrupt as it Was */
    Interrupt_SetInterruptStatus(l_interrupt_status);
    
    return ret;
}
