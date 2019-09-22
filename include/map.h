#ifndef _Map_
#define _Map_

#include <vector>

class Ship;
class Enemy;
class Tile;

namespace sf{
class RenderWindow;
}

class Map {
public:
    Map(int max_x, int max_y);
    ~Map();

    void init();

    int getMax_x() {
        return max_x;
    }
    int getMax_y() {
        return max_y;
    }
    std::vector<Tile*> getCoordinateMap() {
        return coordinate_Map_;
    }

    std::pair<size_t, size_t> Map::getCoordinate(size_t idx, size_t tile_width, size_t tile_height);

    bool updateMap();

    Tile* getTile(int x, int y);

    std::pair<size_t, size_t> getMapSize();

    void drawMap(sf::RenderWindow* window);



    std::vector<Ship*> ship;
    std::vector<Enemy*> enemy;
private:
    int max_x;
    int max_y;
    std::vector<Tile*> coordinate_Map_;
};
#endif