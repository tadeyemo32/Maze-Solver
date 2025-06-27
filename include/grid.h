#ifndef GRID_H
#define GRID_H

#include "raylib.h"
extern int SCREEN_W;
extern int SCREEN_H;
extern int plays ; 
extern Vector2 start ; 
extern Vector2 goal ; 

#define GRID_ROWS 20
#define GRID_COLS 20

typedef enum {
    CELL_EMPTY, // emoty 
    CELL_WALL, // no path
    CELL_START, // start 
    CELL_GOAL, // goal
    CELL_PATH ,//movable path
    CELL_UNMOVABLE_PATH,
    CELL_VISITED,
    CELL_TRACE,
} pathType;

extern pathType grid[GRID_ROWS][GRID_COLS];

// Function declarations
void init_grid();
void draw_grid();
void handle_mouse_input();

#endif
