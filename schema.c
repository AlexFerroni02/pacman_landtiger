
#include "schema.h"



// Struttura del labirinto (2= empty space,1 = wall, 0 = pills, )
 uint8_t map[ROWS][COLS] = {
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
 {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
 {1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
 {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
 {1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1},
 {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
 {1, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 1, 1, 1},
 {2, 2, 2, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 2, 2, 2},
 {2, 2, 2, 1, 0, 0, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 0, 0, 0, 1, 2, 2, 2},
 {1, 1, 1, 1, 0, 0, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 0, 1, 1, 1, 1},
 {2, 2, 2, 2, 0, 0, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 0, 2, 2, 2, 2},
 {1, 1, 1, 1, 0, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 0, 0, 0, 1, 1, 1, 1},
 {2, 2, 2, 1, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0, 1, 2, 2, 2},
 {2, 2, 2, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 1, 2, 2, 2},
 {1, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 1, 1, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
 {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
 {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1},
 {1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1},
 {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1},
 {1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}	 
};
 
int placed = 0; 
void lose(){
	uint16_t row;
	uint16_t col;
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	disable_RIT();	
	LCD_Clear(Black);
	char str4[10] = "LOSE";
	GUI_Text(100, 190, (uint8_t *)str4, White, Black);

}


void victory(){
	uint16_t row;
	uint16_t col;
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	disable_RIT();	
	LCD_Clear(Black);
		char str4[10] = "VICTORY";
		GUI_Text(100, 190, (uint8_t *)str4, White, Black);

}

uint16_t cell_size = 10; // celle 10x10
// function to draw the map
void DrawLabyrinth() {
    
		uint8_t row;
		uint8_t col;
	  uint8_t count =0;
	// Margini superiori e inferiori
    uint16_t margin_top = 3 * cell_size;
    uint16_t margin_bottom = 2 * cell_size;
	// calculate the random power_Pill
		//placePowerPill();
    for (row = 0; row < ROWS; row++) {
        for ( col = 0; col < COLS; col++) {
					// Calcola le coordinate della cella
            uint16_t x0 = col * cell_size;
            uint16_t y0 = margin_top + row * cell_size;
            uint16_t x1 = x0 + cell_size;
            uint16_t y1 = y0 + cell_size;
					  uint16_t dot_x = x0 + cell_size / 2;
            uint16_t dot_y = y0 + cell_size / 2;
            if (map[row][col] == 1) {

               // colora la cella 10x10 del muro
							uint16_t x, y;
						for (y = y0; y < y1; y++) {
								for (x = x0; x < x1; x++) {
									LCD_SetPoint(x, y, Blue); // Imposta il pixel su "Blue"
									}
								}
            }// standard Pill
						else if(map[row][col] == 0){
							if (count < 240){
								
								//GUI_Text(dot_x,  dot_y, (uint8_t *) " . ", White, Black);
							  LCD_SetPoint(dot_x,dot_y,White);
							  count +=1;
							}
						}
						// Power Pill
						else if(map[row][col] == 3){
							uint16_t i;
							uint16_t j ;
							for (j = dot_x-1; j <= dot_x+1; j++) {
								for (i = dot_y-1; i <= dot_y+1; i++) {
									LCD_SetPoint(j, i, White); 
									}
								}
						}
        }
    }
		// per stampare un valore
		char str[10] = "score:";         
   
    GUI_Text(150, 10, (uint8_t *)str, White, Black);  // Passa la stringa a GUI_Text
		//countdown
		char str3[20] = "Game over in:";
		GUI_Text(5, 10, (uint8_t *)str3, White, Black);
		char str2[10];         
    sprintf(str2, "%d", countdown);
		GUI_Text(110, 10, (uint8_t *)str2, White, Black);
		
		char str4[10] = "PAUSE";
		GUI_Text(100, 190, (uint8_t *)str4, White, Black);
		
		DrawPacman(pacman.x,pacman.y,pacman.radius,pacman.color,pacman.startAngle ,pacman.endAngle);
		DrawPacman(x_vita,y_vita,pacman.radius,pacman.color,pacman.startAngle ,pacman.endAngle);
		DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);

		
}


void placePowerPill() {
	
    int placed = 0; 
		srand(pacman.pills_eat);
    while (placed < POWER_PILL) {
        int r = rand() % ROWS; 
        int c = rand() % COLS; 

        if (map[r][c] == 0 && map[r][c]!=3) { // Controlla se è un pallino normale
            map[r][c] = 3; // Imposta il pallino speciale
            placed++;
							uint16_t i;
							uint16_t j ;
							uint16_t dot_x = c * cell_size + cell_size / 2;
							uint16_t dot_y = 30+r * cell_size + cell_size / 2;
							for (j = dot_x-1; j <= dot_x+1; j++) {
								for (i = dot_y-1; i <= dot_y+1; i++) {
									LCD_SetPoint(j, i, White); 
									}
								}
        }
    }
}

void placePowerPill2() {
	

		srand(pacman.pills_eat);
    if(placed < POWER_PILL) {
			int r,c;
			do{ // find the right pills
				 r = rand() % ROWS; 
         c = rand() % COLS; 
			}while (map[r][c] != 0 || map[r][c] == 3);
			
      map[r][c] = 3; // Imposta il pallino speciale
      placed++;
			uint16_t i;
			uint16_t j ;
			uint16_t dot_x = c * cell_size + cell_size / 2;
			uint16_t dot_y = 30+r * cell_size + cell_size / 2;
			for (j = dot_x-1; j <= dot_x+1; j++) {
				for (i = dot_y-1; i <= dot_y+1; i++) {
					LCD_SetPoint(j, i, White); 
					}							
       }
			int timeInterval = (rand() % 5)+1;
			init_timer(0, 25000000*timeInterval);
			 
    }
		else{
			disable_timer(0);
		}
}