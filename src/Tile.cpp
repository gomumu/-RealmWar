#include <SFML/Graphics.hpp>
#include "Tile.h"

sf::Sprite* Tile::WHITE = nullptr;
sf::Sprite* Tile::GREY = nullptr;
sf::Sprite* Tile::BLUE = nullptr;
sf::Sprite* Tile::BLUE_TEMP = nullptr;
sf::Sprite* Tile::RED = nullptr;
sf::Sprite* Tile::RED_TEMP = nullptr;
sf::Sprite* Tile::YELLOW = nullptr;
sf::Sprite* Tile::YELLOW_TEMP = nullptr;
sf::Sprite* Tile::GREEN = nullptr;
sf::Sprite* Tile::GREEN_TEMP = nullptr;

size_t Tile::width_ = 0;
size_t Tile::height_ = 0;

Tile::Tile() : state(WHITE_STATE) {
}

Tile* Tile::createTile(STATE state) {
    Tile* tile = new Tile();
    tile->setState(state);
    return tile;
}

void Tile::initTile() {

    // WHITE
    sf::Texture* white_texture = new sf::Texture();
    white_texture->loadFromFile("../images/white.png");
    WHITE = new sf::Sprite();
    WHITE->setTexture(*white_texture);

    sf::Vector2u size = white_texture->getSize();
    width_ = size.x;
    height_ = size.y;

    // GREY
    sf::Texture* grey_texture = new sf::Texture();
    grey_texture->loadFromFile("../images/grey.png");
    GREY = new sf::Sprite();
    GREY->setTexture(*grey_texture);

    // BLUE
    sf::Texture* blue_texture = new sf::Texture();
    blue_texture->loadFromFile("../images/blue.png");
    BLUE = new sf::Sprite();
    BLUE->setTexture(*blue_texture);

    // BLUE_TEMP
    sf::Texture* blue_tmp_texture = new sf::Texture();
    blue_tmp_texture->loadFromFile("../images/blue_tmp.png");
    BLUE_TEMP = new sf::Sprite();
    BLUE_TEMP->setTexture(*blue_tmp_texture);

    // RED
    sf::Texture* red_texture = new sf::Texture();
    red_texture->loadFromFile("../images/red.png");
    RED = new sf::Sprite();
    RED->setTexture(*red_texture);

    // RED_TEMP
    sf::Texture* red_tmp_texture = new sf::Texture();
    red_tmp_texture->loadFromFile("../images/red_tmp.png");
    RED_TEMP = new sf::Sprite();
    RED_TEMP->setTexture(*red_tmp_texture);

    // GREEN
    sf::Texture* green_texture = new sf::Texture();
    green_texture->loadFromFile("../images/green.png");
    GREEN = new sf::Sprite();
    GREEN->setTexture(*green_texture);

    // GREEN_TEMP
    sf::Texture* green_tmp_texture = new sf::Texture();
    green_tmp_texture->loadFromFile("../images/green_tmp.png");
    GREEN_TEMP = new sf::Sprite();
    GREEN_TEMP->setTexture(*green_tmp_texture);

    // YELLOW
    sf::Texture* yellow_texture = new sf::Texture();
    yellow_texture->loadFromFile("../images/yellow.png");
    YELLOW = new sf::Sprite();
    YELLOW->setTexture(*yellow_texture);

    // YELLOW_TEMP
    sf::Texture* yellow_tmp_texture = new sf::Texture();
    yellow_tmp_texture->loadFromFile("../images/yellow_tmp.png");
    YELLOW_TEMP = new sf::Sprite();
    YELLOW_TEMP->setTexture(*yellow_tmp_texture);

}

void Tile::setState(STATE state) {
    this->state = state;
}

void Tile::drawTile(sf::RenderWindow* window, size_t pos_x, size_t pos_y) {

    sf::Sprite* tile_sp = nullptr;
    switch (state) {
    case WHITE_STATE:
        tile_sp = WHITE;
        break;
    case GREY_STATE:
        tile_sp = GREY;
        break;
    case BLUE_STATE:
        tile_sp = BLUE;
        break;
    case BLUE_TEMP_STATE:
        tile_sp = BLUE_TEMP;
        break;
    case RED_STATE:
        tile_sp = RED;
        break;
    case RED_TEMP_STATE:
        tile_sp = RED_TEMP;
        break;
    case GREEN_STATE:
        tile_sp = GREEN;
        break;
    case GREEN_TEMP_STATE:
        tile_sp = GREEN_TEMP;
        break;
    case YELLOW_STATE:
        tile_sp = YELLOW;
        break;
    case YELLOW_TEMP_STATE:
        tile_sp = YELLOW_TEMP;
        break;
    }
    if (tile_sp) {
        tile_sp->setPosition((float)pos_x, (float)pos_y);
        window->draw(*tile_sp);
    }
}