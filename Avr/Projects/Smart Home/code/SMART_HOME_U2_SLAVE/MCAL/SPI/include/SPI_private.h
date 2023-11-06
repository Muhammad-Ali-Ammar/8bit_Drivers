/**************************************************************************/
/* Filename						: SPI_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 28 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/



#ifndef MCAL_SPI_INCLUDE_SPI_PRIVATE_H_
#define MCAL_SPI_INCLUDE_SPI_PRIVATE_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/
#define SPCR		    (*(volatile u8*)(0x2D))
#define SPSR			(*(volatile u8*)(0x2E))
#define SPDR			(*(volatile u8*)(0x2F))


#define SPCR_SPIE_BIT			(SEVEN_VALUE)
#define SPCR_SPE_BIT			(SIX_VALUE)
#define SPCR_MSTR_BIT			(FOUR_VALUE)


#define SPSR_SPIF_BIT		(SEVEN_VALUE)
#define SPSR_WCOL_BIT		(SIX_VALUE)

/********************************** Macros Function Declarations *********************/

#define Spi_Enable()			(SET_BIT(SPCR,SPCR_SPE_BIT))
#define Spi_Disable()			(CLEAR_BIT(SPCR,SPCR_SPE_BIT))

#define Spi_GetFlag()				(READ_BIT(SPSR,SPSR_SPIF_BIT))

#define Spi_isWirteCollisionHappened()		(READ_BIT(SPSR,SPSR_WCOL_BIT) == ONE_VALUE)

#define Spi_GetDataRegister()				(SPDR)
#define Spi_SetDataRegister(_DATA_)				(ASSIGN_REG(SPDR,_DATA_))

#define Spi_SelectMasterSlave(_ARGU_)			(WRITE_BIT(SPCR,SPCR_MSTR_BIT,_ARGU_))
#define Spi_SelectDataOrding(_ARGU_)			(WRITE_BIT(SPCR,FIVE_VALUE,_ARGU_))
#define Spi_SelectPolarity(_ARGU_)		    	(WRITE_BIT(SPCR,THREE_VALUE,_ARGU_))
#define Spi_SelectPhase(_ARGU_)		        	(WRITE_BIT(SPCR,TWO_VALUE,_ARGU_))

#define Spi_SelectClkSpeed(_ARGU_)		    	do{\
													((SPCR) = ((SPCR)& 0xFC) | ((_ARGU_) & 0x03) );\
													(WRITE_BIT(SPSR,ZERO_VALUE,((_ARGU_)>>TWO_VALUE)));\
													}while(ZERO_VALUE)



#define Spi_EnableInterrupt()				    (SET_BIT(SPCR,SEVEN_VALUE))
#define Spi_DisableInterrupt()				    (CLEAR_BIT(SPCR,SEVEN_VALUE))



#define Spi_IsRecevingDone()				(Spi_GetFlag() == ONE_VALUE)
#define Spi_IsTransmittingDone()			(Spi_GetFlag() == ONE_VALUE)

/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* MCAL_SPI_INCLUDE_SPI_PRIVATE_H_ */
