#include <SFML/Graphics.hpp>
#include "Tile.h"

Tile::Tile() : state(WHITE_STATE), tile_sp(nullptr), width_(0), height_(0) {
}

Tile* Tile::createTile(STATE state) {
    Tile* tile = new Tile();
    tile->state = state;
    sf::Texture* texture = new sf::Texture();

    switch (state) {
    case WHITE_STATE:
        texture->loadFromFile("../images/white.png");
        break;
    case GREY_STATE:
        texture->loadFromFile("../images/grey.png");
        break;
    case BLUE_STATE:
        texture->loadFromFile("../images/blue.png");
        break;
    case BLUE_TEMP_STATE:
        texture->loadFromFile("../images/blue_tmp.png");
        break;
    case RED_STATE:
        texture->loadFromFile("../images/red.png");
        break;
    case RED_TEMP_STATE:
        texture->loadFromFile("../images/red_tmp.png");
        break;
    case GREEN_STATE:
        texture->loadFromFile("../images/green.png");
        break;
    case GREEN_TEMP_STATE:
        texture->loadFromFile("../images/green_tmp.png");
        break;
    case YELLOW_STATE:
        texture->loadFromFile("../images/yellow.png");
        break;
    case YELLOW_TEMP_STATE:
        texture->loadFromFile("../images/yellow_tmp.png");
        break;
    }

    sf::Sprite* sp = new sf::Sprite();
    sp->setTexture(*texture);
    tile->setTileSprite(sp);
    sf::Vector2u v = texture->getSize();
    tile->width_ = v.x;
    tile->height_ = v.y;

    return tile;
}
void Tile::drawTile(sf::RenderWindow* window, size_t pos_x, size_t pos_y) {
    tile_sp->setPosition((float)pos_x, (float)pos_y);
    window->draw(*tile_sp);
}