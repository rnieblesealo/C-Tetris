// Tetris implemented in C by Rafael Niebles.
// Copyright 2023
// Do not distribute!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "components.h"
#include "blocks.h"

int CanMove(Block* block, char** grid, Vector2 dir){
	for(int y = 0; y < block->bounds.y; ++y){
		for (int x = 0; x < block->bounds.x; ++x){
			if (block->currentShape[y][x] == EMPTY)
				continue;
			
			// Get change in position
			int x1 = x + block->position.x;
			int y1 = y + block->position.y;

			int x2 = x1 + dir.x;
			int y2 = y1 + dir.y;

			// Check if change takes shape out of bounds
			int isWithinBounds = (x2 >= 0 && x2 < X_GRID_SIZE) && (y2 >= 0 && y2 < Y_GRID_SIZE);
			
			// Cannot move if out of bounds
			if (!isWithinBounds)
				return 0;

			// Check if tile has nothing in front of it (its motion path is clear)
			// WARNING Conditional may be incorrect!
			int isValidTile = ((x + dir.x < block->bounds.x && y + dir.y < block->bounds.y) && (block->currentShape[y + dir.y][x + dir.x] != FULL)) || (x + dir.x == block->bounds.x || y + dir.y == block->bounds.y);
			
			// Invalid tiles aren't used to check if movement is possible; therefore skip iteration for this tile
			if (!isValidTile)
				continue;

			// Check if move path is clear
			int isValidMove = grid[y1 + dir.y][x1 + dir.x] == EMPTY;			
			
			// If move path is not clear, we cannot move
			if (!isValidMove)
				return 0;
		}
	}

	// If no failcases matched, movement is possible!
	return 1;
}

int CanRotate(Block* block, char** grid){	
	// Check if base position of the block is in bounds; if it isn't, there is no way a rotation is possible
	int isWithinBounds = (block->position.x >= 0 && block->position.x < X_GRID_SIZE) && (block->position.y >= 0 && block->position.y < Y_GRID_SIZE);

	if (!isWithinBounds)
		return 0;

	for (int y = 0; y < block->bounds.y; ++y){
		for (int x = 0; x < block->bounds.x; ++x){
			// Don't consider any empty blocks
			if (block->currentShape[y][x] == EMPTY)
				continue;

			// Check if grid contents at position of block match the shape of the block (this means there is nothing around the block)
			int gridMatchesShape = block->currentShape[y][x] == grid[y + block->position.y][x + block->position.x];
			
			if (!gridMatchesShape)
				return 0;
		}
	}

	// Rotation is possible if grid matches the shape!
	return 1;
}

void Place(Block* block, char** grid){
	// Copy shape of block to the grid
	for (int y = 0; y < block->bounds.y; ++y){
		for (int x = 0; x < block->bounds.x; ++x){
			grid[y + block->position.y][x + block->position.x] = block->currentShape[y][x];	
		}
	}
}

void Move(Block* block, char** grid, Vector2 dir){
	// Only move block if able to
	if (!CanMove(block, grid, dir))
		return;

	// Copy bounds of block to holder variables
	int xBound = block->bounds.x;
	int yBound = block->bounds.y;

	// Adjust shape bounds to cut off any empty space should the block reach an edge
	if (block->position.x + block->bounds.x > X_GRID_SIZE - 1)
		xBound = X_GRID_SIZE - block->position.x;

	if (block->position.y + block->bounds.y > Y_GRID_SIZE - 1)
		yBound = Y_GRID_SIZE - block->position.y;

	// Delete every tile at the current position... 
	for (int y = 0; y < yBound; ++y){
		for (int x = 0; x < xBound; ++x){
			if (block->currentShape[y][x] == FULL){
				grid[y + block->position.y][x + block->position.x] = EMPTY;
			}
		}
	}

	// And recopy its contents to the destination position
	for (int y = 0; y < yBound; ++y){
		for (int x = 0; x < xBound; ++x){
			if (block->currentShape[y][x] != EMPTY){
				grid[y + block->position.y + dir.y][x + block->position.x + dir.x] = block->currentShape[y][x];
			}
		}
	}

	// Update the block's position!
	block->position.x += dir.x;
	block->position.y += dir.y;
}

void Rotate(Block* block, char** grid){
	// Do not perform rotation if unable to
	if (!CanRotate(block, grid))
		return;

	// Apply clockwise rotation to the shape on the grid (copy shape rotation template to its position in the grid)
	block->rotation = (block->rotation + 1 < SHAPE_COUNT) ? block->rotation + 1 : 0;
	block->currentShape = block->shapes[block->rotation];
	Place(block, grid);
}

int RowIsEmpty(char** grid, int row){
	// Check if a certain row is empty
	for (int x = 0; x < X_GRID_SIZE; ++x){
		if (grid[row][x] == FULL)
			return 0;
	}

	return 1;
}

int* GetFullRows(char** grid){
	// Get int array containing rows in the grid which are full, in descending order
	int* fullRows = (int*)malloc(Y_GRID_SIZE * sizeof(int));
	int fullRowsIDX = 0;
	for (int y = 0; y < Y_GRID_SIZE; ++y){
		// If the inner loop completes with no breaks the row is empty and therefore we add it to the array
		int innerLoopComplete = 1;
		for (int x = 0; x < X_GRID_SIZE; ++x){
			if (grid[y][x] != FULL)
				innerLoopComplete = 0;
				break;
		}
	
		if (innerLoopComplete){
			fullRows[fullRowsIDX] = y;
			fullRowsIDX++;
		}
	}

	// Make the last element of the array -1 to signal its end
	fullRows[fullRowsIDX] = -1;
	return fullRows;
}

void DeleteRow(char** grid, int row){
	// NOTE: This function operates on the assumption that there can never be non-contiguous full rows in case more than 1 full row is present
	
	// Delete empty row
	for (int x = 0; x < X_GRID_SIZE; ++x){
		grid[row][x] = EMPTY;
	}
	
	// Bubble down rows towards the bottom
	while (!RowIsEmpty(grid, row - 1) && row - 1 > 0){
		// Copy current row to temporary char array
		char temp[X_GRID_SIZE];
	      	strcpy(temp, grid[row]);
		
		// Swap rows!
		strcpy(grid[row], grid[row - 1]);
		strcpy(grid[row - 1], temp);
	
		// Onward!
		row--;
	}
}

int CanSpawnBlock(Block* block, char** grid){
// A block can spawn when the area a block is going to spawn into has no obstruction (existing tiles)
// Therefore, check if the tiles the block needs to be empty ARE empty, and if so, return true!	// A block can spawn when the area a block is going to spawn into has no obstructions (existing tiles)
	// Therefore, check if the tiles the block needs to be empty ARE empty, and if so, return true!
	for (int y = 0; y < block->bounds.y; ++y){
		for (int x = 0; x < block->bounds.x; ++x){
			if (block->currentShape[y][x] == EMPTY){
				continue;
			}

			if (grid[y + block->position.y][x + block->position.x] == FULL)
				return 0;
		}
	}

	return 1;
}

int main(){
	// Initialize grid	
}
