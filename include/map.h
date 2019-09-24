#ifndef _Map_
#define _Map_

#include <vector>

class Frame;
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

    void inBoundPos(position& p);

    void floodFill(STATE s, Tile* target_tile);

    bool updateMap();

    Tile* getTile(int x, int y);

    void setTile(int x, int y, Tile* tile);

    std::pair<size_t, size_t> getMapSize();

    void drawMap(sf::RenderWindow* window);



    std::vector<Frame*> frame;
    std::vector<Enemy*> enemy;
private:
    int max_x;
    int max_y;
    std::vector<Tile*> coordinate_Map_;
    size_t white_tile_number_;
};
#endif