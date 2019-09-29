#include <SFML/Graphics.hpp>
#include <time.h>

#include "enemy.h"
#include "map.h"
#include "tile.h"

using namespace sf;

Enemy::Enemy() : x(0), y(0), dx(0), dy(0), boss(false) {
}

Enemy* Enemy::createEnemy(int x, int y, bool boss) {
    Enemy* enemy = new Enemy();
    enemy->x = x / 2;
    enemy->y = y / 2;
    enemy->boss = true;

    while (enemy->dx == 0 || enemy->dy == 0) {
        enemy->dx = 2 - rand() % 4;
        enemy->dy = 2 - rand() % 4;
    }
    sf::Texture* texture = new sf::Texture();
    if (boss) {
        texture->loadFromFile("../images/enemy_boss.png");
    } else {
        texture->loadFromFile("../images/enemy.png");
    }
    enemy->sp = new sf::Sprite(*texture);
    sf::Vector2u v = texture->getSize();
    if (boss) {
        enemy->size_ = v.y;
        enemy->tile_size_ = v.y / Tile::getSize();
    } else {
        enemy->size_ = v.x;
        enemy->tile_size_ = v.x / Tile::getSize();
    }
    return enemy;
}

void Enemy::drawEnemy(sf::RenderWindow* window) {

    sp->setPosition(x * Tile::getSize(), y * Tile::getSize());
    window->draw(*sp);
}