#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#define CELL_SIZE 10
int SCREEN_W = 800;
int SCREEN_H = 800;
int plays = 0;
Vector2 start; 
Vector2 goal; 

int gridSize = 800/GRID_ROWS;

pathType grid[GRID_ROWS][GRID_COLS];

pathType curr ; 

void init_grid() {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            if (i == 0 || i == GRID_ROWS - 1 || j == 0 || j == GRID_COLS - 1) {
                grid[i][j] = CELL_WALL;
            } else {
                grid[i][j] = CELL_EMPTY;
            }
        }
    }
}




void draw_grid() {
    // draw lines
   

    // draw cells
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            pathType curr = grid[row][col];

            Color color;
            switch (curr) {
                case CELL_EMPTY: color = BROWN; break;
                case CELL_WALL:  color = LIGHTGRAY; break;
                case CELL_START: color = GREEN; break;
                case CELL_GOAL:  color = RED; break;
                case CELL_PATH:  color = BLUE; break;
            }

            DrawRectangle(col * gridSize, row * gridSize, gridSize, gridSize, color);
        }
    }

     for (int i = 0; i <= GRID_ROWS; i++) {
        DrawLine(0, i * gridSize, SCREEN_W, i * gridSize, RAYWHITE); 
    }
    for (int j = 0; j <= GRID_COLS; j++) {
        DrawLine(j * gridSize, 0, j * gridSize, SCREEN_H, RAYWHITE); 
    }
}


void handle_mouse_input() {
    Vector2 mouse = GetMousePosition();
    int col = mouse.x / gridSize;
    int row = mouse.y / gridSize;

    if (row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS) {
        pathType current = grid[row][col];

        // Prevent editing walls
        if (current == CELL_WALL) {
            printf("Cannot change walls\n");
            return;
        }

        // First click → place start
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && plays == 0) {
            grid[row][col] = CELL_START;
            start.x = col;
            start.y = row;
            plays++;
        }

        // Second click → place goal
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && plays == 1) {
            // Prevent placing goal on the start
            if (grid[row][col] != CELL_START) {
                grid[row][col] = CELL_GOAL;
                goal.x = col;
                goal.y = row;
                plays++;
            }
        }

        // After start and goal set → draw path
        else if (plays >= 2 && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (current == CELL_EMPTY) {
                grid[row][col] = CELL_PATH;
            }
        }
    }
}
