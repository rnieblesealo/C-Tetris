#include <stdio.h>
#include <stdlib.h>
#include "components.h"
#include "blocks.h"

int CanMove(Block* block, Block*** grid, Vector2 dir){
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
			int isValidTile = ((x + dir.x < block->bounds.x && y + dir.y < block->bounds.y) && (block->currentShape[y + dir.y][x + dir.x] != FULL)) || (x + dir.x == blocks->bounds.x || y + dir.y == block->bounds.y);
			
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

int main(){
	
}
