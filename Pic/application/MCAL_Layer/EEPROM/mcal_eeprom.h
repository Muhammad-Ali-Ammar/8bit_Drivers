/* 
 * File:   mcal_eeprom.h
 * Author: Muhammad Ammar
 *
 * Created on 29 ????, 2023, 07:30 ?
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/********************************** Includes *****************************************/

#include "../mcal_std_types.h"
#include "mcal_eeprom_cfg.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *******************************/



#define Eeprom_ChooseEepromMode()         { \
                                                EEPGD = 0;   \
                                                CFGS = 0;    \
                                                }


#define Eeprom_StartWriteCycle()           (EECON1bits.WR = 1)
#define Eeprom_IsWriteCycleCompleted()     (EECON1bits.WR == 0)


#define Eeprom_StartReadCycle()            (EECON1bits.RD = 1)
#define Eeprom_WaitTwoCycles()              { \
                                                NOP();   \
                                                NOP();    \
                                                }
/********************************** Data Type Declarations *******************************/



/********************************** Software Interfaces Declarations *******************************/

Std_ReturnType Eeprom_ReadByte(uint16 _address, uint8* _data);
Std_ReturnType Eeprom_WriteByte(uint16 _address, uint8 _data);


#endif	/* MCAL_EEPROM_H */

