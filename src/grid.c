#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#define CELL_SIZE 10
int SCREEN_W = 800;
int SCREEN_H = 800;

int gridSize = 800/GRID_ROWS;

pathType grid[GRID_ROWS][GRID_COLS];

pathType curr ; 
void init_grid(){
    for (int i = 0;i<GRID_ROWS;i++){
        for(int j =0;j<GRID_COLS;j++){
            grid[i][j] = CELL_EMPTY;
            printf("Grid {%d}{%d} is empty\n",i,j);
        }
}


}



void draw_grid(){
    for(int i = 0 ; i<GRID_ROWS;i++){
            DrawLine(i * gridSize, 0, i * gridSize, SCREEN_H, RAYWHITE);

        for(int j = 0;j<GRID_COLS;j++){
         DrawLine(0, j * gridSize, SCREEN_W, j * gridSize, RAYWHITE);
int row = i ; 
int col = j; 
curr = grid[i][j];
         if(row==0){
            grid[i][j] = CELL_WALL;
         }else if (row == GRID_ROWS-1){
            grid[i][j] = CELL_WALL;
         }else if(col== 0){
        grid[i][j] = CELL_WALL;
         }else if (col ==GRID_COLS-1){
        grid[i][j] = CELL_WALL;
         }

    if (curr == CELL_EMPTY) {
 DrawRectangle(i * gridSize, j*gridSize,gridSize,gridSize,BROWN);} 
 else if (curr == CELL_WALL) {
 DrawRectangle(i * gridSize, j*gridSize,gridSize,gridSize,LIGHTGRAY);} 
 else if (curr == CELL_START) {
 DrawRectangle(i * gridSize, j*gridSize,gridSize,gridSize,GREEN);
} else if (curr == CELL_GOAL) {
 DrawRectangle(i * gridSize, j*gridSize,gridSize,gridSize,RED);
} else if (curr == CELL_PATH) {
 DrawRectangle(i * gridSize, j*gridSize,gridSize,gridSize,BLUE);
} 
    
        }
    }
    
}


void handle_mouse_input(){


}

