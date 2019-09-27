#include "map.h"
#include "Tile.h"
#include "Mushroom.h"
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
            if (i < 2 || j < 2 || j > max_x - 2 || i > max_y - 3) {
                t = Tile::createTile(GREY_STATE);
            } else{
                t = Tile::createTile(BLACK_STATE);
                ++white_tile_number_;
            }
            coordinate_Map_.push_back(t);
        }
    }
}

std::pair<size_t, size_t> Map::getMapSize() {
    std::pair<size_t, size_t> map_size;
    size_t size = coordinate_Map_.size();
    size_t last_size = coordinate_Map_.at(size - 1)->getSize();
    map_size = getCoordinate(coordinate_Map_.size() - 1, last_size, last_size);
    map_size.first += last_size;
    map_size.second += last_size;
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


void Map::floodFill(size_t x, size_t y) {
    Tile* target_tile = getTile(x, y);
    if (target_tile && target_tile->getState() == BLACK_STATE && !target_tile->isChecked()) {
        target_tile->setChecked(true);
        floodFill(x - 1, y);
        floodFill(x + 1, y);
        floodFill(x, y - 1);
        floodFill(x, y + 1);
    }
}


bool Map::updateMap() {

    auto white_count = [](Tile* tile) -> bool {if (tile->getState() == BLACK_STATE) return true; };

    for (auto m : mushroom) {
        std::list<position> tmp = m->getTmp();
        position p = m->getCurrentPos();
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
        m->setCurrentPos(pos);

        Tile* tile = getTile(p.first, p.second);
        STATE state = tile->getState();

        switch (state) {
            case BLACK_STATE:{
                if (m->mushroom_type_ == BLUE_MUSHROOM) {
                    tile->setState(BLUE_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    m->pushTmp(pos);
                } else if (m->mushroom_type_ == RED_MUSHROOM) {
                    tile->setState(RED_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    m->pushTmp(pos);
                } else if (m->mushroom_type_ == YELLOW_MUSHROOM) {
                    tile->setState(YELLOW_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    m->pushTmp(pos);
                } else if (m->mushroom_type_ == GREEN_MUSHROOM) {
                    tile->setState(GREEN_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    m->pushTmp(pos);
                }
                break;
            }
            case GREY_STATE: {
                size_t total_white = count_if(coordinate_Map_.begin(), coordinate_Map_.end(), white_count);
                if (tmp.size() != 0) {
                    for (auto p : tmp) {
                        if (getTile(p.first - 1, p.second)->getState() == BLACK_STATE) {
                            floodFill(p.first - 1, p.second);
                            break;
                        }
                        else if (getTile(p.first + 1, p.second)->getState() == BLACK_STATE) {
                            floodFill(p.first + 1, p.second);
                            break;
                        }
                        else if (getTile(p.first, p.second - 1)->getState() == BLACK_STATE) {
                            floodFill(p.first, p.second - 1);
                            break;
                        }
                        else if (getTile(p.first, p.second + 1)->getState() == BLACK_STATE) {
                            floodFill(p.first, p.second + 1);
                            break;
                        }
                    }
                    auto white_count = [](Tile* tile) -> bool {if (tile->isChecked()) return true; };
                    size_t flood_fill_size = count_if(coordinate_Map_.begin(), coordinate_Map_.end(), white_count);
                    bool use_checked = flood_fill_size < total_white - flood_fill_size;
                    for (auto tile : coordinate_Map_) {
                        if (tile->getState() == BLACK_STATE) {
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
                    m->eraseAllTmp();
                }
                break;
            }
            case BLUE_STATE: {
                if (m->mushroom_type_ == BLUE_MUSHROOM) {
                    size_t total_white = count_if(coordinate_Map_.begin(), coordinate_Map_.end(), white_count);
                    if (tmp.size() != 0) {
                        for (auto p : tmp) {
                            if (getTile(p.first - 1, p.second)->getState() == BLACK_STATE) {
                                floodFill(p.first - 1, p.second);
                                break;
                            }
                            else if (getTile(p.first + 1, p.second)->getState() == BLACK_STATE) {
                                floodFill(p.first + 1, p.second);
                                break;
                            }
                            else if (getTile(p.first, p.second - 1)->getState() == BLACK_STATE) {
                                floodFill(p.first, p.second - 1);
                                break;
                            }
                            else if (getTile(p.first, p.second + 1)->getState() == BLACK_STATE) {
                                floodFill(p.first, p.second + 1);
                                break;
                            }
                        }
                        auto white_count = [](Tile* tile) -> bool {if (tile->isChecked()) return true; };
                        size_t flood_fill_size = count_if(coordinate_Map_.begin(), coordinate_Map_.end(), white_count);
                        bool use_checked = flood_fill_size < total_white - flood_fill_size;
                        for (auto tile : coordinate_Map_) {
                            if (tile->getState() == BLACK_STATE) {
                                if ((use_checked && tile->isChecked()) || (!use_checked && !tile->isChecked())) {
                                    tile->setState(BLUE_STATE);
                                }
                                else {
                                    tile->setChecked(false);
                                }
                            }
                        }
                        for (auto t : tmp) {
                            Tile * tile = getTile(t.first, t.second);
                            tile->setState(BLUE_STATE);
                        }
                        m->eraseAllTmp();
                    }
                    break;
                }
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

    std::vector<Enemy*> delete_enemy;

    for (auto& e : enemy) {
        Tile* t = getTile(e->x, e->y);
        if (t->getState() == RED_STATE ||
            t->getState() == BLUE_STATE ||
            t->getState() == YELLOW_STATE ||
            t->getState() == GREEN_STATE) {
            delete_enemy.push_back(e);
        }

        e->x += e->dx;
        if (e->x < 0) e->x = 0;
        if (e->x > max_x) e->x = max_x;
        e->y += e->dy;
        if (e->y < 0) e->y = 0;
        if (e->y > max_y) e->y = max_y;

        t = getTile(e->x, e->y);
        if (t->getState() == RED_TEMP_STATE ||
            t->getState() == BLUE_TEMP_STATE ||
            t->getState() == YELLOW_TEMP_STATE ||
            t->getState() == GREEN_TEMP_STATE) {
            return false;
        }

        if (t->getState() == GREY_STATE || t->getState() == RED_STATE ||
            t->getState() == BLUE_STATE || t->getState() == YELLOW_STATE ||
            t->getState() == GREEN_STATE) {
            if (e->x < 2 || e->x > max_x - 2) {
                e->dx = -(e->dx); e->x += e->dx;
            }
            if(e->y < 2 || e->y > max_y - 2){
                e->dy = -e->dy; e->y += e->dy;
            }
        }
    }

    auto deleteEnemy = [this] (Enemy* e) {
        for (auto iter = enemy.begin(); iter != enemy.end(); ++iter) {
            if (*iter == e) {
                enemy.erase(iter);
                return;
            }
        }};
    for_each(delete_enemy.begin(), delete_enemy.end(), deleteEnemy);
    return true;
}

void Map::drawMap(sf::RenderWindow* window) {
    for (size_t i = 0; i < coordinate_Map_.size(); ++i) {
        Tile* t = coordinate_Map_.at(i);
        std::pair<size_t, size_t> pos = getCoordinate(i, t->getSize(), t->getSize());
        t->drawTile(window, pos.first , pos.second);
    }

    for (auto m : mushroom) {
        m->drawMushroom(window);
    }

    for (auto e : enemy) {
        e->drawEnemy(window);
    }
}