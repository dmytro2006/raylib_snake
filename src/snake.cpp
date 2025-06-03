//
// Created by dmytro2006 on 03/04/2025.
//

#include "snake.h"

#include <iostream>

#include "config.h"
#include <map>
#include <ostream>

// (previous_direction, current_direction) -> shape
const std::map<std::pair<Direction, Direction>, Snake_shape> shapes = {
    {{Direction::DOWN, Direction::RIGHT}, Snake_shape::UP_RIGHT},
    {{Direction::DOWN, Direction::DOWN}, Snake_shape::VERTICAL},
    {{Direction::DOWN, Direction::LEFT}, Snake_shape::UP_LEFT},
    {{Direction::RIGHT, Direction::RIGHT}, Snake_shape::HORIZONTAL},
    {{Direction::RIGHT, Direction::DOWN}, Snake_shape::DOWN_LEFT},
    {{Direction::RIGHT, Direction::UP}, Snake_shape::UP_LEFT},
    {{Direction::LEFT, Direction::LEFT}, Snake_shape::HORIZONTAL},
    {{Direction::LEFT, Direction::UP}, Snake_shape::UP_RIGHT},
    {{Direction::LEFT, Direction::DOWN}, Snake_shape::DOWN_RIGHT},
    {{Direction::UP, Direction::UP}, Snake_shape::VERTICAL},
    {{Direction::UP, Direction::RIGHT}, Snake_shape::DOWN_RIGHT},
    {{Direction::UP, Direction::LEFT}, Snake_shape::DOWN_LEFT},
};

Snake::Snake(): direction(Direction::RIGHT), previous_direction(Direction::RIGHT) {
}

Snake::~Snake() {
    map.clear();
    snake.clear();
}

void Snake::draw_head(float x, float y) const {
    switch (direction) {
        case Direction::RIGHT:
            DrawTextureEx(head_right, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
            break;
        case Direction::LEFT:
            DrawTextureEx(head_left, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
            break;
        case Direction::UP:
            DrawTextureEx(head_up, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
            break;
        case Direction::DOWN:
            DrawTextureEx(head_down, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
            break;
    }
}

void Snake::draw_tail(float x, float y) const {
    switch (*(directions.end()-2)) {
        case Direction::RIGHT:
            DrawTextureEx(tail_right, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
        break;
        case Direction::LEFT:
            DrawTextureEx(tail_left, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
        break;
        case Direction::UP:
            DrawTextureEx(tail_up, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
        break;
        case Direction::DOWN:
            DrawTextureEx(tail_down, {MARGIN_X + x * GRID_STEP, MARGIN_Y + y * GRID_STEP}, 0,
                          static_cast<float>(GRID_STEP) / 30, WHITE);
        break;
    }
}

void Snake::draw() const {
    auto it = snake.begin() + 1;
    auto shape_it = snake_shape.begin() + 1;
    for (std::size_t i = 0; i < snake.size() - 2; ++i) {
        switch (*shape_it) {
            case Snake_shape::VERTICAL:
                DrawTextureEx(vertical_texture, {MARGIN_X + it->x * GRID_STEP, MARGIN_Y + it->y * GRID_STEP}, 0,
                              static_cast<float>(GRID_STEP) / 30, WHITE);
                break;
            case Snake_shape::HORIZONTAL:
                DrawTextureEx(horizontal_texture, {MARGIN_X + it->x * GRID_STEP, MARGIN_Y + it->y * GRID_STEP}, 0,
                              static_cast<float>(GRID_STEP) / 30, WHITE);
                break;
            case Snake_shape::UP_LEFT:
                DrawTextureEx(up_left_texture, {MARGIN_X + it->x * GRID_STEP, MARGIN_Y + it->y * GRID_STEP}, 0,
                              static_cast<float>(GRID_STEP) / 30, WHITE);
                break;
            case Snake_shape::UP_RIGHT:
                DrawTextureEx(up_right_texture, {MARGIN_X + it->x * GRID_STEP, MARGIN_Y + it->y * GRID_STEP}, 0,
                              static_cast<float>(GRID_STEP) / 30, WHITE);
                break;
            case Snake_shape::DOWN_LEFT:
                DrawTextureEx(down_left_texture, {MARGIN_X + it->x * GRID_STEP, MARGIN_Y + it->y * GRID_STEP}, 0,
                              static_cast<float>(GRID_STEP) / 30, WHITE);
                break;
            case Snake_shape::DOWN_RIGHT:
                DrawTextureEx(down_right_texture, {MARGIN_X + it->x * GRID_STEP, MARGIN_Y + it->y * GRID_STEP}, 0,
                              static_cast<float>(GRID_STEP) / 30, WHITE);
                break;
        }

        ++it;
        ++shape_it;
    }
    draw_head(snake[0].x, snake[0].y);
    draw_tail(snake.back().x, snake.back().y);
}

void Snake::update(const Direction move_direction, const Vector2 fruit_position) {
    direction = move_direction;
    auto new_head = snake.front();
    switch (move_direction) {
        case Direction::UP:
            new_head.y--;
            break;
        case Direction::DOWN:
            new_head.y++;
            break;
        case Direction::RIGHT:
            new_head.x++;
            break;
        case Direction::LEFT:
            new_head.x--;
            break;
    }
    snake.push_front(new_head);
    directions.push_front(direction);
    snake_shape.front() = shapes.at({previous_direction, direction});
    snake_shape.push_front(shapes.at({direction, direction}));
    previous_direction = direction;
    // check if snake has eaten the fruit
    if (fruit_position.x == new_head.x && fruit_position.y == new_head.y) {
        map[new_head.x][new_head.y] = 1;
        return;
    }
    map[snake.back().x][snake.back().y] = 0;
    snake.pop_back();
    snake_shape.pop_back();
    directions.pop_back();
    // check if snake hits wall or itself
    if (snake.front().x < 0 || snake.front().y < 0 || snake.front().x >= GRID_SIZE_X || snake.front().
        y >=
        GRID_SIZE_Y ||
        map[snake.front().x][snake.front().y]) {
        dead = true;
        return;
    }
    map[new_head.x][new_head.y] = 1;
}

bool Snake::is_dead() const {
    return dead;
}

bool Snake::is_occupied(Vector2 position) const {
    return map[position.x][position.y];
}

int Snake::get_length() const {
    return snake.size();
}

void Snake::load_textures(const std::string& skin) {
    vertical_texture = LoadTexture(("textures/" + skin + "/vertical.png").c_str());
    horizontal_texture = LoadTexture(("textures/" + skin + "/horizontal.png").c_str());
    down_right_texture = LoadTexture(("textures/" + skin + "/down_right.png").c_str());
    down_left_texture = LoadTexture(("textures/" + skin + "/down_left.png").c_str());
    up_right_texture = LoadTexture(("textures/" + skin + "/up_right.png").c_str());
    up_left_texture = LoadTexture(("textures/" + skin + "/up_left.png").c_str());
    head_up = LoadTexture(("textures/" + skin + "/head_up.png").c_str());
    head_down = LoadTexture(("textures/" + skin + "/head_down.png").c_str());
    head_left = LoadTexture(("textures/" + skin + "/head_left.png").c_str());
    head_right = LoadTexture(("textures/" + skin + "/head_right.png").c_str());
    tail_up = LoadTexture(("textures/" + skin + "/tail_up.png").c_str());
    tail_down = LoadTexture(("textures/" + skin + "/tail_down.png").c_str());
    tail_left = LoadTexture(("textures/" + skin + "/tail_left.png").c_str());
    tail_right = LoadTexture(("textures/" + skin + "/tail_right.png").c_str());
}

void Snake::unload_textures() {
    UnloadTexture(vertical_texture);
    UnloadTexture(horizontal_texture);
    UnloadTexture(down_right_texture);
    UnloadTexture(down_left_texture);
    UnloadTexture(up_right_texture);
    UnloadTexture(up_left_texture);
    UnloadTexture(head_up);
    UnloadTexture(head_down);
    UnloadTexture(head_left);
    UnloadTexture(head_right);
    UnloadTexture(tail_up);
    UnloadTexture(tail_down);
    UnloadTexture(tail_left);
    UnloadTexture(tail_right);
}


void Snake::reset() {
    dead = false;
    map.clear();
    snake.clear();
    snake_shape.clear();
    directions.clear();
    previous_direction = direction = Direction::RIGHT;
    map = {GRID_SIZE_X, std::vector<short>(GRID_SIZE_Y, 0)};
    map[GRID_SIZE_X / 2][GRID_SIZE_X / 2] = 1;
    map[GRID_SIZE_X / 2 - 1][GRID_SIZE_Y / 2] = 1;
    snake.push_back({GRID_SIZE_X / 2, GRID_SIZE_Y / 2});
    snake.push_back({GRID_SIZE_X / 2 - 1, GRID_SIZE_Y / 2});
    snake_shape.push_back(Snake_shape::HORIZONTAL);
    snake_shape.push_back(Snake_shape::HORIZONTAL);
    directions.push_front(Direction::RIGHT);
    directions.push_back(Direction::RIGHT);
}
