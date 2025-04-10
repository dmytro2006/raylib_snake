//
// Created by dmytro2006 on 03/04/2025.
//

#ifndef GAME_H
#define GAME_H
#include <string>
#include <ui.h>

#include "snake.h"
#include "fruit.h"
#include "window.h"

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

    std::string title;
    int width;
    int height;
    int framerate;
    Snake snake;
    Fruit fruit;
    Window window;
    int score;

    bool should_close;

    float delta{};

    Direction movement_direction;
    Direction previous_direction;
};

#endif //GAME_H
