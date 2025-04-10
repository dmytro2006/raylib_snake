//
// Created by dmytro2006 on 04/04/2025.
//

#ifndef CONFIG_H
#define CONFIG_H

constexpr int GRID_STEP = 30;
constexpr int GAME_AREA_X = 40;
constexpr int GAME_AREA_Y = 40;
constexpr int WIDTH = 500;
constexpr int HEIGHT = 500;
constexpr int GAME_AREA_WIDTH = 420;
constexpr int GAME_AREA_HEIGHT = 420;
constexpr int GRID_SIZE_X = GAME_AREA_WIDTH / GRID_STEP;
constexpr int GRID_SIZE_Y = GAME_AREA_HEIGHT / GRID_STEP;
constexpr int EYE_MARGIN = GRID_STEP / 4;
constexpr int EYE_SIZE = GRID_STEP / 7;
constexpr float MAX_TIME = 0.5;
constexpr float MIN_TIME = 0.2;
constexpr float APPLE_RADIUS = 5;
constexpr auto APPLE_COLOR = RED;

#endif //CONFIG_H
