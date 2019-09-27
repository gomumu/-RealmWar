#include <SFML/Graphics.hpp>
#include <time.h>

#include "enemy.h"
#include "map.h"
#include "tile.h"

using namespace sf;

Enemy::Enemy() {
}

Enemy* Enemy::createEnemy(int x, int y, bool boss) {
    Enemy* enemy = new Enemy();
    enemy->x = x / 2;
    enemy->y = y / 2;
    enemy->dx = 4 - rand() % 8;
    enemy->dy = 4 - rand() % 8;

    sf::Texture* texture = new sf::Texture();
    if (boss) {
        texture->loadFromFile("../images/enemy_boss.png");
    } else {
        texture->loadFromFile("../images/enemy.png");
    }
    enemy->sp = new sf::Sprite(*texture);
    sf::Vector2u v = texture->getSize();
    enemy->size_ = v.y;
    return enemy;
}

void Enemy::drawEnemy(sf::RenderWindow* window) {

    sp->setPosition(x * Tile::getSize(), y * Tile::getSize());
    window->draw(*sp);
}