//
// Created by dmytro2006 on 03/04/2025.
//

#ifndef GAME_H
#define GAME_H
#include <string>

#include "snake.h"
#include "fruit.h"
#include "window.h"
#include "difficulty.h"

class Game {
public:
    Game(const std::string &title, int width, int height, int framerate);

    ~Game();

    void play();

private:
    void update();

    void draw() const;

    void draw_grid() const;

    void draw_ui() const;

    void reset();

    void get_movement_direction();

    std::string get_difficulty_string() const;

    std::string title;
    int width;
    int height;
    int framerate;
    bool should_close;

    Window window;
    int score;
    float delta{};
    Difficulty difficulty;

    float tick_time;
    float max_tick_time;
    float min_tick_time;

    Snake snake;
    Fruit fruit;

    Direction movement_direction;
    Direction previous_direction;

    Texture arrows;
};

#endif //GAME_H
