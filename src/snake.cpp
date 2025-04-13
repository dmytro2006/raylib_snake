//
// Created by dmytro2006 on 03/04/2025.
//

#include "snake.h"
#include "config.h"

Snake::Snake(): direction(Direction::RIGHT) {
}

Snake::~Snake() {
    map.clear();
    snake.clear();
}


void Snake::draw() const {
    for (const auto &part: snake) {
        DrawRectangle(MARGIN_X + part.x * GRID_STEP, MARGIN_Y + part.y * GRID_STEP, GRID_STEP, GRID_STEP, LIME);
    }
    switch (direction) {
        case Direction::UP:
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + EYE_MARGIN, EYE_SIZE, BLACK);
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + GRID_STEP - EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + EYE_MARGIN, EYE_SIZE, BLACK);
            break;
        case Direction::DOWN:
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + GRID_STEP - EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + GRID_STEP - EYE_MARGIN, EYE_SIZE, BLACK);
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + GRID_STEP - EYE_MARGIN, EYE_SIZE, BLACK);
            break;
        case Direction::LEFT:
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + GRID_STEP - EYE_MARGIN, EYE_SIZE, BLACK);
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + EYE_MARGIN, EYE_SIZE, BLACK);
            break;
        case Direction::RIGHT:
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + GRID_STEP - EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + EYE_MARGIN, EYE_SIZE, BLACK);
            DrawCircle(MARGIN_X + snake[0].x * GRID_STEP + GRID_STEP - EYE_MARGIN,
                       MARGIN_Y + snake[0].y * GRID_STEP + GRID_STEP - EYE_MARGIN, EYE_SIZE, BLACK);
            break;
    }
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
    if (fruit_position.x == new_head.x && fruit_position.y == new_head.y) {
        snake.push_front(new_head);
        map[new_head.x][new_head.y] = 1;
        return;
    }
    map[snake.back().x][snake.back().y] = 0;
    snake.pop_back();
    snake.push_front(new_head);
    if (snake.front().x < 0 || snake.front().y < 0 || snake.front().x >= GRID_SIZE_X || snake.front().y >=
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

void Snake::reset() {
    dead = false;
    map.clear();
    snake.clear();
    map = {GRID_SIZE_X, std::vector<short>(GRID_SIZE_Y, 0)};
    snake.push_back({GRID_SIZE_X / 2, GRID_SIZE_Y / 2});
}
