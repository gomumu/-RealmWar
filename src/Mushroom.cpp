#include <SFML/Graphics.hpp>
#include <time.h>

#include "Mushroom.h"
#include "tile.h"

using namespace sf;

sf::Sprite* Mushroom::sp = nullptr;
size_t Mushroom::size_ = 0;
size_t Mushroom::tile_size_ = 0;

Mushroom::Mushroom() {
    current_pos = position(0, 0);
    direction = DIRECTION_NONE;
}

Mushroom* Mushroom::createMushroom(MUSHROOM_TYPE mushroom_t) {
    Mushroom* mushroom = new Mushroom();
    mushroom->mushroom_type_ = mushroom_t;
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile("../images/mushroom.png");
    sp = new sf::Sprite(*texture);
    sf::Vector2u v = texture->getSize();
    mushroom->size_ = v.y;
    mushroom->tile_size_ = v.y / Tile::getSize();
    return mushroom;
}

void Mushroom::up() {
    direction = DIRECTION_UP;
}

void Mushroom::down() {
    direction = DIRECTION_DOWN;
}

void Mushroom::left() {
    direction = DIRECTION_LEFT;
}
void Mushroom::right() {
    direction = DIRECTION_RIGHT;
}

void Mushroom::drawMushroom(sf::RenderWindow* window) {
    sp->setTextureRect(sf::IntRect(mushroom_type_ * 36, 0, size_, size_));
    sp->setPosition(current_pos.first * Tile::getSize(), (float)current_pos.second * Tile::getSize());
    window->draw(*sp);
}