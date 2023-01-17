/* Definitions for components necessary for the application to function. */

#ifndef COMPONENTS_H
#define COMPONENTS_H

// Macro Constants
#define X_SHAPE_SIZE 3
#define Y_SHAPE_SIZE 3

// Structures
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

// Constructors
Vector2 new_s_Vector2(int x, int y);
Vector2* new_d_Vector2(int x, int y);

Block new_s_Block(char(*shapes)[Y_SHAPE_SIZE][X_SHAPE_SIZE], Vector2 position);
Block* new_d_Block(char(*shapes)[Y_SHAPE_SIZE][X_SHAPE_SIZE], Vector2 position);

#endif
