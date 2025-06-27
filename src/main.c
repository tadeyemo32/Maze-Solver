#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "raylib.h"
#include "grid.h"
#include "bfs.h"
#include "cJSON.h"
#include "maze.h"


bool showDropdown = false;



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
        saveMazeToFile("maze.json");  // ✅ Correct
            showDropdown = false;
        } else if (CheckCollisionPointRec(mouse, loadRect)) {
        loadMazeFromFile("maze.json");  // ✅ Correct
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
