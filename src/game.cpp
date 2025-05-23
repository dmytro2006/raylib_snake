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
                                                                            tick_time(0), max_tick_time(0),
                                                                            min_tick_time(0),
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
                if (UI::is_pressed({(WIDTH - 200) / 2, 180}, {200, 60}, GetMousePosition())) {
                    window = Window::GAME;
                    reset();
                    break;
                }
                if (UI::is_pressed({(WIDTH - 200) / 2, 260}, {200, 60}, GetMousePosition())) {
                    difficulty = static_cast<Difficulty>((static_cast<int>(difficulty) + 1) % 3);
                    break;
                }
                if (UI::is_pressed({(WIDTH - 200) / 2, 340}, {200, 60}, GetMousePosition())) {
                    should_close = true;
                    break;
                }
            }
            break;
        case Window::GAME:
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (UI::is_pressed({WIDTH - MARGIN_X - 60, 5}, {60, 30}, GetMousePosition())) {
                    window = Window::MENU;
                    break;
                }
            }
            get_movement_direction();
            delta += GetFrameTime();
            tick_time = max_tick_time - (max_tick_time - min_tick_time) * score / MAX_LENGTH;
            if (delta >= tick_time) {
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
                if (UI::is_pressed({(WIDTH - 200) / 2, 180}, {200, 60}, GetMousePosition())) {
                    reset();
                    window = Window::GAME;
                    break;
                }
                if (UI::is_pressed({(WIDTH - 200) / 2, 260}, {200, 60}, GetMousePosition())) {
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
            UI::draw_button("MENU", {WIDTH - MARGIN_X - 60, 5}, {60, 30}, WHITE, RED, 15);
            DrawText(TextFormat("SCORE: %i", score), 40, 10, 20, BLACK);
            break;
        case Window::SCORE:
            UI::draw_centred_text(TextFormat("SCORE: %i", score), {0, 40}, {WIDTH, 100}, BLACK, 80);
            UI::draw_button("RETRY", {(WIDTH - 200) / 2, 180}, {200, 60}, WHITE, RED, 40);
            UI::draw_button("MENU", {(WIDTH - 200) / 2, 260}, {200, 60}, WHITE, RED, 40);

            break;
        case Window::MENU:
            UI::draw_centred_text("SNAKE", {0, 40}, {WIDTH, 100}, BLACK, 80);
            UI::draw_button("START", {(WIDTH - 200) / 2, 180}, {200, 60},WHITE, RED, 40);
            UI::draw_button("DIFFICULTY\n" + get_difficulty_string(), {(WIDTH - 200) / 2, 260}, {200, 60}, WHITE, RED,
                            20);
            UI::draw_button("EXIT", {(WIDTH - 200) / 2, 340}, {200, 60}, WHITE, RED, 40);
            break;
    }
}

void Game::draw_grid() const {
    for (int x = MARGIN_X; x <= MARGIN_X + GAME_AREA_WIDTH; x += GRID_STEP)
        DrawLineEx((Vector2){static_cast<float>(x + 1), MARGIN_Y},
                   {static_cast<float>(x + 1), MARGIN_Y + GAME_AREA_HEIGHT}, 1, GRAY);
    for (int y = MARGIN_Y; y <= MARGIN_Y + GAME_AREA_HEIGHT; y += GRID_STEP)
        DrawLineEx((Vector2){MARGIN_X, static_cast<float>(y + 1)}, (Vector2){
                       MARGIN_X + GAME_AREA_WIDTH, static_cast<float>(y + 1)
                   }, 1, GRAY);
    DrawRectangleLinesEx({MARGIN_X - 3, MARGIN_Y - 3, GAME_AREA_WIDTH + 6, GAME_AREA_HEIGHT + 6}, 3, BLACK);
}

void Game::reset() {
    max_tick_time = (difficulty == Difficulty::EASY
                         ? MAX_TIME
                         : (difficulty == Difficulty::MEDIUM
                                ? MAX_TIME * MEDIUM_MULTIPLIER
                                : MAX_TIME * HARD_MULTIPLIER));
    min_tick_time = (difficulty == Difficulty::EASY
                         ? MIN_TIME
                         : (difficulty == Difficulty::MEDIUM
                                ? MIN_TIME * MEDIUM_MULTIPLIER
                                : MIN_TIME * HARD_MULTIPLIER));
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
