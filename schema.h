#ifndef SCHEMA_H
#define SCHEMA_H

#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../pacman.h"
#include "../blinky.h"

#define ROWS 27
#define COLS 24
#define POWER_PILL 6
extern uint8_t map[ROWS][COLS];

// function
void DrawLabyrinth(void);
void placePowerPill(void);
void LCD_DrawSquare(uint16_t dot_x, uint16_t dot_y, uint16_t color);
void lose();
void victory();
void placePowerPill2();
#endif // SCHEMA_H




