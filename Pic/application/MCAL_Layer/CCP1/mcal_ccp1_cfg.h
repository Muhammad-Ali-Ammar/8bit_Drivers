/* 
 * File:   mcal_ccp1_cfg.h
 * Author: isammar93
 *
 * Created on 22 ?????, 2023, 07:52 ?
 */

#ifndef MCAL_CCP1_CFG_H
#define	MCAL_CCP1_CFG_H


/********************************** Includes *****************************************/
#include "../mcal_std_types.h"


/********************************** Macros Declarations *******************************/

#define CCP1_MODULE_ENABLE              (1)

// Comment the next defines and let only one 

//#define CCP1_CFG_CAPTURE_MODE_SELECTED                 CCP1_MODULE_ENABLE
#define CCP1_CFG_COMPARE_MODE_SELECTED               CCP1_MODULE_ENABLE
//#define CCP1_CFG_PWM_MODE_SELECTED                   CCP1_MODULE_ENABLE

/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/



/********************************** Software Interfaces Declarations *******************************/


#endif	/* MCAL_CCP1_CFG_H */

