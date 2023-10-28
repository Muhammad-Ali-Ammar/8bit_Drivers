/*
 * main.c
 *
 *  Created on: 20 Oct 2023
 *      Author: muhammad
 */


#include "../SERIVICES/include/STD_TYPES.h"
#include "../SERIVICES/include/MAGIC_NUMBERS.h"
#include "../MCAL/PORT/include/PORT.h"
#include "../MCAL/DIO/include/DIO.h"
#include <util/delay.h>
#include  "../HAL/include/LCD.h"
#include  "../HAL/include/LCD_config.h"


extern Lcd_4bitType Lcd;

u8 Lcd_BoyCustomCharacter[]={0x1F, 0x15, 0x1F, 0x04,  0x1F,  0x04, 0x0E,  0x1F};
u8 Lcd_FloorCustomCharacter[]={0x00, 0x00, 0x00, 0x00,  0x00,  0x00, 0x1F,  0x00};
u8 Lcd_UpCustomCharacter[]={0x00, 0x00, 0x01, 0x02,  0x04,  0x08, 0x10,  0x00};
u8 Lcd_DeathCustomCharacter[]={0x04, 0x04, 0x04, 0x04,  0x04,  0x04, 0x04,  0x04};

#define LCD_BOY_INDEX		0
#define LCD_FLOOR_INDEX		1
#define LCD_UP_INDEX		2
#define LCD_DEATH_INDEX		3



void Lcd_FillTheFloor(void);
void Lcd_MovingTheBoyTheWholeScreen(void);
void Lcd_CreatingTheHoleAndLadderUp(void);
void Lcd_KillingTheBoy(void);
void Lcd_GameOver(void);

int main(){


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* This is Init Part */
	Port_voidInit();
	Lcd_4bit_enuInit(&Lcd);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Generte Custom Characters
	 *
	 * 1- The boy
	 * 2- The ground ( The floor ) _
	 * 3- Up Ladder \
	 * 4- Death Ladder |
	 *  */
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_BoyCustomCharacter, LCD_BOY_INDEX);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_FloorCustomCharacter, LCD_FLOOR_INDEX);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_UpCustomCharacter, LCD_UP_INDEX);
	Lcd_4bit_enuCreateCustomCharacter(&Lcd, Lcd_DeathCustomCharacter, LCD_DEATH_INDEX);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Display the floor to the all Screen cells
	Lcd_FillTheFloor();

	// Display the boy on the first cell
	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX,LCD_ROW1,LCD_COL1);


	// first step : move the boy to the whole of cells
		Lcd_MovingTheBoyTheWholeScreen();


	// Second Step : Create The Hole
	Lcd_CreatingTheHoleAndLadderUp();


	// Third Step : Killing and Game Over
	Lcd_KillingTheBoy();

	//Game Over
	Lcd_GameOver();

	while(1){


	}



}


void Lcd_FillTheFloor(void){

	u8 Loc_RowCounter = LCD_ROW1;
	u8 Loc_ColCounter = LCD_COL1;

	for(Loc_RowCounter = LCD_ROW1; Loc_RowCounter<=LCD_ROW_NUMBERS;Loc_RowCounter++){
		for(Loc_ColCounter = LCD_COL1; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){

			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_RowCounter,Loc_ColCounter);

		}
	}


}

void Lcd_MovingTheBoyTheWholeScreen(void){

	u8 Loc_RowCounter = LCD_ROW1;
	u8 Loc_ColCounter = LCD_COL2;

	u8 Loc_PreviousRow = LCD_ROW1;
	u8 Loc_PreviousCol = LCD_COL1;
	for(Loc_RowCounter = LCD_ROW1; Loc_RowCounter<=LCD_ROW_NUMBERS;Loc_RowCounter++){
		for(Loc_ColCounter = LCD_COL1; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){

			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_RowCounter,Loc_ColCounter);

			Loc_PreviousRow = Loc_RowCounter;
			Loc_PreviousCol = Loc_ColCounter;
			_delay_ms(100);
		}
	}

	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, LCD_ROW1,LCD_COL1);
	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);

}


void Lcd_CreatingTheHoleAndLadderUp(void){
	u8 Loc_RowCounter = LCD_ROW1;
	u8 Loc_ColCounter = LCD_COL2;

	u8 Loc_PreviousRow = LCD_ROW1;
	u8 Loc_PreviousCol = LCD_COL1;

	u8 Loc_HoleRow = LCD_ROW1;
	u8 Loc_HoleCol = LCD_COL15;

	u8 Loc_LadderRow = LCD_ROW2;
	u8 Loc_LadderCol = LCD_COL15;

	// create hole

	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', LCD_ROW1,LCD_COL15);

	// loop til reach to the hole
	for(Loc_ColCounter = LCD_COL2;Loc_ColCounter<= Loc_HoleCol; Loc_ColCounter++){

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_RowCounter,Loc_ColCounter);
		Loc_PreviousRow = Loc_RowCounter;
		Loc_PreviousCol = Loc_ColCounter;
		_delay_ms(100);
	}


	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ' ', Loc_PreviousRow,Loc_PreviousCol);

	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_LadderRow,Loc_LadderCol);
	_delay_ms(100);

	Loc_PreviousRow = Loc_LadderRow;
	Loc_PreviousCol = Loc_LadderCol;


	// continue after the whole
	for(Loc_ColCounter = Loc_HoleCol+ONE_VALUE; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_LadderRow,Loc_ColCounter);

		Loc_PreviousCol = Loc_ColCounter;

		_delay_ms(100);
	}



	// Create the Ladder
	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,LCD_UP_INDEX, Loc_LadderRow,Loc_LadderCol);
	// loop til you reach the ladder
	for(Loc_ColCounter = LCD_COL1; Loc_ColCounter<=Loc_LadderCol;Loc_ColCounter++){

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_LadderRow,Loc_ColCounter);

		Loc_PreviousCol = Loc_ColCounter;

		_delay_ms(100);
	}


	// continute he lifting up
	Loc_PreviousRow = Loc_LadderRow;
	Loc_PreviousCol = Loc_HoleCol;

	for(Loc_ColCounter = Loc_HoleCol; Loc_ColCounter<=LCD_COL_NUMBERS;Loc_ColCounter++){

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_HoleRow,Loc_ColCounter);

		Loc_PreviousCol = Loc_ColCounter;
		Loc_PreviousRow = Loc_HoleRow;

		_delay_ms(100);
	}




	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, LCD_ROW1,LCD_COL1);
	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);


}

void Lcd_KillingTheBoy(void){
		u8 Loc_RowCounter = LCD_ROW1;
		u8 Loc_ColCounter = LCD_COL2;

		u8 Loc_PreviousRow = LCD_ROW1;
		u8 Loc_PreviousCol = LCD_COL1;

		u8 Loc_ObstalceRow = LCD_ROW2;
		u8 Loc_ObstalceCol = LCD_COL10;


		// create the Obstalce

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd,LCD_DEATH_INDEX, Loc_ObstalceRow,Loc_ObstalceCol);

		// loop til reach to the Obstcale
		for(Loc_RowCounter = LCD_ROW1;((Loc_RowCounter != Loc_ObstalceRow) || Loc_ColCounter !=  Loc_ObstalceCol);Loc_RowCounter++){
				for(Loc_ColCounter = LCD_COL1;Loc_ColCounter <= LCD_COL_NUMBERS  ;Loc_ColCounter++){

					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_FLOOR_INDEX, Loc_PreviousRow,Loc_PreviousCol);
					Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_BOY_INDEX, Loc_RowCounter,Loc_ColCounter);

					Loc_PreviousRow = Loc_RowCounter;
					Loc_PreviousCol = Loc_ColCounter;
					_delay_ms(100);

					if ( (Loc_RowCounter == Loc_ObstalceRow) && Loc_ColCounter ==  Loc_ObstalceCol){
						--Loc_RowCounter;
						break;
					}

				}
			}

		Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);

}


void Lcd_GameOver(){

	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(3);
	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2,LCD_COL5);

	Lcd_4bit_enuDisplayString(&Lcd, " GAME OVER");



}
