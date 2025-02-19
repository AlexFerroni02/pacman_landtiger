/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../pacman.h"
#include "../schema.h"
#include "button_EXINT/button.h"
#include "music/music.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
// beat 1/4 = 1.65/4 seconds
#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1
NOTE pause_song[] = 
{
    // 1
    {c4, time_croma}, 
    {stop, time_semicroma},
    {e4, time_croma},
    {stop, time_semicroma},
    {g4, time_croma},
    {stop, time_croma},
    
    // 2
    {f4, time_semiminima},
    {d4, time_croma},
    {stop, time_semicroma},
    {c4, time_croma},
    {stop, time_croma},

    // 3
    {g3, time_croma},
    {a3, time_croma},
    {stop, time_croma},
    {f4, time_croma},
    
    // 4
    {c4, time_semiminima},
    {stop, time_croma},
    {e4, time_croma},
    {g4, time_semiminima},
    
    // 5
    {stop, time_minima},  // Pausa per conclusione effetto "transizione"
};

//SHORTENING UNDERTALE: TOO MANY REPETITIONS
NOTE song[] = 
{
	// 1
	{d3, time_semicroma},
	{d3, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{stop, time_semicroma},
	{a3b, time_semicroma},
	{stop, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 2
	{c3, time_semicroma},
	{c3, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{stop, time_semicroma},
	{a3b, time_semicroma},
	{stop, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 3
	{c3b, time_semicroma},
	{c3b, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{stop, time_semicroma},
	{a3b, time_semicroma},
	{stop, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 4
	{a2b, time_semicroma},
	{a2b, time_semicroma},
	{d4, time_croma},
	{a3, time_croma},
	{stop, time_semicroma},
	{a3b, time_semicroma},
	{stop, time_semicroma},
	{g3, time_croma},
	{f3, time_semicroma*2},
	{d3, time_semicroma},
	{f3, time_semicroma},
	{g3, time_semicroma},
	// 5
	
};


static int currentNote = 0;
static int currentNoteP =0;
void RIT_IRQHandler (void)
{
		// MUSIC

	// Verifica se la nota precedente è terminata
    if (!isNotePlaying() && !pause) {
        // Riproduce la nota corrente
        playNote(song[currentNote]);

        // Passa alla prossima nota
        currentNote = (currentNote + 1) % (sizeof(song) / sizeof(song[0])); // Loop continuo della canzone
    } // MUSIC for the pause
		else if(!isNotePlaying() && pause){
			playNote(pause_song[currentNoteP]);

        // Passa alla prossima nota
        currentNoteP = (currentNoteP + 1) % (sizeof(pause_song) / sizeof(pause_song[0])); // Loop continuo della canzone
		}
		
		
		// JOYSTICK
	if ((LPC_GPIO1->FIOPIN & (1<<29)) == 0) {  
        // Joytick UP pressed
        pacman.directionTemp = 'U';
				
    }
    if ((LPC_GPIO1->FIOPIN & (1<<28)) == 0) {  
        // Joytick R pressed
        pacman.directionTemp = 'R';

    }
    if ((LPC_GPIO1->FIOPIN & (1<<27)) == 0) {  
        // Joytick L pressed
        pacman.directionTemp = 'L';
		
    }
    if ((LPC_GPIO1->FIOPIN & (1<<26)) == 0) {  
        // Joytick D pressed
        pacman.directionTemp = 'D';
		
    }
		
		if(down>=1){
			if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ //EINT 0 pressed
				char str2[10];         

				switch (down){
					
					
					case	2: // we have the action at the first pressed we start the game, at the second we stop it
						if(pause ==1 ){ // we have to start for the start we have to activate the timer and disactivate it
							pause =0;
							char str3[10] = "     ";
							GUI_Text(100, 190, (uint8_t *)str3, Black, Black);
							enable_timer(0); // for the spawn of power pill
							enable_timer(1); // for the game over and for the movement
							
							
							
						}
						else{
							pause =1;
							char str3[10] = "PAUSE";
							GUI_Text(100, 190, (uint8_t *)str3, White, Black);
							
							disable_timer(0);
							disable_timer(1);
						  
							
						}
						
						break;
					default:
						break;
				
				}
				down++;
			}
			else{	// Button released
			
			down =0;
			NVIC_EnableIRQ(EINT0_IRQn);
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* GPIO pin selection */
		}
	}
		
	
		
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
