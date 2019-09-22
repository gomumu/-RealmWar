#include "map.h"
#include "Tile.h"
#include "frame.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>

const int tile_size_ = 3;
Map::Map(int max_x, int max_y) : max_x(max_x), max_y(max_y){
    init();
}

Map::~Map() {
    coordinate_Map_.clear();
}

void Map::init() {
    for (int i = 0; i < max_y; ++i) {
        for (int j = 0; j < max_x; ++j) {
            Tile* t = nullptr;
            if (i == 0 || j == 0 || j == max_x - 1 || i == max_y - 1) {
                t = Tile::createTile(GREY_STATE);
            } else{
                t = Tile::createTile(WHITE_STATE);
            }
            coordinate_Map_.push_back(t);
        }
    }
}

std::pair<size_t, size_t> Map::getMapSize() {
    std::pair<size_t, size_t> map_size;
    size_t size = coordinate_Map_.size();
    size_t last_w = coordinate_Map_.at(size - 1)->getWidth();
    size_t last_h = coordinate_Map_.at(size - 1)->getheight();
    map_size = getCoordinate(coordinate_Map_.size() - 1, last_w, last_h);
    map_size.first += last_w;
    map_size.second += last_h;
    return map_size;
}


Tile* Map::getTile(int x, int y) {
    return coordinate_Map_.at(max_x * y + x);
}

std::pair<size_t, size_t> Map::getCoordinate(size_t idx, size_t tile_width, size_t tile_height) {
    std::pair<size_t, size_t> pos;
    pos.first = (idx % max_x) * tile_width;
    pos.second = (idx / max_x) * tile_height;
    return pos;
}

bool Map::updateMap() {

    for (auto f : frame) {
        f;
        std::list<position*> tmp = f->getTmp();
        position* p = f->getCurrentPos();
        bool realming = !tmp.empty();
        int x = p->first;
        int y = p->second;
        while (x < 0 || y < 0 || x > max_x || y > max_y) {
            break;
        }

        int pointer_x = x, pointer_y = y;
        Tile* tile = getTile(x, y);
        STATE state = tile->getState();
        switch (state) {
            case WHITE_STATE:{
                if (f->frame_type_ == BLUE_FRAME) {
                    getTile(x, y)->setState(BLUE_TEMP_STATE);
                } else if (f->frame_type_ == RED_FRAME) {
                    getTile(x, y)->setState(RED_TEMP_STATE);
                } else if (f->frame_type_ == YELLOW_FRAME) {
                    getTile(x, y)->setState(YELLOW_TEMP_STATE);
                } else if (f->frame_type_ == GREEN_FRAME) {
                    getTile(x, y)->setState(GREEN_TEMP_STATE);
                }
                break;
            }
            case GREY_STATE: {
                if (realming) {
                    for (auto pos : tmp) {
                        pos->first;
                        pos->second;
                    }
                    //cal
                }
                break;
            }
            case BLUE_STATE: {
                if (realming) {
                    for (auto pos : tmp) {
                        pos->first;
                        pos->second;
                    }
                    //cal
                }
                break;
            }
            case RED_STATE: {
                break;
            }
            case GREEN_STATE: {
                break;
            }
            case YELLOW_STATE: {
                break;
            }
            case BLUE_TEMP_STATE: {
                break;
            }
            case RED_TEMP_STATE: {
                break;
            }
            case GREEN_TEMP_STATE: {
                break;
            }
            case YELLOW_TEMP_STATE: {
                break;
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
    for (size_t i = 0; i < coordinate_Map_.size(); ++i) {
        Tile* t = coordinate_Map_.at(i);
        std::pair<size_t, size_t> pos = getCoordinate(i, t->getWidth(), t->getheight());
        if (t->getTileSprite() != nullptr) {
            t->drawTile(window, pos.first , pos.second);
        }
    }

    for (auto f : frame) {
        f->drawFrame(window);
    }
}