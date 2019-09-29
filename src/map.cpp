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
    enemy.clear();
    mushroom.clear();
}

void Map::init() {
    for (int i = 0; i < max_y; ++i) {
        for (int j = 0; j < max_x; ++j) {
            Tile* t = nullptr;
            if (i < 2 || j < 2 || j > max_x - 3 || i > max_y - 3) {
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

    std::vector<Enemy*> delete_enemy;

    for (auto m : mushroom) {
        int ts = m->getTileSize();
        position p = m->getCurrentPos();
        if (p.first < 0) {
            p.first = 0;
        } else if (p.first > max_x - ts) {
            p.first = max_x - ts;
        }

        if (p.second < 0) {
            p.second = 0;
        } else if (p.second > max_y - ts) {
            p.second = max_y - ts;
        }

        position pos = std::make_pair(p.first, p.second);
        m->setCurrentPos(pos);

        Tile* tile = getTile(p.first, p.second);
        STATE state = tile->getState();

        std::list<position> tmp = m->getTmp();
        switch (state) {
            case BLACK_STATE:{
                if (m->mushroom_type_ == BLUE_MUSHROOM) {
                    tile->setState(BLUE_TEMP_STATE);
                    setTile(p.first, p.second, tile);
                    if (!tmp.empty()) {
                        if (pos.first == tmp.back().first - 1, pos.second == tmp.back().second - 1) {
                            std::pair<int, int> correction_pos = std::make_pair(pos.first + 1, pos.second);
                            m->pushTmp(correction_pos);
                        }
                        else if (pos.first == tmp.back().first - 1, pos.second == tmp.back().second + 1) {
                            std::pair<int, int> correction_pos = std::make_pair(pos.first + 1, pos.second);
                            m->pushTmp(correction_pos);
                        }
                        else if (pos.first == tmp.back().first + 1, pos.second == tmp.back().second + 1) {
                            std::pair<int, int> correction_pos = std::make_pair(pos.first - 1, pos.second - 1);
                            m->pushTmp(correction_pos);
                        }
                        else if (pos.first == tmp.back().first + 1, pos.second == tmp.back().second - 1) {
                            std::pair<int, int> correction_pos = std::make_pair(pos.first - 1, pos.second - 1);
                            m->pushTmp(correction_pos);
                        }
                    }
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
                if (tmp.size() != 0) {
                    for (auto e : enemy) {
                        if (e->boss) {
                            floodFill(e->x, e->y);
                            for (auto tile : coordinate_Map_) {
                                if (!tile->isChecked()) {
                                    if (tile->getState() == BLUE_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                        tile->setState(BLUE_STATE);
                                    } else if (tile->getState() == RED_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                        tile->setState(RED_STATE);
                                    } else if (tile->getState() == YELLOW_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                        tile->setState(YELLOW_STATE);
                                    } else if (tile->getState() == GREEN_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                        tile->setState(GREEN_STATE);
                                    }
                                } else {
                                    tile->setChecked(false);
                                }
                            }
                            for (auto& e : enemy) {
                                Tile* t = getTile(e->x, e->y);
                                if (t->getState() == RED_STATE ||
                                    t->getState() == BLUE_STATE ||
                                    t->getState() == YELLOW_STATE ||
                                    t->getState() == GREEN_STATE) {
                                        delete_enemy.push_back(e);
                                }
                            }
                            break;
                        }
                    }
                    m->eraseAllTmp();
                }
                break;
            }
            case BLUE_STATE: {
                if (m->mushroom_type_ == BLUE_MUSHROOM) {
                    if (tmp.size() != 0) {
                        for (auto e : enemy) {
                            if (e->boss) {
                                floodFill(e->x, e->y);
                                for (auto tile : coordinate_Map_) {
                                    if (!tile->isChecked()) {
                                        if (tile->getState() == BLUE_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                            tile->setState(BLUE_STATE);
                                        }
                                        else if (tile->getState() == RED_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                            tile->setState(RED_STATE);
                                        }
                                        else if (tile->getState() == YELLOW_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                            tile->setState(YELLOW_STATE);
                                        }
                                        else if (tile->getState() == GREEN_TEMP_STATE || tile->getState() == BLACK_STATE) {
                                            tile->setState(GREEN_STATE);
                                        }
                                    } else {
                                        tile->setChecked(false);
                                    }
                                }
                                for (auto& e : enemy) {
                                    Tile* t = getTile(e->x, e->y);
                                    if (t->getState() == RED_STATE ||
                                        t->getState() == BLUE_STATE ||
                                        t->getState() == YELLOW_STATE ||
                                        t->getState() == GREEN_STATE) {
                                            delete_enemy.push_back(e);
                                    }
                                }
                                break;
                            }
                        }
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

    auto deleteEnemy = [this](Enemy* e) {
        for (auto iter = enemy.begin(); iter != enemy.end(); ++iter) {
            if (*iter == e) {
                enemy.erase(iter);
                return;
            }
        }};
    for_each(delete_enemy.begin(), delete_enemy.end(), deleteEnemy);

    for (auto& e : enemy) {
        Tile* t = getTile(e->x, e->y);
        if (t->getState() == RED_TEMP_STATE ||
            t->getState() == BLUE_TEMP_STATE ||
            t->getState() == YELLOW_TEMP_STATE ||
            t->getState() == GREEN_TEMP_STATE) {
            return false;
        }
        if (t->getState() == BLACK_STATE) {
            int dx = e->dx > 0 ? e->x + e->dx + e->getTileSize() : e->x + e->dx;
            Tile* tmp_t = getTile(dx, e->y);
            if (tmp_t->getState() == GREY_STATE || tmp_t->getState() == RED_STATE ||
                tmp_t->getState() == BLUE_STATE || tmp_t->getState() == YELLOW_STATE ||
                tmp_t->getState() == GREEN_STATE) {
                e->dx = -(e->dx);
                dx = e->dx > 0 ? e->x + e->dx + e->getTileSize() : e->x + e->dx;
            }

            int dy = e->dy > 0 ? e->y + e->dy + e->getTileSize() : e->y + e->dy;
            tmp_t = getTile(e->x, dy);
            if (tmp_t->getState() == GREY_STATE || tmp_t->getState() == RED_STATE ||
                tmp_t->getState() == BLUE_STATE || tmp_t->getState() == YELLOW_STATE ||
                tmp_t->getState() == GREEN_STATE) {
                e->dy = -(e->dy);
                dy = e->dy > 0 ? e->y + e->dy + e->getTileSize() : e->y + e->dy;
            }

            tmp_t = getTile(dx, dy);
            if (tmp_t->getState() == GREY_STATE || tmp_t->getState() == RED_STATE ||
                tmp_t->getState() == BLUE_STATE || tmp_t->getState() == YELLOW_STATE ||
                tmp_t->getState() == GREEN_STATE) {
                e->dy = -(e->dy);
                e->dx = -(e->dx);
            }
            e->x += e->dx;
            e->y += e->dy;
        }
    }
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