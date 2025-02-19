#ifndef BLINKY_H
#define BLINKY_H



#include "LPC17xx.h"
#include <stdio.h>
#include "GLCD/GLCD.h" 
#include "../pacman.h"
#include "/music/music.h"


typedef struct{
		int x;       // Coordinata X
    int y;       // Coordinata Y
    int radius;    // Dimensione del Pacman
    uint16_t color;   // Colore del Pacman
	  char direction;
	  char directionTemp;
		int chase;
		int eaten;
		int respawn;
		int timemod;
		int speed;
}Blinky;

extern Blinky blinky;

void DrawBlinky(int x0, int y0, int radius, uint16_t color);
void CheckHitBox(int xb, int yb, int radiusB,int xp, int yp, int radiusp);
void MoveBlinky();
int ManhattanDistance(int x1, int y1, int x2, int y2);
int back(char bdir,char scelta);
void EraseBlinkyOverflow(int x0_old, int y0_old, int x0_new, int y0_new, int size);

#endif 