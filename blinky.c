
#include "blinky.h"

Blinky blinky={
		.x =115,
		.y =165,
		.radius = 4,        // Dimensione iniziale
    .color = Red,
		.direction = 'S',        //at the start is in the stop position
		.directionTemp = 'S',
		.chase =1,
		.eaten = 0,  // use with the timer that make it move
		.respawn =0
};

NOTE hitboxsound ={e4,time_semiminima};   // 330Hz
char directions[4] = {'U', 'R', 'L', 'D'};

void DrawBlinky(int x0, int y0, int radius, uint16_t color){
		int x, y;
		for (y = -radius; y <= radius; y++) { 
        for (x = -radius; x <= radius; x++) {
					if(blinky.chase){
						LCD_SetPoint(x0 + x, y0 + y, color);
					}
					else{
						LCD_SetPoint(x0 + x, y0 + y, Blue2);
					}
       
				}  
		}
}
void EraseBlinky(int x0, int y0, int radius, uint16_t color){
		int x, y;
		for (y = -radius; y <= radius; y++) { 
        for (x = -radius; x <= radius; x++) { 
					LCD_SetPoint(x0 + x, y0 + y, color);
       
				}  
		}
}


void CheckHitBox(int xb, int yb, int radiusB,int xp, int yp, int radiusp){

	int dx = xp-xb;
	int dy = yb-yp;
	int distance_squared = dx * dx + dy * dy;
	int radius_sum = radiusp + radiusB;
  int radius_sum_squared = radius_sum * radius_sum;
	if (distance_squared <= radius_sum_squared) {
		  playNote(hitboxsound);
			if(blinky.chase){
					 pacman.lives_lose += 1;
				   pacman.viterimaste -=1;
					 ErasePacman(pacman.x,pacman.y,pacman.radius);
					 pacman.x =115;
					 pacman.y =245;
					 
					 CAN_TxMsg.data[1] = pacman.viterimaste & 0xFF;
			     CAN_TxMsg.len = 4;  // Lunghezza del messaggio in byte
					CAN_TxMsg.id = 2;   // ID del messaggio (CAN 1)
					CAN_TxMsg.format = STANDARD_FORMAT;  
					CAN_TxMsg.type = DATA_FRAME;  

					CAN_wrMsg(1, &CAN_TxMsg);  // Invia il messaggio tramite CAN 1
					 
					 DrawPacman(pacman.x,pacman.y,pacman.radius,pacman.color,pacman.startAngle ,pacman.endAngle);
					
					 if(pacman.lives ==pacman.lives_lose){
						 lose();
					 }
				   
			}
			else if(!blinky.eaten){
				blinky.eaten =1;
				EraseBlinky(blinky.x,blinky.y,blinky.radius,Black);
				
				blinky.respawn =0;
				pacman.score += 100;
				//START A TIMER THAT COUNT 3 SECONDS TO MAKE IT RESPAWN
				
			}
     
    }
}
int ManhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}


int back(char bdir,char scelta){
	// blinky can't go back
		if((bdir == 'U' && scelta == 'D')|| (bdir == 'D' && scelta == 'U')){
			return 1;
		}
		else if((bdir == 'R' && scelta == 'L')|| (bdir == 'L' && scelta == 'R')){
			return 1;
		}
	return 0;
}


void BCheckMove(){
	if(blinky.x ==115 && 135<blinky.y&& blinky.y<175){
		blinky.directionTemp = 'U';
		return;
	}
	if((blinky.x%5==0 && !(blinky.x%10 ==0))&& (blinky.y%5==0 && !(blinky.y%10 ==0))) {
		int best_distance = 100000;
		int min_dist = -1;
		int k;
		int i = (blinky.y-30)/10; // we have to subtract 30 because our matrix start under 30 pixel
		int j = (blinky.x)/10;
		for(k=0;k<4;k++){
			if( !back(blinky.direction,directions[k])){
				switch (directions[k]){
					
					case	'U':
						// if there isn't a wall check best direction
						if(map[i-1][j] != 1){
							int distance = ManhattanDistance(blinky.x,blinky.y-1,pacman.x,pacman.y);
							if (blinky.chase){
								if(distance < best_distance ){
								best_distance = distance;
								blinky.directionTemp = directions[k];  // so in this way choose the best direction
								}
							}else{
								if(distance > min_dist){
									min_dist = distance;
									blinky.directionTemp = directions[k];
								}
							}
							
						}
						break;
						
				 case	'R':
						// if there isn't a wall check best direction
						if(map[i][j+1] != 1){
							int distance = ManhattanDistance(blinky.x+1,blinky.y,pacman.x,pacman.y);
							if (blinky.chase){
								if(distance < best_distance ){
								best_distance = distance;
								blinky.directionTemp = directions[k];  // so in this way choose the best direction
								}
							}else{
								if(distance > min_dist){
									min_dist = distance;
									blinky.directionTemp = directions[k];
								}
							}
						}
						break;
						
				 case	'L':
						// if there isn't a wall check best direction
						if(map[i][j-1] != 1){
							int distance = ManhattanDistance(blinky.x-1,blinky.y,pacman.x,pacman.y);
							if (blinky.chase){
								if(distance < best_distance ){
								best_distance = distance;
								blinky.directionTemp = directions[k];  // so in this way choose the best direction
								}
							}else{
								if(distance > min_dist){
									min_dist = distance;
									blinky.directionTemp = directions[k];
								}
							}
						}
						break;
						
				case	'D':
						// if there isn't a wall check best direction
						if(map[i+1][j] != 1){
							int distance = ManhattanDistance(blinky.x,blinky.y+1,pacman.x,pacman.y);
							if (blinky.chase){
								if(distance < best_distance ){
								best_distance = distance;
								blinky.directionTemp = directions[k];  // so in this way choose the best direction
								}
							}else{
								if(distance > min_dist){
									min_dist = distance;
									blinky.directionTemp = directions[k];
								}
							}
						}
						break;
				}
			}
		}
	}	
}



void MoveBlinky(){
	int i = (blinky.y-30)/10; // we have to subtract 30 because our matrix start under 30 pixel
	int j = (blinky.x)/10;
	BCheckMove();
	if(blinky.direction!=blinky.directionTemp){
			blinky.direction=blinky.directionTemp;
		}
	 int x, y;
	
	switch (blinky.direction){
			case 'U':
				
				y = blinky.y+4;
				for(x= blinky.x-4;x<= blinky.x +4;x++){
					LCD_SetPoint(x, y, Black);
				}
				blinky.y = blinky.y -1;
				DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);
				if(blinky.y % 10 ==0 && map[i][j] ==0){
					LCD_SetPoint(blinky.x,blinky.y+5,White);
				}
				else if (blinky.y% 10 ==0 && map[i][j] ==3){
								uint16_t i;
								uint16_t j ;
								for (j = blinky.x-1; j <= blinky.x+1; j++) {
								for (i = blinky.y+6-1; i <= blinky.y+6+1; i++) {
										LCD_SetPoint(j, i, White); 
									}
								}
							}
				
				break;
				
			case 'R':
				if(j+1 == 24){ //we teleport
						EraseBlinky(blinky.x,blinky.y,blinky.radius,Black);
						blinky.x = 5;
						DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);
				}
				else{
						x = blinky.x -4;
						for(y= blinky.y-4;y<=blinky.y+4;y++){
									LCD_SetPoint(x, y, Black);
						}	
						
						blinky.x = blinky.x +1;
						DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);
						if(blinky.x% 10 ==0 && map[i][j] ==0){
								LCD_SetPoint(blinky.x-5,blinky.y,White);
						}
						else if (blinky.x% 10 ==1 && map[i][j-1] ==3){
								uint16_t i;
								uint16_t j ;
							
								 for (i = blinky.y-1; i <= blinky.y+1; i++){
								 for (j = blinky.x-6-1; j <= blinky.x-6+1; j++){
										LCD_SetPoint(j, i, White); 
									}
								}
							}
				
				}
				break;
				
			case 'L':
				if(j-1 == -1){ // teleport
						EraseBlinky(blinky.x,blinky.y,blinky.radius,Black);
						blinky.x = 235;
						DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);
						
					}
					else{
						x = blinky.x+4;
						for(y= blinky.y-4; y<=blinky.y+4 ;y++){
							LCD_SetPoint(x, y, Black);
						}
						
						blinky.x = blinky.x -1;
						DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);
						if(blinky.x% 10 ==0 && map[i][j] ==0){
								LCD_SetPoint(blinky.x+5,blinky.y,White);
						}
						else if (blinky.x% 10 ==0 && map[i][j] ==3){
								uint16_t i;
								uint16_t j ;
								 for (i = blinky.y-1; i <= blinky.y+1; i++){
								 for (j = blinky.x+6-1; j <= blinky.x+6+1; j++){
										LCD_SetPoint(j, i, White); 
									}
								}
							}
						
					}
					break;
					
			case 'D':
				y = blinky.y-4;
				for(x= blinky.x-4;x<= blinky.x +4;x++){
					LCD_SetPoint(x, y, Black);
				}
				blinky.y = blinky.y +1;
				DrawBlinky(blinky.x,blinky.y,blinky.radius,blinky.color);
				if(blinky.y% 10 ==0 && map[i][j] ==0){
								LCD_SetPoint(blinky.x,blinky.y-5,White);
						}
				else if (blinky.y% 10 ==0 && map[i][j] ==3){
					uint16_t i;
					uint16_t j ;
					for (j = blinky.x-1; j <= blinky.x+1; j++) {
					for (i = blinky.y-6-1; i <= blinky.y-6+1; i++) {
							LCD_SetPoint(j, i, White); 
						}
					}
				}
				
				break;
		}
	
		CheckHitBox(blinky.x,blinky.y,blinky.radius,pacman.x,pacman.y,pacman.radius);
	
}


