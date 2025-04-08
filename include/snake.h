//
// Created by dmytro2006 on 03/04/2025.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <vector>

#include "raylib.h"
#include "direction.h"

class Snake {
public:
    Snake();

    ~Snake();

    void draw() const;

    void update(Direction move_direction, Vector2 fruit_position);

    bool is_dead() const;

    bool is_occupied(Vector2 position) const;

private:
    std::deque<Vector2> snake;
    std::vector<std::vector<short> > map;
    bool dead = false;
    Direction direction;
};


#endif //SNAKE_H
