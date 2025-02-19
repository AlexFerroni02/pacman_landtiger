/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "../schema.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include <stdio.h>
#include <stdlib.h>
#include "button_EXINT/button.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
int pause =1;

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	CAN_Init();
	LCD_Initialization();
	LCD_Clear(Black);
	DrawLabyrinth();
	BUTTON_init();
	joystick_init();

	int timeInterval = (rand() % 10)+1;
	init_timer(0, 25000000*timeInterval);
	
	//init_timer(2,25000000/blinky.speed);
	//init_timer(1,0x17D7840); // 1 sec, il timer per il game-Over
	//init_timer(2, 0x65B9A);	//60Hz
	//init_timer(2, 0x57316);// 70Hz
	//init_timer(1, 0x4C4B4);		//80Hz for the movement of pacman and countdown
	init_timer(1, 0x61A8);  // 1ms
	//init_timer(2, 0x161A8); 
	//init_timer(2, 0x1E848);//200Hz			// for the movement
	//init_timer(2, 0xC350);// 500 Hz
	init_RIT(0x0004C4B4);									/* RIT Initialization 50 msec  sarebbero con lo 0 alla fine*/
	enable_RIT();													/* RIT enabled	*/	
	
	
  
	
	
	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */ 
	//init_timer(0, 0x6108 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	//init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */
 
					
	

	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);			
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
