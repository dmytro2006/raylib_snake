//
// Created by dmytro2006 on 03/04/2025.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <vector>

#include "raylib.h"
#include "direction.h"
#include "snake_shape.h"

class Snake {
public:
    Snake();

    ~Snake();

    void draw() const;

    void update(Direction move_direction, Vector2 fruit_position);

    bool is_dead() const;

    bool is_occupied(Vector2 position) const;

    int get_length() const;

    void reset();

private:
    void draw_head(float x, float y) const;

    void draw_tail(float x, float y) const;

    std::deque<Vector2> snake;
    std::deque<Snake_shape> snake_shape;
    std::deque<Direction> directions;
    std::vector<std::vector<short> > map;
    bool dead = false;
    Direction direction;
    Direction previous_direction;
    Texture vertical_texture;
    Texture horizontal_texture;
    Texture down_right_texture;
    Texture down_left_texture;
    Texture up_right_texture;
    Texture up_left_texture;
    Texture head_up;
    Texture head_down;
    Texture head_left;
    Texture head_right;
    Texture tail_up;
    Texture tail_down;
    Texture tail_left;
    Texture tail_right;
};


#endif //SNAKE_H
