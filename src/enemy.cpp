#include <SFML/Graphics.hpp>
#include <time.h>

#include "enemy.h"

using namespace sf;

Enemy::Enemy(int x, int y) {
    this->x = x/2;
    this->y = y/2;
    dx = 4 - rand() % 8;
    dy = 4 - rand() % 8;
}