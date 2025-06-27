#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "raylib.h"
#include "grid.h"
#include "bfs.h"
#include "cJSON.h"

bool showDropdown = false;

// Ensure "mazes/" directory exists
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

// Reset everything: grid, BFS, state
void resetMaze() {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            grid[y][x] = CELL_EMPTY; // <-- clear every cell
        }
    }

    start = (Vector2){ -1, -1 }; // <-- clears start marker
    goal = (Vector2){ -1, -1 };  // <-- clears goal marker

    resetQueue(); // <-- clears BFS queue
}


// Save maze to mazes/maze.json
void saveMazeToFile(const char* filename) {
    ensureMazeDirExists();
    cJSON* root = cJSON_CreateArray();
    for (int y = 0; y < GRID_ROWS; y++) {
        cJSON* row = cJSON_CreateArray();
        for (int x = 0; x < GRID_COLS; x++) {
            cJSON_AddItemToArray(row, cJSON_CreateNumber(grid[y][x]));
        }
        cJSON_AddItemToArray(root, row);
    }

    char* jsonStr = cJSON_Print(root);
    FILE* f = fopen(filename, "w");
    if (f) {
        fputs(jsonStr, f);
        fclose(f);
    }

    cJSON_Delete(root);
    free(jsonStr);
}

// Load maze and reset traces
void loadMazeFromFile(const char* filename) {
    FILE* f = fopen(filename, "r");
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
        for (int x = 0; x < GRID_COLS; x++) {
            int val = cJSON_GetArrayItem(row, x)->valueint;
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

int main(void) {
    init_grid();

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);  
    InitWindow(SCREEN_W, SCREEN_H, "Maze Solver");
    InitAudioDevice();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        draw_grid();

        // === Top-right Menu ===
        Rectangle menuButton = { SCREEN_W - 110, 10, 100, 30 };
        DrawRectangleRec(menuButton, DARKGRAY);
        DrawText("Menu", menuButton.x + 20, menuButton.y + 8, 15, WHITE);

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, menuButton)) {
            showDropdown = !showDropdown;
        }

        // If menu is open, pause game logic
        bool paused = showDropdown;

        // === Dropdown Items ===
        if (showDropdown) {
            Rectangle saveRect = { menuButton.x, menuButton.y + 35, 100, 30 };
            Rectangle loadRect = { menuButton.x, menuButton.y + 70, 100, 30 };

            DrawRectangleRec(saveRect, GRAY);
            DrawText("Save Maze", saveRect.x + 5, saveRect.y + 8, 14, BLACK);

            DrawRectangleRec(loadRect, GRAY);
            DrawText("Load Maze", loadRect.x + 5, loadRect.y + 8, 14, BLACK);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, saveRect)) {
                    saveMazeToFile("mazes/maze.json");
                    showDropdown = false;
                } else if (CheckCollisionPointRec(mouse, loadRect)) {
                    loadMazeFromFile("mazes/maze.json");
                    showDropdown = false;
                }
            }
        }

        // === Restart Button (bottom left) ===
        Rectangle restartButton = { 10, SCREEN_H - 40, 100, 30 };
        DrawRectangleRec(restartButton, RED);
        DrawText("Restart", restartButton.x + 15, restartButton.y + 8, 15, WHITE);

        if (!paused && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, restartButton)) {
            resetMaze();
        }

        // === Game logic only if not paused ===
        if (!paused) {
            handle_mouse_input(); // set start, goal, walls
            if (IsKeyPressed(KEY_SPACE)) {
                bfs();
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
