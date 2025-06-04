//
// Created by dmytro2006 on 03/04/2025.
//

#include "fruit.h"

#include <stdexcept>

#include "config.h"

// generate new fruit position
void Fruit::generate() {
    position.x = static_cast<float>(GetRandomValue(0, GAME_AREA_WIDTH / GRID_STEP - 1));
    position.y = static_cast<float>(GetRandomValue(0, GAME_AREA_HEIGHT / GRID_STEP - 1));
}

void Fruit::draw() const {
    if (!visible) return;
    // DrawCircle(MARGIN_X + position.x * GRID_STEP + GRID_STEP / 2,
    //            MARGIN_Y + position.y * GRID_STEP + GRID_STEP / 2, FRUIT_RADIUS, FRUIT_COLOR);
    DrawTextureEx(fruit, {
                      MARGIN_X + position.x * GRID_STEP,
                      MARGIN_Y + position.y * GRID_STEP
                  }, 0, static_cast<float>(GRID_STEP)/30, WHITE);
}

void Fruit::set_visible(bool visible) {
    this->visible = visible;
}

Vector2 Fruit::get_position() const {
    return position;
}

void Fruit::set_position(Vector2 position) {
    this->position = position;
}

void Fruit::load_textures() {
    fruit = LoadTexture("textures/fruit.png");
    if (!IsTextureValid(fruit)) {
        throw std::runtime_error("Fruit texture could not be loaded");
    }
}

void Fruit::unload_textures() {
    UnloadTexture(fruit);
}
