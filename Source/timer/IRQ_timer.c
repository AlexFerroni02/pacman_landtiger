/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include <stdio.h> /*for sprintf*/
#include "../pacman.h"
#include "../schema.h"
#include "music/music.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};
int contatore =0;
void TIMER0_IRQHandler (void) // use for random pills
{
	placePowerPill2();
	LPC_TIM0->IR = 1;			/* clear interrupt flag */

  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
// Variabili globali
volatile int pacman_counter = 0;  // Contatore per Pac-Man
volatile int blinky_counter = 0;  // Contatore per Blinky
volatile int second_counter = 0;  // Contatore per i secondi
volatile int blinky_interval = 18; // Intervallo iniziale per Blinky (es. 15 ms) 66Hz
void TIMER1_IRQHandler (void) // use for countdown
{
	
	pacman_counter++;
  blinky_counter++;
  second_counter++;

	if(pacman.pills_eat== 240){	
		victory();
	}
	else{
		 
    if (pacman_counter >= 14) { // 14 ms approssima 70 Hz
        movePacman();
        pacman_counter = 0;
    }
		
		// Movimento di Blinky
    if (blinky_counter >= blinky_interval) {
        if(!blinky.eaten){
					MoveBlinky();
				}
        blinky_counter = 0;
    }
		// Aggiornamento del tempo (ogni 1 secondo)
    if (second_counter >= 780) { // 780ms because there is latency so 1 seconds in 1 seconds in real life if we stay 
        second_counter = 0;
        countdown--;
			  
        if (countdown % 10 == 0) { // Velocità di Blinky aumenta ogni 10 secondi
            blinky_interval =  blinky_interval - 1;
        }
				// check the respawn
				if(blinky.eaten){
						blinky.respawn ++;
						if(blinky.respawn ==3){
							blinky.x = 115;
							blinky.y =165;
							DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);
							blinky.eaten =0;
							blinky.chase = 1;
						}
				}
				// check the mode
				if(!blinky.chase){
					blinky.timemod ++;
					if(blinky.timemod ==10){
						blinky.chase =1;
					}
				}
				// check the end
        if (countdown == 0) {
            lose();
        }
				else{
						//int x,y;
					  CAN_TxMsg.data[0] = countdown & 0xFF;
					  CAN_TxMsg.data[1] = pacman.viterimaste & 0xFF;
					  CAN_TxMsg.data[2] = (pacman.score >> 8) & 0xFF; // save the 16 bit score 
					  CAN_TxMsg.data[3] = pacman.score & 0xFF;  // Byte meno significativo
			      CAN_TxMsg.len = 4;  // Lunghezza del messaggio in byte
				    CAN_TxMsg.id = 2;   
				    CAN_TxMsg.format = STANDARD_FORMAT;  
				    CAN_TxMsg.type = DATA_FRAME;  

				    CAN_wrMsg(1, &CAN_TxMsg);  // Invia il messaggio tramite CAN 1
						
					}
    }
		
	} 
	
	
	
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{	
	static int ticks = 0; // because is static is initiated only the first time, for the rest call of the handler has the previous Value
	// DAC management: invio del dato al DAC
	static int currentValue;
         // Suono del pallino
	currentValue = SinTable[ticks];
  ticks ++; // Aumenta la frequenza per un suono più acuto
				
  if (ticks >= 45) ticks = 0;
   
	
	
  LPC_DAC->DACR = (currentValue << 6);  // Scrittura nel registro del DAC
  
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;

}
void TIMER3_IRQHandler (void)
{
	disable_timer(2);

	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
