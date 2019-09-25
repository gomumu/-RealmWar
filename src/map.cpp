#include "map.h"
#include "Tile.h"
#include "frame.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

Map::Map(int max_x, int max_y) : max_x(max_x), max_y(max_y), white_tile_number_(0){
    init();
    Tile::initTile();
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
                ++white_tile_number_;
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
    size_t idx = max_x * y + x;
    if (idx < 0 || idx > coordinate_Map_.size()) return nullptr;
    return coordinate_Map_.at(max_x * y + x);
}

void Map::setTile(int x, int y, Tile* tile) {
    size_t idx = max_x * y + x;
    if (idx < 0 || idx > coordinate_Map_.size()) return;
    coordinate_Map_.at(max_x * y + x) = tile;
}

std::pair<size_t, size_t> Map::getCoordinate(size_t idx, size_t tile_width, size_t tile_height) {
    std::pair<size_t, size_t> pos;
    pos.first = (idx % max_x) * tile_width;
    pos.second = (idx / max_x) * tile_height;
    return pos;
}


//Flood - fill(node, target - color, replacement - color) :
//    1. If target - color is equal to replacement - color, return.
//    2. If color of node is not equal to target - color, return.
//    3. Set Q to the empty queue.
//    4. Set the color of node to replacement - color.
//    5. Add node to the end of Q.
//    6. While Q is not empty:
//7.     Set n equal to the first element of Q.
//8.     Remove first element from Q.
//9.     If the color of the node to the west of n is target - color,
//set the color of that node to replacement - color and add that node to the end of Q.
//10.     If the color of the node to the east of n is target - color,
//set the color of that node to replacement - color and add that node to the end of Q.
//11.     If the color of the node to the north of n is target - color,
//set the color of that node to replacement - color and add that node to the end of Q.
//12.     If the color of the node to the south of n is target - color,
//set the color of that node to replacement - color and add that node to the end of Q.
//13. Continue looping until Q is exhausted.
//14. Return.

//Flood - fill(node, target - color, replacement - color) :
//    1. If target - color is equal to replacement - color, return.
//    2. If color of node is not equal to target - color, return.
//    3. Set Q to the empty queue.
//    4. Add node to Q.
//    5. For each element N of Q :
//6.     Set w and e equal to N.
//7.     Move w to the west until the color of the node to the west of w no longer matches target - color.
//8.     Move e to the east until the color of the node to the east of e no longer matches target - color.
//9.     For each node n between w and e :
//    10.         Set the color of n to replacement - color.
//    11.         If the color of the node to the north of n is target - color, add that node to Q.
//    12.         If the color of the node to the south of n is target - color, add that node to Q.
//    13. Continue looping until Q is exhausted.
//    14. Return.

void Map::floodFill(size_t x, size_t y) {
    Tile* target_tile = getTile(x, y);
    if (target_tile && target_tile->getState() == WHITE_STATE && !target_tile->isChecked()) {
        target_tile->setChecked(true);
        floodFill(x - 1, y);
        floodFill(x + 1, y);
        floodFill(x, y - 1);
        floodFill(x, y + 1);
    }
}

bool Map::updateMap() {

    auto white_count = [](Tile* tile) -> bool {if (tile->getState() == WHITE_STATE) return true; };

    for (auto f : frame) {
        std::list<position> tmp = f->getTmp();
        position p = f->getCurrentPos();
        if (p.first < 0) {
            p.first = 0;
        } else if (p.first > max_x - 1) {
            p.first = max_x - 1;
        }

        if (p.second < 0) {
            p.second = 0;
        } else if (p.second > max_y - 1) {
            p.second = max_y - 1;
        }

        position pos = std::make_pair(p.first, p.second);
        f->setCurrentPos(pos);

        Tile* tile = getTile(p.first, p.second);
        STATE state = tile->getState();

        switch (state) {
            case WHITE_STATE:{
                if (f->frame_type_ == BLUE_FRAME) {
                    tile->setState(BLUE_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    f->pushTmp(pos);
                } else if (f->frame_type_ == RED_FRAME) {
                    tile->setState(RED_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    f->pushTmp(pos);
                } else if (f->frame_type_ == YELLOW_FRAME) {
                    tile->setState(YELLOW_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    f->pushTmp(pos);
                } else if (f->frame_type_ == GREEN_FRAME) {
                    tile->setState(GREEN_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    f->pushTmp(pos);
                }
                break;
            }
            case GREY_STATE: {
                size_t total_white = count_if(coordinate_Map_.begin(), coordinate_Map_.end(), white_count);
                if (tmp.size() != 0) {
                    for (auto p : tmp) {
                        if (getTile(p.first - 1, p.second)->getState() == WHITE_STATE) {
                            floodFill(p.first - 1, p.second);
                            break;
                        }
                        else if (getTile(p.first + 1, p.second)->getState() == WHITE_STATE) {
                            floodFill(p.first + 1, p.second);
                            break;
                        }
                        else if (getTile(p.first, p.second - 1)->getState() == WHITE_STATE) {
                            floodFill(p.first, p.second - 1);
                            break;
                        }
                        else if (getTile(p.first, p.second + 1)->getState() == WHITE_STATE) {
                            floodFill(p.first, p.second + 1);
                            break;
                        }
                    }
                    auto white_count = [](Tile* tile) -> bool {if (tile->isChecked()) return true; };
                    size_t flood_fill_size = count_if(coordinate_Map_.begin(), coordinate_Map_.end(), white_count);
                    bool use_checked = flood_fill_size < total_white - flood_fill_size;
                    for (auto tile : coordinate_Map_) {
                        if (tile->getState() == WHITE_STATE) {
                            if ((use_checked && tile->isChecked()) || (!use_checked && !tile->isChecked())) {
                                tile->setState(BLUE_STATE);
                            } else {
                                tile->setChecked(false);
                            }
                        }
                    }
                    for (auto t : tmp) {
                        Tile * tile = getTile(t.first, t.second);
                        tile->setState(BLUE_STATE);
                    }
                    f->eraseAllTmp();
                }
                break;
            }
            case BLUE_STATE: {
                if (f->frame_type_ == BLUE_FRAME) {
                    if (!tmp.empty()) {
                        for (auto pos : tmp) {
                            //pos->first;
                            //pos->second;
                        }
                        // cal
                    }
                } else {
                    // destory
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
        t->drawTile(window, pos.first , pos.second);
    }

    for (auto f : frame) {
        f->drawFrame(window);
    }
}