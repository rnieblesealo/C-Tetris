#include <stdio.h>
#include <stdlib.h>
#include "components.h"
#include "blocks.h"

int main(){
	Block* new = new_d_Block(T_BLOCK, new_s_Vector2(0, 0));
	
	// Test display new's position, note that it works!
	for (int i = 0; i < 4; ++i){
		for (int y = 0; y < Y_SHAPE_SIZE; ++y){
			for (int x = 0; x < X_SHAPE_SIZE; ++x){
				printf(" %c ", new->shapes[i][y][x]);
			}
			putchar('\n');
		}
		puts("--------");
	}
}
