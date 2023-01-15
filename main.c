#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

#define X_SHAPE_SIZE 3
#define Y_SHAPE_SIZE 3

typedef struct Vector2{
	int x;
	int y;
} Vector2;

typedef struct Block{	
	char(*shapes)[Y_SHAPE_SIZE][X_SHAPE_SIZE];
	char(*currentShape)[X_SHAPE_SIZE];
	Vector2 bounds;
	Vector2 position;
	int rotation;

} Block;

Vector2 new_Vector2(int x, int y);
Block* new_Block(char(*shapes)[Y_SHAPE_SIZE][X_SHAPE_SIZE], Vector2 position);

int main(){
	Block* new = new_Block(T_BLOCK, new_Vector2(0, 0));
	
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

Vector2 new_Vector2(int x, int y){
	Vector2 n;
	
	n.x = x;
	n.y = y;

	return n;
}

Block* new_Block(char(*shapes)[Y_SHAPE_SIZE][X_SHAPE_SIZE], Vector2 position){
	Block* n = (Block*)malloc(sizeof(Block));

	n->position = position;
	n->rotation = 0;

	n->bounds.x = X_SHAPE_SIZE;
	n->bounds.y = Y_SHAPE_SIZE;

	n->shapes = shapes;
	n->currentShape = shapes[n->rotation];

	return n;
}
