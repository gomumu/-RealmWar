#include <SFML/Graphics.hpp>
#include "config.h"
#include "Tile.h"

Tile::Tile() : state(WHITE_STATE), sp(nullptr), width_(0), height_(0) {
}

Tile* Tile::createTile(STATE state) {
    Tile* tile = new Tile();
    tile->state = state;
    sf::Texture* texture = new sf::Texture();

    switch (state) {
    case WHITE_STATE:
        texture->loadFromFile(RESOURCE_PATH +"/images/white.png");
        break;
    case GREY_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/grey.png");
        break;
    case BLUE_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/blue.png");
        break;
    case BLUE_TEMP_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/blue_tmp.png");
        break;
    case RED_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/red.png");
        break;
    case RED_TEMP_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/red_tmp.png");
        break;
    case GREEN_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/green.png");
        break;
    case GREEN_TEMP_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/green_tmp.png");
        break;
    case YELLOW_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/yellow.png");
        break;
    case YELLOW_TEMP_STATE:
        texture->loadFromFile(RESOURCE_PATH + "/images/yellow_tmp.png");
        break;
    }

    sf::Sprite* sp = new sf::Sprite();
    sp->setTexture(*texture);
    tile->setSprite(sp);
    sf::Vector2u v = texture->getSize();
    tile->width_ = v.x;
    tile->height_ = v.y;

    return tile;
}
void Tile::drawTile(sf::RenderWindow* window, size_t pos_x, size_t pos_y) {
    sp->setPosition((float)pos_x, (float)pos_y);
    window->draw(*sp);
}