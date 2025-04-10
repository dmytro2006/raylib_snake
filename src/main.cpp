//
// Created by dmytro2006 on 03/04/2025.
//

#include <iostream>
#include <vector>

#include "ui.h"
#include "raylib.h"
#include "game.h"

int main() {
    Game game("SNAKE", 500,500, 60);
    game.play();
    return 0;
}
