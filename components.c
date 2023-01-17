#include <stdlib.h>
#include "components.h"

/* Constructor Definitions */

// Vector2
Vector2 new_s_Vector2(int x, int y){
	Vector2 n;

	n.x = x;
	n.y = y;

	return n;
}

Vector2* new_d_Vector2(int x, int y){
	Vector2* n = (Vector2*)malloc(sizeof(Vector2));

	n->x = x;
	n->y = y;

	return n;
}

// Block
Block new_s_Block(char(*shapes)[Y_SHAPE_SIZE][X_SHAPE_SIZE], Vector2 position){
	Block n;

	n.position = position;
	n.rotation = 0;

	n.bounds.x = X_SHAPE_SIZE;
	n.bounds.y = Y_SHAPE_SIZE;

	n.shapes = shapes;
	n.currentShape = shapes[n.rotation];

	return n;
}

Block* new_d_Block(char(*shapes)[Y_SHAPE_SIZE][X_SHAPE_SIZE], Vector2 position){
	Block* n = (Block*)malloc(sizeof(Block));

	n->position = position;
	n->rotation = 0;

	n->bounds.x = X_SHAPE_SIZE;
	n->bounds.y = Y_SHAPE_SIZE;

	n->shapes = shapes;
	n->currentShape = shapes[n->rotation];

	return n;
}
