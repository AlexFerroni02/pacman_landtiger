#include "pacman.h"
#include <stdio.h>

// INitialize the variable pacman
volatile Pacman pacman = { 
    .x = 115,           // Initial position X
    .y = 245,           // Initial position Y
    .radius = 4,        // Dimensione iniziale
    .color = Yellow,
		.startAngle = 135,
		.endAngle = 225,
		.direction = 'S',        //at the start is in the stop position
		.directionTemp = 'S',
		.score = 0,
		.lives = 1,
		.pills_eat = 0,
		.lives_lose = 0,
	  .viterimaste =1
};
uint16_t x_vita = 5;
uint16_t y_vita = 310;
int countdown = 60;
int precScore =0;
volatile int dotSoundIndex = -1; // -1 significa che la musica è attiva
int checkMove(){
	
	// do the check if- only if we are at the center 
	if((pacman.x%5==0 && !(pacman.x%10 ==0))&& (pacman.y%5==0 && !(pacman.y%10 ==0))) {
		if(pacman.direction!=pacman.directionTemp){
			pacman.direction=pacman.directionTemp;
		}
		int i = (pacman.y-30)/10; // we have to subtract 30 because our matrix start under 30 pixel
		int j = (pacman.x)/10;
		 
		if( pacman.direction == 'U'){
			if(map[i-1][j] ==1){
					return 1; // there is a wall
				}
		}
		else if( pacman.direction == 'R'){
			if(map[i][j+1] ==1){
					return 1; // there is a wall
				}
		}
		else if( pacman.direction == 'L'){
			if(map[i][j-1] ==1){
					return 1; // there is a wall
				}
		}
		else if( pacman.direction == 'D'){
			if(map[i+1][j] ==1){
					return 1; // there is a wall
				}
		}
		
	}
	return 0;
}
NOTE dotsound ={789,time_croma};       // 700Hz k = 789
void movePacman() {
	
		if(checkMove()){
			return;
		}
	
		int i = (pacman.y-30)/10; // we have to subtract 30 because our matrix start under 30 pixel
		int j = (pacman.x)/10;
		switch (pacman.direction){
			case 'U':
				ErasePacmanOverflow(pacman.x, pacman.y, pacman.x, pacman.y -1, pacman.radius);
				pacman.y = pacman.y -1;
				DrawPacman(pacman.x,pacman.y,pacman.radius,pacman.color,45 ,135);
				
				break;
				
			case 'R':
				if(j+1 == 24){ //we teleport
						ErasePacman(pacman.x,pacman.y,pacman.radius);
						pacman.x = 5;
						DrawPacmanD(pacman.x,pacman.y,pacman.radius,pacman.color,45 ,315);
				}
				else{
				ErasePacmanOverflow(pacman.x, pacman.y, pacman.x+1, pacman.y , pacman.radius);
				pacman.x = pacman.x +1;
				DrawPacmanD(pacman.x,pacman.y,pacman.radius,pacman.color,45 ,315);
				
				}
				break;
				
			case 'L':
				if(j-1 == -1){ // teleport
						ErasePacman(pacman.x,pacman.y,pacman.radius);
						pacman.x = 235;
						DrawPacman(pacman.x,pacman.y,pacman.radius,pacman.color,pacman.startAngle ,pacman.endAngle);
						
					}
					else{
						ErasePacmanOverflow(pacman.x, pacman.y, pacman.x-1, pacman.y , pacman.radius);
						pacman.x = pacman.x -1;
						DrawPacman(pacman.x,pacman.y,pacman.radius,pacman.color,pacman.startAngle ,pacman.endAngle);
						
					}
					break;
					
			case 'D':
				ErasePacmanOverflow(pacman.x, pacman.y, pacman.x, pacman.y+1 , pacman.radius);
				pacman.y = pacman.y +1;
				DrawPacman(pacman.x,pacman.y,pacman.radius,pacman.color,225 ,315);
				
				break;
		}
		if(map[i][j] == 0){
			pacman.score += 10;
			pacman.pills_eat +=1;
			map[i][j] = 2;
			playNote(dotsound);
		}
		else if (map[i][j] == 3){
			pacman.score += 50;
			pacman.pills_eat +=1;
			map[i][j] = 2;
			blinky.chase = 0;
			blinky.timemod =0;
			playNote(dotsound);
		}
		if(pacman.score  >= pacman.lives *1000){
			pacman.lives +=1;
			pacman.viterimaste +=1;
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
		if(countdown !=0){
			/*char str[10]; 
			
			sprintf(str, "%d", pacman.score);  
  
			GUI_Text(200, 10, (uint8_t *)str, White, Black);*/
			if (pacman.score != precScore) {  
					precScore = pacman.score;

					// Prepara il messaggio con il punteggio
          CAN_TxMsg.data[0] = countdown & 0xFF;				
					CAN_TxMsg.data[1] = pacman.viterimaste & 0xFF;
					CAN_TxMsg.data[2] = (pacman.score >> 8) & 0xFF; // save the 16 bit score 
					CAN_TxMsg.data[3] = pacman.score & 0xFF;  // Byte meno significativo

					CAN_TxMsg.len = 4;  // Lunghezza del messaggio in byte
					CAN_TxMsg.id = 2;   // ID del messaggio (CAN 1)
					CAN_TxMsg.format = STANDARD_FORMAT;  
					CAN_TxMsg.type = DATA_FRAME;  

					CAN_wrMsg(1, &CAN_TxMsg);  // Invia il messaggio tramite CAN 1
			}
		}
			
		
		return;
		
}



void DrawPacman(int x0, int y0, int radius, uint16_t color,float startAngle, float endAngle) {
    int x, y;

    for (y = -radius; y <= radius; y++) { 
        for (x = -radius; x <= radius; x++) { 
            //circle equation if a point is in the circlo the write
					if (x * x + y * y <= radius * radius) {
								float angle = atan2f(-y, x) * 180 / M_PI; // Angolo in gradi
                if (angle < 0) {
									angle += 360; // Porta l'angolo tra 0 e 360 gradi
								}
                // Draw the point out of the interval
                if (!(angle >= startAngle && angle <= endAngle)) {
                    LCD_SetPoint(x0 + x, y0 + y, color); // Corpo del Pacman
                }
							
						}
				}  
		}
}

void DrawPacmanD(int x0, int y0, int radius, uint16_t color,float startAngle, float endAngle) {
    int x, y;

    for (y = -radius; y <= radius; y++) { 
        for (x = -radius; x <= radius; x++) { 
            //circle equation if a point is in the circlo the write
					if (x * x + y * y <= radius * radius) {
								float angle = atan2f(-y, x) * 180 / M_PI; // Angolo in gradi
                if (angle < 0) {
									angle += 360; // Porta l'angolo tra 0 e 360 gradi
								}
                // Draw the point out of the interval
                if ((angle >= startAngle && angle <= endAngle)) {
                    LCD_SetPoint(x0 + x, y0 + y, color); // Corpo del Pacman
                }
						}
				}  
		}
}


void ErasePacman(int x0, int y0, int radius) {
	
    int x, y;

    for (y = -radius; y <= radius; y++) { 
        for (x = -radius; x <= radius; x++) { 
            //circle equation if a point is in the circlo the write
            if (x * x + y * y <= radius * radius) {
                LCD_SetPoint(x0 + x, y0 + y, Black); 
            }
        }
    }  
}
void ErasePacmanOverflow(int x0_old, int y0_old, int x0_new, int y0_new, int radius) {
    int x, y;

    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            // Pixel sulla circonferenza esterna del cerchio vecchio
            int dist_old = x * x + y * y;
            int dist_new = (x + (x0_old - x0_new)) * (x + (x0_old - x0_new)) + 
                           (y + (y0_old - y0_new)) * (y + (y0_old - y0_new));
            
            if (dist_old <= radius * radius && dist_new > radius * radius) {
                // Cancella solo i pixel che appartenevano al vecchio cerchio ma non al nuovo
                LCD_SetPoint(x0_old + x, y0_old + y, Black);
            }
        }
    }
}

void DrawPacmanNewPart(int x0_old, int y0_old, int x0_new, int y0_new, int radius, int color) {
    int x, y;

    for (y = -radius; y <= radius; y++) {
        for (x = -radius; x <= radius; x++) {
            // Pixel sulla circonferenza esterna del cerchio nuovo
            int dist_old = (x + (x0_new - x0_old)) * (x + (x0_new - x0_old)) +
                           (y + (y0_new - y0_old)) * (y + (y0_new - y0_old));
            int dist_new = x * x + y * y;

            if (dist_new <= radius * radius && dist_old > radius * radius) {
                // Disegna solo i pixel che appartengono al nuovo cerchio ma non al vecchio
                LCD_SetPoint(x0_new + x, y0_new + y, color);
            }
        }
    }
}

