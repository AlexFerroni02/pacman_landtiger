/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "LPC17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/

void joystick_init(void) {
	/* joystick up functionality */
  LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.29)
	LPC_GPIO1->FIODIR   &= ~(1<<29);	//P1.25 Input (joysticks on PORT1 defined as Input)
	/* Configuration pin joystick (P1.29, P1.28, P1.27, P1.26) come GPIO */
   //LPC_PINCON->PINSEL3 &= ~((3 << 26) | (3 << 24) | (3 << 22) | (3 << 20)); 

    /* Configuration  pin like input */
   //LPC_GPIO1->FIODIR &= ~((1 << 29) | (1 << 28) | (1 << 27) | (1 << 26));
}
