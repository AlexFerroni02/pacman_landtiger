/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.h>                  /* LPC17xx definitions */
#include "CAN.h"                      /* LPC17xx CAN adaption layer */
#include "../GLCD/GLCD.h"

extern uint8_t icr ; 										//icr and result must be global in order to work with both real and simulated landtiger.
extern uint32_t result;
extern CAN_msg       CAN_TxMsg;    /* CAN message for sending */
extern CAN_msg       CAN_RxMsg;    /* CAN message for receiving */                                

static int puntiRicevuti1 = 0;
static int puntiInviati1 = 0;

static int puntiRicevuti2 = 0;
static int puntiInviati2 = 0;

uint16_t val_RxCoordX = 0;            /* Locals used for display */
uint16_t val_RxCoordY = 0;

/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
void CAN_IRQHandler (void)  {

  /* check CAN controller 1 */
	icr = 0;
  icr = (LPC_CAN1->ICR | icr) & 0xFF;               /* clear interrupts */
	
  if (icr & (1 << 0)) {                          		/* CAN Controller #1 meassage is received */
		
		
		puntiRicevuti1++;
  }
	if (icr & (1 << 1)) {                         /* CAN Controller #1 meassage is transmitted */
		// do nothing in this example
		puntiInviati1++;
	}
		
	/* check CAN controller 2 */
	icr = 0;
	icr = (LPC_CAN2->ICR | icr) & 0xFF;             /* clear interrupts */

	if (icr & (1 << 0)) {                          	/* CAN Controller #2 meassage is received */
		CAN_rdMsg(2, &CAN_RxMsg);  // Leggi il messaggio ricevuto da CAN 2
		LPC_CAN2->CMR = (1 << 2);                    		/* Release receive buffer */

    static int receivedScore = 0;
		static int pacmanlives = 1;
		static int countdownd = 60;
		int new_countdown = CAN_RxMsg.data[0];
		int new_remainingsLives = CAN_RxMsg.data[1];
		        // Ricostruisci il punteggio dal messaggio
    int new_receivedScore = (CAN_RxMsg.data[2] << 8) | 
                (CAN_RxMsg.data[3]);
		
		if(countdownd != new_countdown){
			countdownd=new_countdown;
			char str3[10];         
			sprintf(str3, "%d ", countdown);
			GUI_Text(110, 10, (uint8_t *)str3, White, Black);
		}
		if (new_remainingsLives > pacmanlives) {
				pacmanlives = new_remainingsLives;
				x_vita += 10;
				DrawPacman(x_vita, y_vita, pacman.radius, pacman.color, pacman.startAngle, pacman.endAngle);
		} else if (new_remainingsLives < pacmanlives) {
				pacmanlives = new_remainingsLives;
				ErasePacman(x_vita, y_vita, pacman.radius);
				x_vita -= 10;
		}
			
		
    
	 if(new_receivedScore != receivedScore){
		 receivedScore = new_receivedScore;
		 
		 char str[10]; 
			
		sprintf(str, "%d", receivedScore);  
  
		GUI_Text(200, 10, (uint8_t *)str, White, Black);
	 }
            
		
		 
		
		puntiRicevuti2++;
	}
	if (icr & (1 << 1)) {                         /* CAN Controller #2 meassage is transmitted */
		// do nothing in this example
		puntiInviati2++;
	}
}
