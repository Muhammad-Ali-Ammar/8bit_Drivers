/* 
 * File:   mcal_std_types.h
 * Author: Muhammad Ammar 
 *
 * Created on 24 ??????, 2022, 10:54 ?
 * 
 * This file for the whole Project 
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/********************************** Includes *****************************************/
#include "mcal_compiler.h"
#include "mcal_std_libraries.h"



/********************************** Macros Function Declarations *******************************/


/********************************** Data Type Declarations *******************************/
typedef unsigned char     uint8;
typedef signed char       sint8;

typedef uint8             Std_ReturnType;


typedef unsigned short          uint16;
typedef signed short            sint16;

typedef unsigned long           uint32;
typedef signed long             sint32;


typedef unsigned long long      uint64;
typedef signed long long        sint64;


typedef float                   float32;
typedef double                  float64;

typedef unsigned char         boolean;



/********************************** Macros Declarations *******************************/

#define STD_HIGH        (0x01u)
#define STD_LOW         (0x00u)

#define STD_ON          (0x01u)
#define STD_OFF         (0x00u)

#define STD_ACTIVE      (0x01u)
#define STD_IDLE        (0x00u)


#define E_OK                ((Std_ReturnType)0x01)
#define E_NOT_OK            ((Std_ReturnType)0x00)


#define ZERO_VALUE          ((uint8)0)

/********************************** Software Interfaces Declarations *******************************/



#endif	/* MCAL_STD_TYPES_H */

