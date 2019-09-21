#include "map.h"
#include "Tile.h"
#include "ship.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>

const int tile_size_ = 3;
Map::Map(int max_x, int max_y) {
    sf::Texture* tile = new sf::Texture();
    tile->loadFromFile("E:/study/1/xonix/images/tiles.png");
    Tile::tile_size = tile_size_;

    Tile::blue_tile->setTexture(*tile);
    Tile::blue_tile->setTextureRect(sf::IntRect(0, 0, Tile::tile_size, Tile::tile_size));

    Tile::purple_tile->setTexture(*tile);
    Tile::purple_tile->setTextureRect(sf::IntRect(18, 0, Tile::tile_size, Tile::tile_size));
    
    Tile::red_tile->setTexture(*tile);
    Tile::red_tile->setTextureRect(sf::IntRect(36, 0, Tile::tile_size, Tile::tile_size));

    Tile::green_tile->setTexture(*tile);
    Tile::green_tile->setTextureRect(sf::IntRect(54, 0, Tile::tile_size, Tile::tile_size));

    Tile::yellow_tile->setTexture(*tile);
    Tile::yellow_tile->setTextureRect(sf::IntRect(72, 0, Tile::tile_size, Tile::tile_size));

    Tile::skyblue_tile->setTexture(*tile);
    Tile::skyblue_tile->setTextureRect(sf::IntRect(90, 0, Tile::tile_size, Tile::tile_size));

    Tile::orange_tile->setTexture(*tile);
    Tile::orange_tile->setTextureRect(sf::IntRect(108, 0, Tile::tile_size, Tile::tile_size));

    this->max_x = max_x;
    this->max_y = max_y;

    for (int i = 0; i < max_y; ++i) {
        for (int j = 0; j < max_x; ++j) {
            Tile* t = new Tile(j, i);
            if (i == 0 || j == 0 || j == max_x - 1 || i == max_y - 1) {
                t->setState(GREEN_STATE);
            }
            coordinate.push_back(t);
        }
    }
}

Map::~Map() {
    coordinate.clear();
}

Tile* Map::getTile(int x, int y) {
    return coordinate.at(max_x * y + x);
}

int Map::getMapHorizontalSize() {
    return max_x * Tile::tile_size;
}

int Map::getMapverticalSize() {
    return max_y * Tile::tile_size;
}

bool Map::updateMap() {

    for (auto s : ship) {
        std::vector<position*> trace = s->getTrace();

        position* current_pos = s->getCurrentPos();
        int x = current_pos->first;
        int y = current_pos->second;
        while (x < 0 || y < 0 || x > max_x || y > max_y) {
            if (!s->undo()) return true;
            current_pos = s->getCurrentPos();
            x = current_pos->first;
            y = current_pos->second;
        }
        if (s->undo_) {
            if (s->undo()) {
                getTile(x, y)->setState(BLACK_STATE);
                return true;
            } else {
                s->undo_ = false;
                return true;
            }
        }
        for (auto position = trace.rbegin(); position != trace.rend(); ++position) {
            current_pos = s->getCurrentPos();
            int pointer_x = x, pointer_y = y;
            Tile* tile = getTile(pointer_x, pointer_y);
            STATE state = tile->getState();
            switch (state) {
                case BLACK_STATE:{
                    getTile(x,y)->setState(BLUE_STATE);
                    break;
                }
                case BLUE_STATE: {
                    //ground!
                    for (auto begin : trace) {

                    }
                    if (trace.size() > 1) {
                        current_pos = trace.back();
                        trace.clear();
                        trace.push_back(current_pos);
                        return true;
                    }
                    break;
                }
                case PURPLE_STATE: {
                    break;
                }
                case RED_STATE: {
                    break;
                }
                case GREEN_STATE: {
                    //ground!
                    for (auto begin : trace) {
                    
                    }
                    if (trace.size() > 1) {
                        current_pos = trace.back();
                        trace.clear();
                        trace.push_back(current_pos);
                        return true;
                    }
                    break;
                }
                case YELLOW_STATE: {
                    break;
                }
                case SKYBLUE_STATE: {
                    break;
                }
                case ORANGE_STATE: {
                    break;
                }

            }

        }

    }

    //for (auto e : enemy) {
    //    e->x += e->dx;
    //    if (e->x < 0) e->x = 0;
    //    if (e->x > max_x) e->x = max_x;
    //    e->y += e->dy;
    //    if (e->y < 0) e->y = 0;
    //    if (e->y > max_y) e->y = max_y;

    //    if (coordinate[e->x][e->y].getState() == RED_STATE) {
    //        return false;
    //    }

    //    if (coordinate[e->x][e->y].getState() == GREY_STATE) {
    //        e->dx = -(e->dx); e->x += e->dx;
    //    }
    //    if (coordinate[e->x][e->y].getState() == GREY_STATE) {
    //        e->dy = -e->dy; e->y += e->dy;
    //    }
    //}
    return true;
}

void Map::drawMap(sf::RenderWindow* window) {
    for (Tile* t : coordinate) {
        if (t->sTile != NULL) {
            t->drawTile(window);
        }
    }
    for (auto s : ship) {
        s->drawShip(window, tile_size_);
    }
}