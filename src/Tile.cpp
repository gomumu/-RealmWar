#include <SFML/Graphics.hpp>
#include "Tile.h"

size_t Tile::size_ = 0;
sf::Sprite* Tile::tile = nullptr;

Tile::Tile() : state(BLACK_STATE), checked(false) {
}

Tile* Tile::createTile(STATE state) {
    Tile* tile = new Tile();
    tile->setState(state);
    return tile;
}

void Tile::initTile() {

    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile("../images/tiles.png");
    tile = new sf::Sprite();
    tile->setTexture(*texture);

    sf::Vector2u size = texture->getSize();
    size_ = size.y;
}

void Tile::setState(STATE state) {
    this->state = state;
}

void Tile::drawTile(sf::RenderWindow* window, size_t pos_x, size_t pos_y) {
    int x = state * 18;
    tile->setTextureRect(sf::IntRect(state * 18, 0, size_, size_));
    tile->setPosition((float)pos_x, (float)pos_y);
    window->draw(*tile);
}