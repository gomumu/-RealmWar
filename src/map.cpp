#include "map.h"
#include "Tile.h"
#include "ship.h"
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
            Tile* t = Tile::createTile(WHITE_STATE);
            if (i == 0 || j == 0 || j == max_x - 1 || i == max_y - 1) {
                t->setState(GREY_STATE);
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
    // ¹Ì±¸Çö
    //for (auto s : ship) {
    //    std::vector<position*> trace = s->getTrace();

    //    position* current_pos = s->getCurrentPos();
    //    int x = current_pos->first;
    //    int y = current_pos->second;
    //    while (x < 0 || y < 0 || x > max_x || y > max_y) {
    //        if (!s->undo()) return true;
    //        current_pos = s->getCurrentPos();
    //        x = current_pos->first;
    //        y = current_pos->second;
    //    }
    //    if (s->undo_) {
    //        if (s->undo()) {
    //            getTile(x, y)->setState(BLACK_STATE);
    //            return true;
    //        } else {
    //            s->undo_ = false;
    //            return true;
    //        }
    //    }
    //    for (auto position = trace.rbegin(); position != trace.rend(); ++position) {
    //        current_pos = s->getCurrentPos();
    //        int pointer_x = x, pointer_y = y;
    //        Tile* tile = getTile(pointer_x, pointer_y);
    //        STATE state = tile->getState();
    //        switch (state) {
    //            case BLACK_STATE:{
    //                getTile(x,y)->setState(BLUE_STATE);
    //                break;
    //            }
    //            case BLUE_STATE: {
    //                //ground!
    //                for (auto begin : trace) {

    //                }
    //                if (trace.size() > 1) {
    //                    current_pos = trace.back();
    //                    trace.clear();
    //                    trace.push_back(current_pos);
    //                    return true;
    //                }
    //                break;
    //            }
    //            case RED_STATE: {
    //                break;
    //            }
    //            case GREEN_STATE: {
    //                //ground!
    //                for (auto begin : trace) {
    //                
    //                }
    //                if (trace.size() > 1) {
    //                    current_pos = trace.back();
    //                    trace.clear();
    //                    trace.push_back(current_pos);
    //                    return true;
    //                }
    //                break;
    //            }
    //            case YELLOW_STATE: {
    //                break;
    //            }

    //        }

    //    }

    //}

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
        if (t->getSprite() != nullptr) {
            t->drawTile(window, pos.first , pos.second);
        }
    }

    //for (auto s : ship) {
    //    s->drawShip(window, tile_size_);
    //}
}