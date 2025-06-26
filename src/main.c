#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "grid.h"


int main(void) {
    init_grid();

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);  
    InitWindow(SCREEN_W, SCREEN_H, "Maze");
    InitAudioDevice();

    while (!WindowShouldClose()) {
        handle_mouse_input();

        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        draw_grid();
        
        EndDrawing();
    }

    CloseWindow();   

}
