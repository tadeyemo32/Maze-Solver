#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#define CELL_SIZE 10
int SCREEN_W = 800;
int SCREEN_H = 800;
int plays = 0;

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
        DrawLine(0, i * gridSize, SCREEN_W, i * gridSize, RAYWHITE); // horizontal
    }
    for (int j = 0; j <= GRID_COLS; j++) {
        DrawLine(j * gridSize, 0, j * gridSize, SCREEN_H, RAYWHITE); // vertical
    }
}

void handle_mouse_input() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        int col = mouse.x / gridSize;
        int row = mouse.y / gridSize;

        // Bounds check to avoid crashing when clicking outside the grid
        if (row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS) {
            if (grid[row][col] != CELL_WALL) {
                if (plays == 0) {
                    grid[row][col] = CELL_START;
                    plays++;
                } else if (plays == 1) {
                    grid[row][col] = CELL_GOAL;
                    plays++;
                } else {
                    grid[row][col] = CELL_PATH;
                }
            } else {
                printf("Cannot change walls\n");
            }
        }
    }
}

