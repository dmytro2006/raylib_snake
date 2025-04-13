//
// Created by dmytro2006 on 03/04/2025.
//

#include "game.h"
#include "config.h"

int main() {
    Game game("SNAKE", WIDTH, HEIGHT, 60);
    game.play();
    return 0;
}
