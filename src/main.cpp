//
// Created by dmytro2006 on 03/04/2025.
//

#include "ui.h"
#include "raylib.h"

int main() {
    InitWindow(800, 600, "RAYLIB");
    SetTargetFPS(1000);
    UI::CentredText title("HELLO", BLACK, {0, 0}, {800, 600}, 80, 30);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        title.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
