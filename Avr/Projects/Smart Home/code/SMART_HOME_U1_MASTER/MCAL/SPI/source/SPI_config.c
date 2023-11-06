/**************************************************************************/
/* Filename						: SPI_config.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 28 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/





/********************************** Includes *********************************************/
#include "../../../SERIVICES/include/STD_TYPES.h"
#include "../../../SERIVICES/include/BIT_UTILS.h"
#include "../../../SERIVICES/include/HELPERS.h"
#include "../../../SERIVICES/include/MAGIC_NUMBERS.h"

#include "../../DIO/include/DIO.h"
#include "../include/SPI_config.h"
#include "../include/SPI_private.h"
#include "../include/SPI.h"


/********************************** Macros Declarations *******************************/

/********************************** Macros Function Declarations *********************/


/********************************** Data Type Definition ****************************/

Spi_ConfigType Spi ={
		.select_clk_speed = SPI_SELECT_CLK_FREQ_DIV_128,
		.select_data_ording = SPI_SELECT_DATA_LSB_FIRST,
		.select_master_or_slave = SPI_SELECT_MASTER_MODE,
		.select_phase = SPI_SELECT_PHASE_SETUP_WRITE_FIRST_AT_LEADING_EDGE,
		.select_polarity = SPI_SELECT_POLARITY_IDLE_LOW_LEADING_EDGE_RISING
};


/********************************** Software Interfaces Declarations *******************/
