//
// Created by dmytro2006 on 03/04/2025.
//

#ifndef FRUIT_H
#define FRUIT_H

#include "raylib.h"

class Fruit {
public:
    Fruit() = default;

    ~Fruit() = default;

    void generate();

    Vector2 get_position() const;

    void draw() const;

    void set_visible(bool visible);

    void set_position(Vector2 position);

private:
    Vector2 position{};
    bool visible = true;
};


#endif //FRUIT_H
