#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#define CELL_SIZE 10
int SCREEN_W = 800;
int SCREEN_H = 800;

int gridSize = 800/GRID_ROWS;

pathType grid[GRID_ROWS][GRID_COLS];


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
            DrawRectangle(i * gridSize, j*gridSize,gridSize,gridSize,SKYBLUE);
           


        }
    }
    
}


void handle_mouse_input(){


}

