//
// Created by dmytro2006 on 03/04/2025.
//

#include "game.h"
#include "raylib.h"
#include "ui.h"
#include "config.h"

Game::Game(const std::string &title, int width, int height, int framerate): title(title), width(width), height(height),
                                                                            framerate(framerate), should_close(false),
                                                                            window(Window::MENU), score(1),
                                                                            difficulty(Difficulty::EASY),
                                                                            movement_direction(Direction::RIGHT),
                                                                            previous_direction(Direction::RIGHT) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(framerate);
    SetExitKey(KEY_NULL);
}

Game::~Game() {
    CloseWindow();
}

void Game::play() {
    while (!should_close) {
        update();
        draw();
    }
}


void Game::update() {
    should_close = WindowShouldClose();
    switch (window) {
        case Window::MENU:
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (UI::is_pressed({150, 180}, {200, 60}, GetMousePosition())) {
                    window = Window::GAME;
                    reset();
                    break;
                }
                if (UI::is_pressed({150, 260}, {200, 60}, GetMousePosition())) {
                    difficulty = static_cast<Difficulty>((static_cast<int>(difficulty) + 1) % 3);
                    break;
                }
                if (UI::is_pressed({150, 340}, {200, 60}, GetMousePosition())) {
                    should_close = true;
                    break;
                }
            }
            break;
        case Window::GAME:
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (UI::is_pressed({400, 5}, {60, 30}, GetMousePosition())) {
                    window = Window::MENU;
                    break;
                }
            }
            get_movement_direction();
            delta += GetFrameTime();
            if (delta >= 0.3) {
                delta = 0;
                snake.update(movement_direction, fruit.get_position());
                previous_direction = movement_direction;
                if (snake.is_dead()) {
                    window = Window::SCORE;
                }
                score = snake.get_length();
                if (snake.is_occupied(fruit.get_position()) && score < GRID_SIZE_X * GRID_SIZE_Y) {
                    do {
                        fruit.generate();
                    } while (snake.is_occupied(fruit.get_position()));
                }
                if (score == GRID_SIZE_X * GRID_SIZE_Y) {
                    fruit.set_visible(false);
                }
            }
            break;
        case Window::SCORE:
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (UI::is_pressed({150, 180}, {200, 60}, GetMousePosition())) {
                    reset();
                    window = Window::GAME;
                    break;
                }
                if (UI::is_pressed({150, 260}, {200, 60}, GetMousePosition())) {
                    window = Window::MENU;
                    break;
                }
            }
    }
}

void Game::draw() const {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    draw_ui();
    if (window == Window::GAME) {
        draw_grid();
        snake.draw();
        fruit.draw();
    }
    EndDrawing();
}

void Game::draw_ui() const {
    switch (window) {
        case Window::GAME:
            UI::draw_button("MENU", {400, 5}, {60, 30}, WHITE, RED, 15);
            DrawText(TextFormat("SCORE: %i", score), 40, 10, 20, BLACK);
            break;
        case Window::SCORE:
            UI::draw_centred_text(TextFormat("SCORE: %i", score), {0, 40}, {WIDTH, 100}, BLACK, 80);
            UI::draw_button("RETRY", {150, 180}, {200, 60}, WHITE, RED, 40);
            UI::draw_button("MENU", {150, 260}, {200, 60}, WHITE, RED, 40);

            break;
        case Window::MENU:
            UI::draw_centred_text("SNAKE", {0, 40}, {WIDTH, 100}, BLACK, 80);
            UI::draw_button("START", {150, 180}, {200, 60},WHITE, RED, 40);
            UI::draw_button("DIFFICULTY\n" + get_difficulty_string(), {150, 260}, {200, 60}, WHITE, RED, 20);
            UI::draw_button("EXIT", {150, 340}, {200, 60}, WHITE, RED, 40);
            break;
    }
}

void Game::draw_grid() const {
    for (int x = GAME_AREA_X; x <= GAME_AREA_X + GAME_AREA_WIDTH; x += GRID_STEP)
        DrawLineEx((Vector2){static_cast<float>(x + 1), GAME_AREA_Y},
                   {static_cast<float>(x + 1), GAME_AREA_Y + GAME_AREA_HEIGHT}, 1, GRAY);
    for (int y = GAME_AREA_Y; y <= GAME_AREA_Y + GAME_AREA_HEIGHT; y += GRID_STEP)
        DrawLineEx((Vector2){GAME_AREA_X, static_cast<float>(y + 1)}, (Vector2){
                       GAME_AREA_X + GAME_AREA_WIDTH, static_cast<float>(y + 1)
                   }, 1, GRAY);
    DrawRectangleLinesEx({GAME_AREA_X - 3, GAME_AREA_Y - 3, GAME_AREA_WIDTH + 6, GAME_AREA_HEIGHT + 6}, 3, BLACK);
}

void Game::reset() {
    snake.reset();
    score = 1;
    delta = 0;
    do {
        fruit.generate();
    } while (snake.is_occupied(fruit.get_position()));
}

void Game::get_movement_direction() {
    if (IsKeyDown(KEY_RIGHT) && previous_direction != Direction::LEFT) {
        movement_direction = Direction::RIGHT;
        return;
    }
    if (IsKeyDown(KEY_LEFT) && previous_direction != Direction::RIGHT) {
        movement_direction = Direction::LEFT;
        return;
    }
    if (IsKeyDown(KEY_UP) && previous_direction != Direction::DOWN) {
        movement_direction = Direction::UP;
        return;
    }
    if (IsKeyDown(KEY_DOWN) && previous_direction != Direction::UP) {
        movement_direction = Direction::DOWN;
        return;
    }
}

std::string Game::get_difficulty_string() const {
    switch (difficulty) {
        case Difficulty::EASY:
            return "EASY";
        case Difficulty::MEDIUM:
            return "MEDIUM";
        case Difficulty::HARD:
            return "HARD";
    }
    return "";
}
