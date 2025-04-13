//
// Created by dmytro2006 on 04/04/2025.
//

#ifndef CONFIG_H
#define CONFIG_H

constexpr int GRID_STEP = 30; // size of one grid cell
constexpr int MARGIN_X = 40; // left/right margin of the grid
constexpr int MARGIN_Y = 40; // top/bottom margin of the grid
constexpr int GRID_SIZE_X = 12; // number of cells (horizontal)
constexpr int GRID_SIZE_Y = 12; // number of cells (vertical)
constexpr int GAME_AREA_WIDTH = GRID_SIZE_X * GRID_STEP; // width of the grid in pixels
constexpr int GAME_AREA_HEIGHT = GRID_SIZE_Y * GRID_STEP; // height of the grid in pixels
constexpr int WIDTH = GAME_AREA_WIDTH + 2 * MARGIN_X; // width of the game window
constexpr int HEIGHT = GAME_AREA_HEIGHT + 2 * MARGIN_Y; // height of the game window
constexpr int EYE_MARGIN = GRID_STEP / 4; // distance from the edge of snake to the eyes in pixels
constexpr int EYE_SIZE = GRID_STEP / 7; // size of the eyes in pixels
constexpr float MAX_TIME = 0.5;
constexpr float MIN_TIME = 0.2;
constexpr float FRUIT_RADIUS = 5; // radius of the fruit in pixels
constexpr auto FRUIT_COLOR = RED; // color of the fruit

#endif //CONFIG_H
