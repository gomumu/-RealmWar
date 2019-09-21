#include <SFML/Graphics.hpp>
#include <time.h>
#include "config.h"
#include "Tile.h"

sf::Sprite* Tile::blue_tile = new sf::Sprite();
sf::Sprite* Tile::purple_tile = new sf::Sprite();
sf::Sprite* Tile::red_tile = new sf::Sprite();
sf::Sprite* Tile::green_tile = new sf::Sprite();
sf::Sprite* Tile::yellow_tile = new sf::Sprite();
sf::Sprite* Tile::skyblue_tile = new sf::Sprite();
sf::Sprite* Tile::orange_tile = new sf::Sprite();
int Tile::tile_size = 0;

Tile::Tile(int x, int y) : x(x), y(y) {
    state = BLACK_STATE;
    sTile = nullptr;
}

void Tile::drawTile(sf::RenderWindow* window) {

    sTile->setPosition(x*tile_size, y*tile_size);
    window->draw(*sTile);
    sTile->setPosition(0, 0);
}
