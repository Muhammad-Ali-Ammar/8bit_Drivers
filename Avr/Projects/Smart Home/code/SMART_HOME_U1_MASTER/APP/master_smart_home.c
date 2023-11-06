/**************************************************************************/
/* Filename						: main.h                                  */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 2 Nov 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/* Trainee At					: NTI (4 Months)						  */
/* Instructor					: Mahmoud Embabi						  */
/**************************************************************************/

#include "master_smart_home.h"

///////////////////////////////////////////////////////////////////////////


#define SMART_USART_MODE 				    	    2
#define SMART_KEYPAD_MODE 				        	1
#define SMART_NOT_SELECT_MODE						0

#define USART_STATUS_PRESS				    1
#define USART_STATUS_NOT_PRESS				0



#define SPI_SLAVE_PIN					DIO_PINB4_CHANNEL12


////////////////////////////////////////////////////////////////////////////

volatile u8 Keypad_u8Result;
volatile Keypad_ErrorStatusType Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;


volatile u8 Usart_u8Status = ZERO_VALUE;
volatile u8 Usart_u8Value ;

volatile u8 Smart_u8Value ;

u8 Smart_u8Mode  = ZERO_VALUE;

u8 MasterSmart_u8SlavePins = ZERO_VALUE;
static u8 Loc_u8FirstTime = ONE_VALUE;
///////////////////////////////////////////////////////////////////////
#define LCD_CURSOR					0xFF

///////////////////////////////////////////////////////////////////////////


u8 AdminListStatus[] ={0,
				0, /* Door */
				0, /* room 1*/
				0, /* room 2*/
				0,	/* room 3*/
				0,  /* show time*/
				0,	/* add user */
				0,  /* delete user */
				0 /* back to menu*/
};

////////////////////////////////////////////////////////////////////////////

u8 AdminListArr[][20]={" ",
					"1- Close The Door",
					"1- Open The Door",
					"2- Turn Off Room1",
					"2- Turn On Room1",
					"3- Turn Off Room2",
					"3- Turn On Room2",
					"4- Turn Off Room3",
					"4- Turn On Room3",
					"5- Show The Time",
					"5- Show The Time",
					"6- Add User",
					"6- Add User",
					"7- Delete User",
					"7- Delete User",
					"8- Back To Menu",
					"8- Back To Menu"

};


u8 UserListArr[][20]={" ",
					"1- Close The Door",
					"1- Open The Door",
					"2- Turn Off Room1",
					"2- Turn On Room1",
					"3- Turn Off Room2",
					"3- Turn On Room2",
					"4- Turn Off Room3",
					"4- Turn On Room3",
					"5- Show The Time",
					"5- Show The Time",
					"6- Change Password",
					"6- Change Password",
					"7- Back To Menu",
					"7- Back To Menu"

};
//////////////////////////////////////////////////////////////////////////
int main(){
	Smart_enuInit();

	while(1){

		smart_WelcomeHome();
		if(Smart_u8Mode == SMART_USART_MODE){
			// USART MODE
			if(Usart_u8Value =='1'){
				Smart_UartModeAdmin();

			}
			else if(Usart_u8Value =='2')
				Smart_UartModeUser();
		}
		else if(Smart_u8Mode == SMART_KEYPAD_MODE){
			// KEYPAD MODE
			if(Keypad_u8Result =='1'){
				Smart_KeypadModeAdmin();

			}
			else if(Keypad_u8Result =='2')
				Smart_KeypadModeUser();
		}




	}
	return 0;
}



void smart_WelcomeHome(void){

	/* Init Values */
Smart_u8Mode = ZERO_VALUE;
Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
Usart_u8Status = USART_STATUS_NOT_PRESS;

	/* enable interrupts */
	Usart_enuEnableRxInterrupt();
	Timer0_enuEnableOverflowInterrupt();

Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
_delay_ms(LCD_CLEAR_DELAY);
Lcd_4bit_enuDisplayStringWithPosition(&Lcd,(u8*) "Welcome Home", LCD_ROW1, LCD_COL7);
Lcd_4bit_enuDisplayStringWithPosition(&Lcd,(u8*) "1- Select Admin ", LCD_ROW2, LCD_COL1);
Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"2- Select User ", LCD_ROW3, LCD_COL1);

Usart_enuTransmitStringBlocking(&Usart1, (u8*)"                  Welcome Home\r");
Usart_enuTransmitStringBlocking(&Usart1, (u8*)"1- Select Admin\r");
Usart_enuTransmitStringBlocking(&Usart1, (u8*)"2- Select User \r");


	while( Smart_u8Mode == SMART_NOT_SELECT_MODE ){

		if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result == '1' || Keypad_u8Result =='2')){

			/* KeyPad Mode */
			Smart_u8Mode = SMART_KEYPAD_MODE;

		}

		else if(Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value == '1' || Usart_u8Value =='2')){


			/* Uart Mode */
			Smart_u8Mode = SMART_USART_MODE;
			Usart_u8Status = USART_STATUS_NOT_PRESS;
		}


	}

}



void Smart_KeypadModeAdmin(){

	u8 Loc_u8AdminPassword = ZERO_VALUE;
	u8 Loc_u8Check = ONE_VALUE;
	u8 Loc_u8RealAdminPassword;

	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_CLEAR_DELAY);
	Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;

	///////////////////////////////////////////////////////////////
	if(Loc_u8FirstTime == ONE_VALUE){
		Loc_u8FirstTime = ZERO_VALUE;
		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Admin New Password",LCD_ROW1,LCD_COL1);
		Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW2, LCD_COL1);

		while(Loc_u8Check != ZERO_VALUE){

			if(Keypad_Status == KEYPAD_IS_PRESSED){
				if(Keypad_u8Result != '='){
					Loc_u8AdminPassword=Loc_u8AdminPassword*10 + (Keypad_u8Result-'0');
					Lcd_4bit_enuDisplayCharacter(&Lcd, '*');
				}
				else{
					Loc_u8Check = ZERO_VALUE;
					ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, ZERO_VALUE, Loc_u8AdminPassword);
					Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
					_delay_ms(LCD_CLEAR_DELAY);

					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Admin Password Done", LCD_ROW2, LCD_COL2);
					_delay_ms(1000);


				}
				Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
			}

		}

	}
	////////////////////////////////////////////////////////////////////////////
	else{
		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Enter Admin Password",LCD_ROW1,LCD_COL1);

		ExternalEeprom_ReadByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, ZERO_VALUE, &Loc_u8RealAdminPassword);

		while(Loc_u8Check != ZERO_VALUE){


					if(Keypad_Status == KEYPAD_IS_PRESSED){
						if(Keypad_u8Result != '='){
							Loc_u8AdminPassword=Loc_u8AdminPassword*10 + (Keypad_u8Result-'0');
							Lcd_4bit_enuDisplayCharacter(&Lcd, '*');
						}
						else{


								if(Loc_u8RealAdminPassword == Loc_u8AdminPassword){
									// password is right
									Loc_u8Check = ZERO_VALUE;
									Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
									_delay_ms(LCD_CLEAR_DELAY);

									Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Password Is Right",LCD_ROW2,LCD_COL2);
									_delay_ms(500);
									Smart_KeypadAdminList();
								}
								else{
									Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
									_delay_ms(LCD_CLEAR_DELAY);

									Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Password Is WRONG",LCD_ROW2,LCD_COL2);
									Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Try Again ",LCD_ROW4,LCD_COL6);
									_delay_ms(500);
									Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
									_delay_ms(LCD_CLEAR_DELAY);
									Loc_u8AdminPassword = ZERO_VALUE;
									Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Enter Admin Password",LCD_ROW1,LCD_COL1);

								}


						}
						Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
					}

				}

	}
}

void Smart_KeypadModeUser(){
	/*
	 * 1- Open/Close The door
	 * 2- Turn On/ Turn Off Room1
	 * 3- Turn On/ Turn Off Room2
	 * 4- Turn On/ Turn Off Room3
	 * 5- show the time
	 * 6- Change Password
	 * 7- back to the main menu
	 */



		u8 Loc_u8TempData = ZERO_VALUE ;



///////////////////// LOG IN PART ///////////////////////////////////////////////////

		u8 Loc_u8Check = ONE_VALUE;
		u8 Loc_u8UsernameId= ZERO_VALUE;
		u8 Loc_u8Password= ZERO_VALUE;
		u8 Loc_u8RealPassword = ZERO_VALUE;
		u8 Loc_u8TryAgain = ONE_VALUE;

		u8 Loc_u8Index = ZERO_VALUE;
		u8 Loc_u8CursorIndex = ONE_VALUE;
		u8 Loc_u8Start = ONE_VALUE;
		u8 Loc_u8TempStart = ONE_VALUE;

			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;

			while(Loc_u8TryAgain == ONE_VALUE){
		        Loc_u8Check = ONE_VALUE;

				Loc_u8Password= ZERO_VALUE;
				Loc_u8RealPassword = ZERO_VALUE;
				Loc_u8Check = ONE_VALUE;

			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
			_delay_ms(LCD_CLEAR_DELAY);
			Lcd_4bit_enuDisplayString(&Lcd, (u8*)"Enter Username ID:");

			while(Loc_u8Check != ZERO_VALUE){
				Loc_u8UsernameId=ZERO_VALUE;
				if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result>='0') && (Keypad_u8Result<='9')){
					Loc_u8UsernameId = Keypad_u8Result-'0';
					Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8UsernameId);
					Loc_u8Check = ZERO_VALUE;
					Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
				}

			}

			/* Password Part */
			Loc_u8Check = ONE_VALUE;

			Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Enter Password: ",LCD_ROW2,LCD_COL1);
			Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW3, LCD_COL1);
			while(Loc_u8Check != ZERO_VALUE){

				if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result>='0') && (Keypad_u8Result<='9')){
					Loc_u8Password = Loc_u8Password*10+ Keypad_u8Result-'0';
					Lcd_4bit_enuDisplayCharacter(&Lcd, '*');
					Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
				}
				else if (Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result=='=')){
					ExternalEeprom_ReadByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8UsernameId, &Loc_u8RealPassword);
					Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
					_delay_ms(LCD_DISPLAY_DELAY);

					if(Loc_u8RealPassword == Loc_u8Password){
						Loc_u8TryAgain = ZERO_VALUE;
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"  Logging In", LCD_ROW2,LCD_COL4);
					}
					else{
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)" Wrong Password", LCD_ROW2,LCD_COL4);
					}

					_delay_ms(800);
					Loc_u8Check = ZERO_VALUE;
					Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;



				}

			}

			}


			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
			_delay_ms(LCD_DISPLAY_DELAY);

		Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_CURSOR, Loc_u8CursorIndex, LCD_COL20);
		for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<FOUR_VALUE; Loc_u8Index++ ){
			Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)UserListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]],Loc_u8Index+1,LCD_COL1);
		}

		Loc_u8Check = ONE_VALUE;
		while(Loc_u8Check != ZERO_VALUE){

			if(Keypad_Status == KEYPAD_IS_PRESSED){


				Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
				switch(Keypad_u8Result){

				case '1':
					Timer0_enuDisableOverflowInterrupt();
					Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
					_delay_ms(LCD_CLEAR_DELAY);

					if(AdminListStatus[ONE_VALUE] == ZERO_VALUE){
						Servo_enuSetAngle(180);
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Door Is Open", LCD_ROW2,LCD_COL4);
						AdminListStatus[ONE_VALUE] = ONE_VALUE;
					}
					else {
						Servo_enuSetAngle(0);
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Door Is Closed", LCD_ROW2,LCD_COL4);
						AdminListStatus[ONE_VALUE] = ZERO_VALUE;
					}
					_delay_ms(500);
					Timer0_enuEnableOverflowInterrupt();
					break;


				case '2':
					Timer0_enuDisableOverflowInterrupt();
					Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
					_delay_ms(LCD_CLEAR_DELAY);

					if(AdminListStatus[TWO_VALUE] == ZERO_VALUE){
						SET_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room1 Is On", LCD_ROW2,LCD_COL4);
						AdminListStatus[TWO_VALUE] = ONE_VALUE;
					}
					else {

						CLEAR_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room1 Is Off", LCD_ROW2,LCD_COL4);
						AdminListStatus[TWO_VALUE] = ZERO_VALUE;
					}
					Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);

					_delay_ms(500);
					Timer0_enuEnableOverflowInterrupt();

					break;

				case '3':
					Timer0_enuDisableOverflowInterrupt();
					Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
					_delay_ms(LCD_CLEAR_DELAY);

					if(AdminListStatus[THREE_VALUE] == ZERO_VALUE){
						SET_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room2 Is On", LCD_ROW2,LCD_COL4);
						AdminListStatus[THREE_VALUE] = ONE_VALUE;
					}
					else {
						CLEAR_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room2 Is Off", LCD_ROW2,LCD_COL4);
						AdminListStatus[THREE_VALUE] = ZERO_VALUE;
					}
					Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);
					_delay_ms(500);
					Timer0_enuEnableOverflowInterrupt();
					break;
				case '4':
					Timer0_enuDisableOverflowInterrupt();
					Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
					_delay_ms(LCD_CLEAR_DELAY);

					if(AdminListStatus[FOUR_VALUE] == ZERO_VALUE){
						SET_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room3 Is On", LCD_ROW2,LCD_COL4);
						AdminListStatus[FOUR_VALUE] = ONE_VALUE;
					}
					else {
						// Spi
						Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room3 Is Off", LCD_ROW2,LCD_COL4);
						AdminListStatus[FOUR_VALUE] = ZERO_VALUE;
						CLEAR_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
					}
					Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);
					_delay_ms(500);
					Timer0_enuEnableOverflowInterrupt();
					break;
				case '5': // show time

					Timer0_enuDisableOverflowInterrupt();
					Smart_ShowTime();
					Timer0_enuEnableOverflowInterrupt();
					break;

				case '6':// Change Password
					MasterSmart_ChangePasswordKeypad(Loc_u8UsernameId,Loc_u8RealPassword);
					ExternalEeprom_ReadByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8UsernameId, &Loc_u8RealPassword);
					break;

				case '7':
					Loc_u8Check = ZERO_VALUE;
					break;
				case '-':
					Loc_u8CursorIndex = (Loc_u8CursorIndex-1)<1? 1 : Loc_u8CursorIndex-1;
					Loc_u8Start = (Loc_u8Start-1)<1? 1 : Loc_u8Start-1;
//					if(Loc_u8Start == 3)
//						Loc_u8Start = 2;
					break;
				case '+':

					Loc_u8CursorIndex = (Loc_u8CursorIndex+1)>4? 4 : Loc_u8CursorIndex+1;
					Loc_u8Start = (Loc_u8Start+1)>4? 4 : Loc_u8Start+1;

					break;

				default :
					break;

				}
				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(LCD_CLEAR_DELAY);
				Loc_u8TempStart = Loc_u8Start;
				Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_CURSOR, Loc_u8CursorIndex, LCD_COL20);
				for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<FOUR_VALUE; Loc_u8Index++ ){
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, UserListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]],Loc_u8Index+1,LCD_COL1);
				}


			}

		} // while
}

void Smart_KeypadAdminList(){

/*
 * 1- Open/Close The door
 * 2- Turn On/ Turn Off Room1
 * 3- Turn On/ Turn Off Room2
 * 4- Turn On/ Turn Off Room3
 * 5- show the time
 * 6- Add User
 * 7- Delete User
 * 8- back to the main menu
 */

	u8 Loc_u8Index = ZERO_VALUE;
	u8 Loc_u8CursorIndex = ONE_VALUE;
	u8 Loc_u8Start = ONE_VALUE;
	u8 Loc_u8TempStart = ONE_VALUE;
	u8 Loc_u8Check = ONE_VALUE;
	u8 Loc_u8TempData = ZERO_VALUE ;
	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_CLEAR_DELAY);

	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_CURSOR, Loc_u8CursorIndex, LCD_COL20);
	for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<FOUR_VALUE; Loc_u8Index++ ){
		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)AdminListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]],Loc_u8Index+1,LCD_COL1);
	}


	while(Loc_u8Check != ZERO_VALUE){

		if(Keypad_Status == KEYPAD_IS_PRESSED){


			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
			switch(Keypad_u8Result){

			case '1':
				Timer0_enuDisableOverflowInterrupt();
				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(LCD_CLEAR_DELAY);

				if(AdminListStatus[ONE_VALUE] == ZERO_VALUE){
					Servo_enuSetAngle(180);
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Door Is Open", LCD_ROW2,LCD_COL4);
					AdminListStatus[ONE_VALUE] = ONE_VALUE;
				}
				else {
					Servo_enuSetAngle(0);
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Door Is Closed", LCD_ROW2,LCD_COL4);
					AdminListStatus[ONE_VALUE] = ZERO_VALUE;
				}
				_delay_ms(500);
				Timer0_enuEnableOverflowInterrupt();
				break;


			case '2':
				Timer0_enuDisableOverflowInterrupt();
				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(LCD_CLEAR_DELAY);

				if(AdminListStatus[TWO_VALUE] == ZERO_VALUE){
					SET_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room1 Is On", LCD_ROW2,LCD_COL4);
					AdminListStatus[TWO_VALUE] = ONE_VALUE;
				}
				else {

					CLEAR_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room1 Is Off", LCD_ROW2,LCD_COL4);
					AdminListStatus[TWO_VALUE] = ZERO_VALUE;
				}
				Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);

				_delay_ms(500);
				Timer0_enuEnableOverflowInterrupt();

				break;

			case '3':
				Timer0_enuDisableOverflowInterrupt();
				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(LCD_CLEAR_DELAY);

				if(AdminListStatus[THREE_VALUE] == ZERO_VALUE){
					SET_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room2 Is On", LCD_ROW2,LCD_COL4);
					AdminListStatus[THREE_VALUE] = ONE_VALUE;
				}
				else {
					CLEAR_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room2 Is Off", LCD_ROW2,LCD_COL4);
					AdminListStatus[THREE_VALUE] = ZERO_VALUE;
				}
				Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);
				_delay_ms(500);
				Timer0_enuEnableOverflowInterrupt();
				break;
			case '4':
				Timer0_enuDisableOverflowInterrupt();
				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(LCD_CLEAR_DELAY);

				if(AdminListStatus[FOUR_VALUE] == ZERO_VALUE){
					SET_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room3 Is On", LCD_ROW2,LCD_COL4);
					AdminListStatus[FOUR_VALUE] = ONE_VALUE;
				}
				else {
					// Spi
					Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Room3 Is Off", LCD_ROW2,LCD_COL4);
					AdminListStatus[FOUR_VALUE] = ZERO_VALUE;
					CLEAR_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
				}
				Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);
				_delay_ms(500);
				Timer0_enuEnableOverflowInterrupt();
				break;
			case '5': // show time

				Timer0_enuDisableOverflowInterrupt();
				Smart_ShowTime();
				Timer0_enuEnableOverflowInterrupt();
				break;

			case '6':// add user
				Smart_AddUserKeypad();
				break;
			case '7': // delete user
				Smart_DeleteUserKeypad();
				break;
			case '8':
				Loc_u8Check = ZERO_VALUE;
				break;
			case '-':
				Loc_u8CursorIndex = (Loc_u8CursorIndex-1)<1? 1 : Loc_u8CursorIndex-1;
				Loc_u8Start = (Loc_u8Start-1)<1? 1 : Loc_u8Start-1;
				if(Loc_u8Start == 3)
					Loc_u8Start = 2;
				break;
			case '+':

				Loc_u8CursorIndex = (Loc_u8CursorIndex+1)>4? 4 : Loc_u8CursorIndex+1;
				Loc_u8Start = (Loc_u8Start+1)>5? 5 : Loc_u8Start+1;
				if(Loc_u8Start == 3)
					Loc_u8Start = 4;
				break;

			default :
				break;

			}
			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
			_delay_ms(LCD_CLEAR_DELAY);
			Loc_u8TempStart = Loc_u8Start;
			Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, LCD_CURSOR, Loc_u8CursorIndex, LCD_COL20);
			for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<FOUR_VALUE; Loc_u8Index++ ){
				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, AdminListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]],Loc_u8Index+1,LCD_COL1);
			}


		}

	} // while
}


void Smart_AddUserKeypad(){
	u8 Loc_u8Check = ONE_VALUE;
	u8 Loc_u8UsernameId;
	u8 Loc_u8Password= ZERO_VALUE;
	Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_CLEAR_DELAY);

	Lcd_4bit_enuDisplayString(&Lcd, (u8*)"Enter Username ID:");

	while(Loc_u8Check != ZERO_VALUE){

		if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result>='0') && (Keypad_u8Result<='9')){
			Loc_u8UsernameId = Keypad_u8Result-'0';
			Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8UsernameId);
			Loc_u8Check = ZERO_VALUE;
			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
		}

	}

	/* Password Part */
	Loc_u8Check = ONE_VALUE;

	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Enter Password: ",LCD_ROW2,LCD_COL1);
	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW3, LCD_COL1);
	while(Loc_u8Check != ZERO_VALUE){

		if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result>='0') && (Keypad_u8Result<='9')){
			Loc_u8Password = Loc_u8Password*10+ Keypad_u8Result-'0';
			Lcd_4bit_enuDisplayCharacter(&Lcd, '*');
			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
		}
		else if (Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result=='=')){
			ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, (u8)Loc_u8UsernameId, (u8)Loc_u8Password);
			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
			_delay_ms(LCD_DISPLAY_DELAY);
			Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"User ", LCD_ROW2, LCD_COL3);
			Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8UsernameId);
			Lcd_4bit_enuDisplayString(&Lcd, (u8*)" Is Added ");
			Loc_u8Check = ZERO_VALUE;
			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;



		}

	}
	_delay_ms(800);
}



void Smart_ShowTime(){
	u8 Loc_u8Second =ZERO_VALUE;
	u8 Loc_u8Minute =ZERO_VALUE;
	u8 Loc_u8Hour =ZERO_VALUE;
	u8 Loc_u8Day =ZERO_VALUE;
	u8 Loc_u8Month =ZERO_VALUE;
	u8 Loc_u8Year =ZERO_VALUE;
	u32 Loc_u32Counter = ZERO_VALUE;


	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_CLEAR_DELAY);

	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Date:  ", LCD_ROW3,LCD_COL1);


	_delay_ms(100);
	Rtc_enuGetDay(&Loc_u8Day);
	Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8Day);
	Lcd_4bit_enuDisplayCharacter(&Lcd, ':');

	_delay_ms(100);
	Rtc_enuGetMonth(&Loc_u8Month);
	Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8Month);
	Lcd_4bit_enuDisplayCharacter(&Lcd, ':');

	_delay_ms(100);
	Rtc_enuGetYear(&Loc_u8Year);
	Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8Year);



	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Clock:  ", LCD_ROW1,LCD_COL1);

	// display for 3 seconds





	Rtc_enuGetHour(&Loc_u8Hour);
//	Lcd_4bit_enuDisplayStringWithPosition(&Lcd,(u8*)"  ",LCD_ROW1,LCD_COL10);
	Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u8Hour,LCD_ROW1,LCD_COL10);
	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ':',LCD_ROW1,LCD_COL12);
	_delay_ms(100);

	Rtc_enuGetMinute(&Loc_u8Minute);
//	Lcd_4bit_enuDisplayStringWithPosition(&Lcd,(u8*)"  ",LCD_ROW1,LCD_COL13);
	Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u8Minute,LCD_ROW1,LCD_COL13);
	Lcd_4bit_enuDisplayCharacterWithPosition(&Lcd, ':',LCD_ROW1,LCD_COL15);
	_delay_ms(100);

	for(Loc_u32Counter =ZERO_VALUE;Loc_u32Counter<FIVE_VALUE;++Loc_u32Counter){
	Rtc_enuGetSecond(&Loc_u8Second);
	Lcd_4bit_enuDisplayStringWithPosition(&Lcd,(u8*)"  ",LCD_ROW1,LCD_COL16);
	Lcd_4bit_enuDisplayNumberWithPosition(&Lcd, Loc_u8Second,LCD_ROW1,LCD_COL16);
	_delay_ms(500);
	}





}
void Smart_DeleteUserKeypad(){

	   u8 Loc_u8Check = ONE_VALUE;
		u8 Loc_u8UsernameId= NINE_VALUE;

		Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
		Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
		_delay_ms(LCD_CLEAR_DELAY);

		Lcd_4bit_enuDisplayString(&Lcd, (u8*)"Enter Username ID:");

		while(Loc_u8Check != ZERO_VALUE){

			if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result>='0') && (Keypad_u8Result<='9')){
				Loc_u8UsernameId = Keypad_u8Result-'0';
				Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8UsernameId);
				Loc_u8Check = ZERO_VALUE;
				Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
			}

		}
		Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
		_delay_ms(LCD_CLEAR_DELAY);
		Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"User ", LCD_ROW2, LCD_COL3);
		Lcd_4bit_enuDisplayNumber(&Lcd, Loc_u8UsernameId);
		Lcd_4bit_enuDisplayString(&Lcd, (u8*)" Is Deleted ");

		ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8UsernameId, 0xFF);
		_delay_ms(800);

}

void MasterSmart_ChangePasswordKeypad(u8 Loc_u8CopyUserId,u8 Loc_u8CopyUserPassword){

	u8 Loc_u8Check = ONE_VALUE;
	u8 Loc_u8Password = ZERO_VALUE;
	Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
	_delay_ms(LCD_DISPLAY_DELAY);

	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Enter Old Password: ",LCD_ROW2,LCD_COL1);
	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW3, LCD_COL1);
	while(Loc_u8Check != ZERO_VALUE){

		if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result>='0') && (Keypad_u8Result<='9')){
			Loc_u8Password = Loc_u8Password*10+ Keypad_u8Result-'0';
			Lcd_4bit_enuDisplayCharacter(&Lcd, '*');
			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
		}
		else if (Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result=='=')){
			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
			_delay_ms(LCD_DISPLAY_DELAY);

			if(Loc_u8CopyUserPassword == Loc_u8Password){
				Loc_u8Check = ZERO_VALUE;
			}

			else{
				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)" Wrong Password", LCD_ROW2,LCD_COL4);
				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"  Try Again ", LCD_ROW4,LCD_COL4);
				Loc_u8Password = ZERO_VALUE;
				_delay_ms(800);

				Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
				_delay_ms(LCD_DISPLAY_DELAY);

				Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Enter Old Password: ",LCD_ROW2,LCD_COL1);
				Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW3, LCD_COL1);
			}



			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;



		}

	}

	/* Password Part */
	Loc_u8Check = ONE_VALUE;
	Loc_u8Password =ZERO_VALUE;
	Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Enter New Password: ",LCD_ROW2,LCD_COL1);
	Lcd_4bit_enuGoToXY(&Lcd, LCD_ROW3, LCD_COL1);
	while(Loc_u8Check != ZERO_VALUE){

		if(Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result>='0') && (Keypad_u8Result<='9')){
			Loc_u8Password = Loc_u8Password*10+ Keypad_u8Result-'0';
			Lcd_4bit_enuDisplayCharacter(&Lcd, '*');
			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;
		}
		else if (Keypad_Status == KEYPAD_IS_PRESSED && (Keypad_u8Result=='=')){
			ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8CopyUserId, Loc_u8Password);

			Lcd_4bit_enuSendCommand(&Lcd, LCD_CLEAR_COMMAND);
			_delay_ms(LCD_DISPLAY_DELAY);
			Lcd_4bit_enuDisplayStringWithPosition(&Lcd, (u8*)"Change is done ", LCD_ROW2, LCD_COL3);

			Loc_u8Check = ZERO_VALUE;
			Keypad_Status = KEYPAD_STATUS_NOT_PRESSED;



		}

	}
	_delay_ms(800);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Smart_UartModeAdmin(){
	    u8 Loc_u8AdminPassword = ZERO_VALUE;
		u8 Loc_u8Check = ONE_VALUE;
		u8 Loc_u8RealAdminPassword;
		Usart_u8Status = ZERO_VALUE;
		///////////////////////////////////////////////////////////////
		if(Loc_u8FirstTime == ONE_VALUE){
			Loc_u8FirstTime = ZERO_VALUE;
			Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rAdmin New Password\r");

			while(Loc_u8Check != ZERO_VALUE){

				if(Usart_u8Status == USART_STATUS_PRESS){
					if(Usart_u8Value != '\r'){
						Loc_u8AdminPassword=Loc_u8AdminPassword*10 + (Usart_u8Value-'0');
					}
					else{
						Loc_u8Check = ZERO_VALUE;
						ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, ZERO_VALUE, Loc_u8AdminPassword);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rAdmin Password Done\r");

					}
					Usart_u8Status = USART_STATUS_NOT_PRESS;
				}

			}

		}
		////////////////////////////////////////////////////////////////////////////
		else{
			Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter Admin Password\r");

			ExternalEeprom_ReadByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, ZERO_VALUE, &Loc_u8RealAdminPassword);

			while(Loc_u8Check != ZERO_VALUE){


						if(Usart_u8Status == USART_STATUS_PRESS){
							if(Usart_u8Value != '\r'){
								Loc_u8AdminPassword=Loc_u8AdminPassword*10 + (Usart_u8Value-'0');
							}
							else{


									if(Loc_u8RealAdminPassword == Loc_u8AdminPassword){
										// password is right
										Loc_u8Check = ZERO_VALUE;

										Usart_enuTransmitStringBlocking(&Usart1,  (u8*)"\rPassword Is Right\r");
										Smart_UartAdminList();
									}
									else{

										Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\r\rPassword Is WRONG\r");
										Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\r\rTry Again \r");

										Loc_u8AdminPassword = ZERO_VALUE;
										Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter Admin Password\r");

									}


							}
							Usart_u8Status = USART_STATUS_NOT_PRESS;
						}

					}

		}
}
void Smart_UartModeUser(){

	u8 Loc_u8TempData = ZERO_VALUE ;



///////////////////// LOG IN PART ///////////////////////////////////////////////////

	u8 Loc_u8Check = ONE_VALUE;
	u8 Loc_u8UsernameId= ZERO_VALUE;
	u8 Loc_u8Password= ZERO_VALUE;
	u8 Loc_u8RealPassword = ZERO_VALUE;
	u8 Loc_u8TryAgain = ONE_VALUE;

	u8 Loc_u8Index = ZERO_VALUE;
	u8 Loc_u8CursorIndex = ONE_VALUE;
	u8 Loc_u8Start = ONE_VALUE;
	u8 Loc_u8TempStart = ONE_VALUE;

		Usart_u8Status = USART_STATUS_NOT_PRESS;

		while(Loc_u8TryAgain == ONE_VALUE){
	        Loc_u8Check = ONE_VALUE;

			Loc_u8Password= ZERO_VALUE;
			Loc_u8RealPassword = ZERO_VALUE;
			Loc_u8Check = ONE_VALUE;

			Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter Username ID: ");

		while(Loc_u8Check != ZERO_VALUE){
			Loc_u8UsernameId=ZERO_VALUE;
			if(Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value>='0') && (Usart_u8Value<='9')){
				Loc_u8UsernameId = Usart_u8Value-'0';
				Usart_enuTransmitCharBlocking(&Usart1,  Usart_u8Value);
				Loc_u8Check = ZERO_VALUE;
				Usart_u8Status = USART_STATUS_NOT_PRESS;
			}

		}

		/* Password Part */
		Loc_u8Check = ONE_VALUE;

		Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter Password:\r");

		while(Loc_u8Check != ZERO_VALUE){

			if(Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value>='0') && (Usart_u8Value<='9')){
				Loc_u8Password = Loc_u8Password*10+ Usart_u8Value-'0';

				Usart_u8Status = USART_STATUS_NOT_PRESS;
			}
			else if (Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value=='\r')){
				ExternalEeprom_ReadByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8UsernameId, &Loc_u8RealPassword);

				if(Loc_u8RealPassword == Loc_u8Password){
					Loc_u8TryAgain = ZERO_VALUE;
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\r\rLogging In\r\r");
				}
				else{
					Usart_enuTransmitStringBlocking(&Usart1,(u8*)"\r\rWrong Password\r\r");
				}

				Loc_u8Check = ZERO_VALUE;
				Usart_u8Status = USART_STATUS_NOT_PRESS;



			}

		}

		}


		//////////////////////////////////////////////////////////////////////////////////////////////////////////



	for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<SEVEN_VALUE; Loc_u8Index++ ){
		Usart_enuTransmitStringBlocking(&Usart1, (u8*)UserListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]]);
		Usart_enuTransmitCharBlocking(&Usart1, '\r');
	}

	Loc_u8Check = ONE_VALUE;
	while(Loc_u8Check != ZERO_VALUE){

		if(Usart_u8Status == USART_STATUS_PRESS){


			Usart_u8Status = USART_STATUS_NOT_PRESS;
			switch(Usart_u8Value){

			case '1':


				if(AdminListStatus[ONE_VALUE] == ZERO_VALUE){
					Servo_enuSetAngle(180);
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rDoor Is Open\r");

					AdminListStatus[ONE_VALUE] = ONE_VALUE;
				}
				else {
					Servo_enuSetAngle(0);
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rDoor Is Closed\r");
					AdminListStatus[ONE_VALUE] = ZERO_VALUE;
				}
				break;


			case '2':


				if(AdminListStatus[TWO_VALUE] == ZERO_VALUE){
					SET_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom1 Is On\r");
					AdminListStatus[TWO_VALUE] = ONE_VALUE;
				}
				else {

					CLEAR_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom1 Is Off\r");
					AdminListStatus[TWO_VALUE] = ZERO_VALUE;
				}
				Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);


				break;

			case '3':

				if(AdminListStatus[THREE_VALUE] == ZERO_VALUE){
					SET_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom2 Is On\r");
					AdminListStatus[THREE_VALUE] = ONE_VALUE;
				}
				else {
					CLEAR_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom2 Is Off\r");
					AdminListStatus[THREE_VALUE] = ZERO_VALUE;
				}
				Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);

				break;
			case '4':

				if(AdminListStatus[FOUR_VALUE] == ZERO_VALUE){
					SET_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom3 Is On\r");
					AdminListStatus[FOUR_VALUE] = ONE_VALUE;
				}
				else {
					// Spi
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom3 Is Off\r");
					AdminListStatus[FOUR_VALUE] = ZERO_VALUE;
					CLEAR_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
				}
				Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);

				break;
			case '5': // show time

				Smart_ShowTimeUart();
				break;

			case '6':// Change Password
				MasterSmart_ChangePasswordUart(Loc_u8UsernameId,Loc_u8RealPassword);
				ExternalEeprom_ReadByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8UsernameId, &Loc_u8RealPassword);
				break;

			case '7':
				Loc_u8Check = ZERO_VALUE;
				return;
//			case '-':
//				Loc_u8CursorIndex = (Loc_u8CursorIndex-1)<1? 1 : Loc_u8CursorIndex-1;
//				Loc_u8Start = (Loc_u8Start-1)<1? 1 : Loc_u8Start-1;
////					if(Loc_u8Start == 3)
////						Loc_u8Start = 2;
//				break;
//			case '+':
//
//				Loc_u8CursorIndex = (Loc_u8CursorIndex+1)>4? 4 : Loc_u8CursorIndex+1;
//				Loc_u8Start = (Loc_u8Start+1)>4? 4 : Loc_u8Start+1;
//
//				break;

			default :
				break;

			}

			Loc_u8TempStart = Loc_u8Start;
			for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<SEVEN_VALUE; Loc_u8Index++ ){
				Usart_enuTransmitStringBlocking(&Usart1,  UserListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]]);
				Usart_enuTransmitCharBlocking(&Usart1, '\r');
			}


		}

	} // while

}
void Smart_UartAdminList(){
	/*
	 * 1- Open/Close The door
	 * 2- Turn On/ Turn Off Room1
	 * 3- Turn On/ Turn Off Room2
	 * 4- Turn On/ Turn Off Room3
	 * 5- show the time
	 * 6- Add User
	 * 7- Delete User
	 * 8- back to the main menu
	 */

		u8 Loc_u8Index = ZERO_VALUE;
		u8 Loc_u8Start = ONE_VALUE;
		u8 Loc_u8TempStart = ONE_VALUE;
		u8 Loc_u8Check = ONE_VALUE;
		u8 Loc_u8TempData = ZERO_VALUE ;
		Usart_u8Status = USART_STATUS_NOT_PRESS;


		for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<EIGHT_VALUE; Loc_u8Index++ ){
			Usart_enuTransmitStringBlocking(&Usart1, (u8*)AdminListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]]);
			Usart_enuTransmitCharBlocking(&Usart1, '\r');
		}


		while(Loc_u8Check != ZERO_VALUE){

			if(Usart_u8Status == USART_STATUS_PRESS){


				Usart_u8Status = USART_STATUS_NOT_PRESS;
				switch(Usart_u8Value){

				case '1':

					if(AdminListStatus[ONE_VALUE] == ZERO_VALUE){
						Servo_enuSetAngle(180);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rDoor Is Open\r");
						AdminListStatus[ONE_VALUE] = ONE_VALUE;
					}
					else {
						Servo_enuSetAngle(0);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rDoor Is Closed\r");
						AdminListStatus[ONE_VALUE] = ZERO_VALUE;
					}
					break;


				case '2':

					if(AdminListStatus[TWO_VALUE] == ZERO_VALUE){
						SET_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom1 Is On\r");
						AdminListStatus[TWO_VALUE] = ONE_VALUE;
					}
					else {

						CLEAR_BIT(MasterSmart_u8SlavePins,ZERO_VALUE);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom1 Is Off\r");
						AdminListStatus[TWO_VALUE] = ZERO_VALUE;
					}
					Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);

					break;

				case '3':

					if(AdminListStatus[THREE_VALUE] == ZERO_VALUE){
						SET_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom2 Is On\r");
						AdminListStatus[THREE_VALUE] = ONE_VALUE;
					}
					else {
						CLEAR_BIT(MasterSmart_u8SlavePins,ONE_VALUE);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom2 Is Off\r");
						AdminListStatus[THREE_VALUE] = ZERO_VALUE;
					}
					Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);

					break;
				case '4':

					if(AdminListStatus[FOUR_VALUE] == ZERO_VALUE){
						SET_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom3 Is On\r");
						AdminListStatus[FOUR_VALUE] = ONE_VALUE;
					}
					else {
						// Spi
						Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rRoom3 Is Off\r");
						AdminListStatus[FOUR_VALUE] = ZERO_VALUE;
						CLEAR_BIT(MasterSmart_u8SlavePins,TWO_VALUE);
					}
					Spi_enuTransmitBlocking(SPI_SLAVE_PIN, MasterSmart_u8SlavePins, &Loc_u8TempData);

					break;
				case '5': // show time

					Smart_ShowTimeUart();
					break;

				case '6':// add user
					Smart_AddUserUart();
					break;
				case '7': // delete user
					Smart_DeleteUserUart();
					break;
				case '8':
					Loc_u8Check = ZERO_VALUE;
					return;
//				case '-':
//					Loc_u8Start = (Loc_u8Start-1)<1? 1 : Loc_u8Start-1;
//
//					break;
//				case '+':
//
//					Loc_u8Start = (Loc_u8Start+1)>5? 5 : Loc_u8Start+1;
//
//					break;

				default :
					break;

				}

				Loc_u8TempStart = Loc_u8Start;

				for(Loc_u8Index = ZERO_VALUE;Loc_u8Index<EIGHT_VALUE; Loc_u8Index++ ){
					Usart_enuTransmitStringBlocking(&Usart1, AdminListArr[Loc_u8TempStart*TWO_VALUE-AdminListStatus[Loc_u8TempStart++]]);
					Usart_enuTransmitCharBlocking(&Usart1, '\r');
				}


			}

		}
}
void Smart_AddUserUart(){
		u8 Loc_u8Check = ONE_VALUE;
		u8 Loc_u8UsernameId;
		u8 Loc_u8Password= ZERO_VALUE;
		Usart_u8Status = USART_STATUS_NOT_PRESS;

		Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter Username ID: ");

		while(Loc_u8Check != ZERO_VALUE){

			if(Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value>='0') && (Usart_u8Value<='9')){
				Loc_u8UsernameId = Usart_u8Value-'0';
				Loc_u8Check = ZERO_VALUE;
				Usart_u8Status = USART_STATUS_NOT_PRESS;
			}

		}

		/* Password Part */
		Loc_u8Check = ONE_VALUE;

		Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter Password:\r");
		while(Loc_u8Check != ZERO_VALUE){

			if(Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value>='0') && (Usart_u8Value<='9')){
				Loc_u8Password = Loc_u8Password*10+ Usart_u8Value-'0';
				Usart_enuTransmitCharBlocking(&Usart1, '*');
				Usart_u8Status = USART_STATUS_NOT_PRESS;
			}
			else if (Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value=='\r')){
				ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, (u8)Loc_u8UsernameId, (u8)Loc_u8Password);

				Usart_enuTransmitStringBlocking(&Usart1,  (u8*)"\rUser ");
				Usart_enuTransmitCharBlocking(&Usart1, Loc_u8UsernameId+'0');
				Usart_enuTransmitStringBlocking(&Usart1,  (u8*)" Is Added \r\r");
				Usart_u8Status = USART_STATUS_NOT_PRESS;
				Loc_u8Check = ZERO_VALUE;



			}

		}

}
void Smart_DeleteUserUart(){
	u8 Loc_u8Check = ONE_VALUE;
	u8 Loc_u8UsernameId= NINE_VALUE;

	Usart_u8Status = USART_STATUS_NOT_PRESS;


	Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter Username ID: ");

	while(Loc_u8Check != ZERO_VALUE){

		if(Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value>='0') && (Usart_u8Value<='9')){
			Loc_u8UsernameId = Usart_u8Value-'0';
			Lcd_4bit_enuDisplayNumber(&Lcd, Usart_u8Value);
			Loc_u8Check = ZERO_VALUE;
			Usart_u8Status = USART_STATUS_NOT_PRESS;
		}

	}

	Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rUser ");
	Usart_enuTransmitCharBlocking(&Usart1, Loc_u8UsernameId+'0');
	Usart_enuTransmitStringBlocking(&Usart1, (u8*)" Is Deleted \r");

	ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8UsernameId, 0xFF);
}
void MasterSmart_ChangePasswordUart(u8 Loc_u8CopyUserId,u8 Loc_u8CopyUserPassword){
	u8 Loc_u8Check = ONE_VALUE;
		u8 Loc_u8Password = ZERO_VALUE;
		Usart_u8Status = USART_STATUS_NOT_PRESS;


		Usart_enuTransmitStringBlocking(&Usart1,  (u8*)"\rEnter Old Password: ");
		while(Loc_u8Check != ZERO_VALUE){

			if( Usart_u8Status== USART_STATUS_PRESS && (Usart_u8Value>='0') && (Usart_u8Value<='9')){
				Loc_u8Password = Loc_u8Password*10+ Usart_u8Value-'0';
				Usart_u8Status = USART_STATUS_NOT_PRESS;
			}
			else if (Usart_u8Status == USART_STATUS_PRESS && (Usart_u8Value=='\r')){

				if(Loc_u8CopyUserPassword == Loc_u8Password){
					Loc_u8Check = ZERO_VALUE;
				}

				else{
					Usart_enuTransmitStringBlocking(&Usart1,(u8*)"\r Wrong Password");
					Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rTry Again\r");
					Loc_u8Password = ZERO_VALUE;


					Usart_enuTransmitStringBlocking(&Usart1,  (u8*)"\rEnter Old Password: ");
				}



				Usart_u8Status = USART_STATUS_NOT_PRESS;



			}

		}

		/* Password Part */
		Loc_u8Check = ONE_VALUE;
		Loc_u8Password =ZERO_VALUE;
		Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rEnter New Password: ");
		while(Loc_u8Check != ZERO_VALUE){

			if( Usart_u8Status== USART_STATUS_PRESS && (Usart_u8Value>='0') && (Usart_u8Value<='9')){
				Loc_u8Password = Loc_u8Password*10+ Usart_u8Value-'0';
				Usart_u8Status = USART_STATUS_NOT_PRESS;
			}
			else if (Usart_u8Status== USART_STATUS_PRESS && (Usart_u8Value=='\r')){
				ExternalEeprom_WriteByte(EXTERNAL_EEPROM1_7BIT_ADDRESS, Loc_u8CopyUserId, Loc_u8Password);


				Usart_enuTransmitStringBlocking(&Usart1,(u8*)"\rChange is done\r ");

				Loc_u8Check = ZERO_VALUE;
				Usart_u8Status = USART_STATUS_NOT_PRESS;



			}

		}

}



void Smart_ShowTimeUart(){
	u8 Loc_u8Second =ZERO_VALUE;
	u8 Loc_u8Minute =ZERO_VALUE;
	u8 Loc_u8Hour =ZERO_VALUE;
	u8 Loc_u8Day =ZERO_VALUE;
	u8 Loc_u8Month =ZERO_VALUE;
	u8 Loc_u8Year =ZERO_VALUE;
	u32 Loc_u32Counter = ZERO_VALUE;

	u8 Loc_u8DayArr[5];
	u8 Loc_u8MonthArr[5];
	u8 Loc_u8YearArr[5];


	u8 Loc_u8SecondArr[5];
	u8 Loc_u8MinutesArr[5];
	u8 Loc_u8HoursArr[5];

	Usart_enuTransmitStringBlocking(&Usart1, (u8*)"\rDate:  ");


	Rtc_enuGetDay(&Loc_u8Day);
	Convert_IntToString(Loc_u8Day, Loc_u8DayArr);
	Usart_enuTransmitStringBlocking(&Usart1,Loc_u8DayArr);
	Usart_enuTransmitCharBlocking(&Usart1, ':');
	_delay_ms(150);


	Rtc_enuGetMonth(&Loc_u8Month);
	Convert_IntToString(Loc_u8Month, Loc_u8MonthArr);
	Usart_enuTransmitStringBlocking(&Usart1,Loc_u8MonthArr);
	Usart_enuTransmitCharBlocking(&Usart1, ':');
	_delay_ms(150);

	Rtc_enuGetYear(&Loc_u8Year);
	Convert_IntToString(Loc_u8Year, Loc_u8YearArr);
	Usart_enuTransmitStringBlocking(&Usart1,Loc_u8YearArr);
	_delay_ms(150);



	Usart_enuTransmitStringBlocking(&Usart1,(u8*)"\rClock:  ");

	// display for 3 seconds





	Rtc_enuGetHour(&Loc_u8Hour);
	Convert_IntToString(Loc_u8Hour, Loc_u8HoursArr);
	Usart_enuTransmitStringBlocking(&Usart1,Loc_u8HoursArr);
	Usart_enuTransmitCharBlocking(&Usart1, ':');

	_delay_ms(150);

	Rtc_enuGetMinute(&Loc_u8Minute);
	Convert_IntToString(Loc_u8Minute, Loc_u8MinutesArr);
	Usart_enuTransmitStringBlocking(&Usart1,Loc_u8MinutesArr);
	Usart_enuTransmitCharBlocking(&Usart1, ':');

	_delay_ms(150);



	Rtc_enuGetSecond(&Loc_u8Second);
	Convert_IntToString(Loc_u8Second, Loc_u8SecondArr);
	Usart_enuTransmitStringBlocking(&Usart1,Loc_u8SecondArr);
	Usart_enuTransmitCharBlocking(&Usart1, '\r');







}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ISR PART */
void smart_voidUartIsr(u16 Copy_u16ReceiveData){


		Usart_u8Value = Copy_u16ReceiveData;
		Usart_u8Status = USART_STATUS_PRESS;


}


void smart_voidTimer0Isr(void){
	static volatile u8 Loc_u8Counter = ZERO_VALUE;
	u8 Loc_u8TempRead;

	Loc_u8Counter++;
	if(18 == Loc_u8Counter){
		Dio_enuFlipChannel(DIO_PINA0_CHANNEL0);
		Keypad_Status = Keypad_enuRead(&Keypad, &Loc_u8TempRead);
		if(Keypad_Status == KEYPAD_IS_PRESSED)
			Keypad_u8Result = Loc_u8TempRead;

		Loc_u8Counter = ZERO_VALUE;
	}
}
