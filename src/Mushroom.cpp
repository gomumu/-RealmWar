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
    int x = current_pos.first;
    int y = current_pos.second - 1;
    current_pos = position(x, y);
}

void Mushroom::down() {
    int x = current_pos.first;
    int y = current_pos.second + 1;
    current_pos = position(x, y);
}

void Mushroom::left() {
    int x = current_pos.first - 1;
    int y = current_pos.second;
    current_pos = position(x, y);
}
void Mushroom::right() {
    int x = current_pos.first + 1;
    int y = current_pos.second;
    current_pos = position(x, y);
}

void Mushroom::drawMushroom(sf::RenderWindow* window) {
    sp->setTextureRect(sf::IntRect(mushroom_type_ * 36, 0, size_, size_));
    sp->setPosition(current_pos.first * Tile::getSize(), (float)current_pos.second * Tile::getSize());
    window->draw(*sp);
}