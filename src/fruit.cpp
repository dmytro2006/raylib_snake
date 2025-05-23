//
// Created by dmytro2006 on 03/04/2025.
//

#include "fruit.h"
#include "config.h"


void Fruit::generate() {
    position.x = static_cast<float>(GetRandomValue(0, GAME_AREA_WIDTH / GRID_STEP - 1));
    position.y = static_cast<float>(GetRandomValue(0, GAME_AREA_HEIGHT / GRID_STEP - 1));
}

void Fruit::draw() const{
    if (!visible) return;
    DrawCircle(MARGIN_X + position.x * GRID_STEP + GRID_STEP / 2,
               MARGIN_Y + position.y * GRID_STEP + GRID_STEP / 2, FRUIT_RADIUS, FRUIT_COLOR);
}

void Fruit::set_visible(bool visible) {
    this->visible = visible;
}

Vector2 Fruit::get_position() const {
    return position;
}
