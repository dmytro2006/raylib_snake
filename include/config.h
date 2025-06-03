//
// Created by dmytro2006 on 04/04/2025.
//

#ifndef CONFIG_H
#define CONFIG_H

constexpr int GRID_STEP = 50; // size of one grid cell
constexpr int MARGIN_X = 40; // left/right margin of the grid
constexpr int MARGIN_Y = 40; // top/bottom margin of the grid
constexpr int GRID_SIZE_X = 12; // number of cells (horizontal)
constexpr int GRID_SIZE_Y = 12; // number of cells (vertical)
constexpr int GAME_AREA_WIDTH = GRID_SIZE_X * GRID_STEP; // width of the grid in pixels
constexpr int GAME_AREA_HEIGHT = GRID_SIZE_Y * GRID_STEP; // height of the grid in pixels
constexpr int WIDTH = GAME_AREA_WIDTH + 2 * MARGIN_X; // width of the game window
constexpr int HEIGHT = GAME_AREA_HEIGHT + 2 * MARGIN_Y; // height of the game window

constexpr int EYE_MARGIN = GRID_STEP / 3; // distance from the edge of snake to the eyes in pixels
constexpr int EYE_SIZE = GRID_STEP / 10; // size of the eyes in pixels

constexpr float FRUIT_RADIUS = GRID_STEP / 5; // radius of the fruit in pixels
constexpr auto FRUIT_COLOR = RED; // color of the fruit

constexpr int MAX_LENGTH = GRID_SIZE_X * GRID_SIZE_Y; // max length of the snake

constexpr float MAX_TIME = 0.5; // duration of 1 tick at the start of the game for the easy mode
constexpr float MIN_TIME = 0.3; // duration of 1 tick at the end of the game for the easy mode (i.e. when the snake is the longest possible)
constexpr float MEDIUM_MULTIPLIER = 0.75; // multiplier of max and min time for the medium mode
constexpr float HARD_MULTIPLIER = 0.5; // multiplier of max and min time for the hard mode

#endif //CONFIG_H
