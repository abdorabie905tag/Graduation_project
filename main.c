

/*
 * main.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Abdelrhman
 */
#include "LSTD_Types.h"
#include "LUTILS.h"
#include "LMath_Interface.h"
#include "LDELAY_Interface.h"
#include"MDIO_Interface.h"
#include"MADC_Interface.h"
#include"MTIMER0_interface.h"
#include"TIMER1_interface.h"
#include"HLCD_Interface.h"
#include"MUART_interface.h"
#include"avr/delay.h"
// variabl for number of space available for car
u8 c1=0;//,c2=0,c3=0,c4=0;
// var to number of space
u8 slot=4;
// init var to IR sensor value front & back
u8 val_A1=0;
u8 val_A2=0;
// init var to IR sensor value slot
u8 val_A3=0;
u8 val_c1=0;
//u8 val_c2=0;
//u8 val_c3=0;
//u8 val_c4=0;
/// arr to save message to convert integer to string
//char message[10];
// var to save value of UART
u8 resUart;
// two var use as a flage
u8 f1=0;
u8 f2=0;
void Read_sensor_cars();
void Display_LCD();
// front of gate
void front();
// back of gate
void back();

//void ISR();

void main()
{
		// inti TIMER0
		//MTIMER0_voidInitializeTimer0;

		// inti LCD
		HLCD_voidInitializeLCD();
		// inti servo
		TIMER1_voidSERVO_init();
		// init uart
		MUART_voidInitializeUART();
		//// servo PIN
		MDIO_u8SetDirectionBit(MDIO_PORTD,5,1);


		//// IR front 1 PIN
		MDIO_u8SetDirectionBit(MDIO_PORTB,0,0);
		//// IR back 2 PIN
		MDIO_u8SetDirectionBit(MDIO_PORTB,1,0);


		//// flame sensor PIN fire
		MDIO_u8SetDirectionBit(MDIO_PORTB,2,0);
		//// IR car 1 PIN
		MDIO_u8SetDirectionBit(MDIO_PORTB,3,0);
		//// IR car 2 PIN
//		MDIO_u8SetDirectionBit(MDIO_PORTB,4,0);
//		//// IR car 3 PIN
//		MDIO_u8SetDirectionBit(MDIO_PORTB,5,0);
//		//// IR car 4 PIN
//		MDIO_u8SetDirectionBit(MDIO_PORTB,6,0);






	/***********************LCD PRINT ***************************/

		HLCD_voidSetCursorPosition(HLCD_LINE1,1);
		HLCD_voidDisplayString("Car Parking",HLCD_STRING);
		HLCD_voidSetCursorPosition(HLCD_LINE2,1);
		HLCD_voidDisplayString("System",HLCD_STRING);
		_delay_ms(2000);
		HLCD_voidClearLCD();
		HLCD_voidCursorBlinkOnOff(HLCD_OFF);
		HLCD_voidCursorDisplayOnOff(HLCD_OFF);
		servo(1500);
		Read_sensor_cars();
		u8 total=c1;//+c2+c3+c4;
		slot=slot-total;
//		MTIMER0_voidOverFlowCallBack(ISR);
//		MTIMER0_voidSetDesiredTime_ms(1000);

	while(1)
	{
		// val of fire sensor
		val_A3= MDIO_u8ReadBit(MDIO_PORTB,2);

		 Display_LCD();

		 MUART_voidSendByteSynch('\r');
		 MUART_voidSendByteSynch('\n');
		 if(slot==4){
			 MUART_voidSendByteSynch('4');
		 }
		 if(slot==3){
			 MUART_voidSendByteSynch('3');
		 }
		 if(slot==2){
			 MUART_voidSendByteSynch('2');
		 }
		 if(slot==1){
			 MUART_voidSendByteSynch('1');
		 }
		 if(slot==0){
			 MUART_voidSendByteSynch('0');
		 }

/****************************************************************************/
			/**************** IR FRONT ***********************/
			val_A1= MDIO_u8ReadBit(MDIO_PORTB,0);
			/**************** IR BACK ***********************/
			val_A2= MDIO_u8ReadBit(MDIO_PORTB,1);
			if(0==val_A1)
					 {
						 f1=1;
					    front();

					 }
			if(0==val_A2)
					 {
						 f2=1;
					    back();

					 }

					if(f1==1 && f2==1)
					{
						//close servo
							 servo(1500);
							 f1=0;
							 f2=0;
					}

		//fire
//		if(0==val_A3)
//		{
//			//MDIO_u8WriteBit(MDIO_PORTB,5,1); //led
//			HLCD_voidClearLCD();
//			HLCD_voidSetCursorPosition(HLCD_LINE1,1);
//			HLCD_voidDisplayString("FIRE..",HLCD_STRING);
//			_delay_ms(2000);
//
//		}


	}

}
void Read_sensor_cars()
{
	c1=0;//,c2=0,c3=0,c4=0;
	val_c1= MDIO_u8ReadBit(MDIO_PORTB,3);
//	val_c2= MDIO_u8ReadBit(MDIO_PORTB,4);
//	val_c3= MDIO_u8ReadBit(MDIO_PORTB,5);
//	val_c4= MDIO_u8ReadBit(MDIO_PORTB,6);

	if(0==val_c1){c1=1;}
//	if(0==val_c2){c2=1;}
//	if(0==val_c3){c3=1;}
//	if(0==val_c4){c4=1;}


}
void Display_LCD()
{
	Read_sensor_cars();
	HLCD_voidSetCursorPosition(HLCD_LINE1,1);
	HLCD_voidDisplayString(" Have Slot: ",HLCD_STRING);
	HLCD_voidSetCursorPosition(HLCD_LINE1,13);
	LCD_voidSendNumber(slot);
	HLCD_voidSetCursorPosition(HLCD_LINE2,1);
	if(c1==1)
	{
		HLCD_voidDisplayString("1:F ",HLCD_STRING);
	}
	else {
		HLCD_voidDisplayString("1:E ",HLCD_STRING);
	}
//	HLCD_voidSetCursorPosition(HLCD_LINE2,5);
//	if(c2==1)
//	{
//		HLCD_voidDisplayString("2:F ",HLCD_STRING);
//	}
//	else {
//		HLCD_voidDisplayString("2:E ",HLCD_STRING);
//	}
//	HLCD_voidSetCursorPosition(HLCD_LINE2,9);
//	if(c3==1)
//		{
//			HLCD_voidDisplayString("3:F ",HLCD_STRING);
//		}
//		else {
//			HLCD_voidDisplayString("3:E ",HLCD_STRING);
//		}
//		HLCD_voidSetCursorPosition(HLCD_LINE2,13);
//		if(c4==1)
//		{
//			HLCD_voidDisplayString("4:F ",HLCD_STRING);
//		}
//		else {
//			HLCD_voidDisplayString("4:E",HLCD_STRING);
//		}
}
void front()
{

		if(slot>0)
		{
			// send message to NODEMCU to open camera and detect the car and open servo <income>
			MUART_voidSendByteSynch('\r');
			MUART_voidSendByteSynch('\n');
			_delay_ms(10);
			MUART_voidSendByteSynch('o');
			    resUart=MUART_voidRecieveByteSynch(1000);
				if(resUart=='z')
				{
					servo(600);
					slot = slot-1;
				}


		}
		else
		{
			HLCD_voidClearLCD();
			HLCD_voidSetCursorPosition(HLCD_LINE1,1);
			HLCD_voidDisplayString("parking full",HLCD_STRING);
			_delay_ms(2000);
			HLCD_voidClearLCD();
		}


}
void back()
{

		if(slot<4)
		{
			// send message to NODEMCU to open camera and detect the car and open servo <get out>
			MUART_voidSendByteSynch('\r');
			MUART_voidSendByteSynch('\n');
			_delay_ms(10);
			MUART_voidSendByteSynch('c');

			    resUart=MUART_voidRecieveByteSynch(1000);
				if(resUart=='b')
				{
					servo(600);
					slot = slot+1;
				}


		}
		else
		{
			HLCD_voidClearLCD();
			HLCD_voidSetCursorPosition(HLCD_LINE1,1);
			HLCD_voidDisplayString("parking empty",HLCD_STRING);
			_delay_ms(2000);
			HLCD_voidClearLCD();
		}


}
//void ISR(){
//	/**************** IR FRONT ***********************/
//	val_A1= MDIO_u8ReadBit(MDIO_PORTB,0);
//	/**************** IR BACK ***********************/
//	val_A2= MDIO_u8ReadBit(MDIO_PORTB,1);
//	if(0==val_A1)
//			 {
//				 f1=1;
//			    front();
//
//			 }
//	if(0==val_A2)
//			 {
//				 f2=1;
//			    back();
//
//			 }
//
//			if(f1==1 && f2==1)
//			{
//				//close servo
//					 servo(1500);
//					 f1=0;
//					 f2=0;
//			}
//}
