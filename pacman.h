#ifndef PACMAN_H
#define PACMAN_H

#include "LPC17xx.h"
#include <stdio.h>
#include "GLCD/GLCD.h" 
#include <math.h>
#define M_PI 3.14159265358979323846
#include "schema.h"
#include "music/music.h"
#include "CAN/CAN.h"


typedef struct {
    int x;       // Coordinata X
    int y;       // Coordinata Y
    int radius;    // Dimensione del Pacman
    uint16_t color;   // Colore del Pacman
		float startAngle;
		float endAngle;
	  char direction;
	  char directionTemp;
		uint16_t score;
		int lives;
		int pills_eat;
	  int lives_lose;
	  uint8_t viterimaste;
} Pacman;
extern uint16_t x_vita;
extern uint16_t y_vita;
extern volatile Pacman pacman;

extern int countdown;
void DrawPacman(int x0, int y0, int radius, uint16_t color,float startAngle, float endAngle);
void DrawPacmanD(int x0, int y0, int radius, uint16_t color,float startAngle, float endAngle);
void ErasePacman(int x0, int y0, int radius);
void movePacman();
int checkMove();
void ErasePacmanOverflow(int x0_old, int y0_old, int x0_new, int y0_new, int radius);
void DrawPacmanNewPart(int x0_old, int y0_old, int x0_new, int y0_new, int radius, int color);
#endif 