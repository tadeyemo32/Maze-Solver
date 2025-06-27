#include "grid.h"
#include "maze.h"
#include "bfs.h"
#include "cJSON.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

// Ensure the "mazes" directory exists
void ensureMazeDirExists() {
    struct stat st = {0};
    if (stat("mazes", &st) == -1) {
#ifdef _WIN32
        mkdir("mazes");
#else
        mkdir("mazes", 0700);
#endif
    }
}

// Save maze to "mazes/<filename>.json"
void saveMazeToFile(const char* filename) {
    ensureMazeDirExists();

    char path[256];
    snprintf(path, sizeof(path), "mazes/%s", filename);

    cJSON* root = cJSON_CreateArray();
    for (int y = 0; y < GRID_ROWS; y++) {
        cJSON* row = cJSON_CreateArray();
        for (int x = 0; x < GRID_COLS; x++) {
            cJSON_AddItemToArray(row, cJSON_CreateNumber(grid[y][x]));
        }
        cJSON_AddItemToArray(root, row);
    }

    char* jsonStr = cJSON_Print(root);
    FILE* f = fopen(path, "w");
    if (f) {
        fputs(jsonStr, f);
        fclose(f);
    }

    cJSON_Delete(root);
    free(jsonStr);
}

// Load maze from "mazes/<filename>.json"
void loadMazeFromFile(const char* filename) {
    char path[256];
    snprintf(path, sizeof(path), "mazes/%s", filename);

    FILE* f = fopen(path, "r");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    char* data = (char*)malloc(len + 1);
    fread(data, 1, len, f);
    data[len] = '\0';
    fclose(f);

    cJSON* root = cJSON_Parse(data);
    if (!root) {
        free(data);
        return;
    }

    for (int y = 0; y < GRID_ROWS; y++) {
        cJSON* row = cJSON_GetArrayItem(root, y);
        if (!cJSON_IsArray(row)) continue;

        for (int x = 0; x < GRID_COLS; x++) {
            cJSON* item = cJSON_GetArrayItem(row, x);
            if (!cJSON_IsNumber(item)) continue;

            int val = item->valueint;
            if (val == CELL_TRACE || val == CELL_VISITED)
                grid[y][x] = CELL_EMPTY;
            else
                grid[y][x] = (pathType)val;

            if (val == CELL_START) start = (Vector2){ x, y };
            if (val == CELL_GOAL)  goal = (Vector2){ x, y };
        }
    }

    resetQueue();
    cJSON_Delete(root);
    free(data);
}

// Reset the maze grid and BFS state
void resetMaze() {
   init_grid();
    plays = 0;

    start = (Vector2){ -1, -1 };
    goal = (Vector2){ -1, -1 };

    resetQueue();
}
