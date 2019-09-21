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
    int getMax_x() {
        return max_x;
    }
    int getMax_y() {
        return max_y;
    }
    std::vector<Tile*> getCoordinate() {
        return coordinate;
    }
    bool updateMap();

    Tile* getTile(int x, int y);

    int getMapHorizontalSize();

    int getMapverticalSize();

    void drawMap(sf::RenderWindow* window);



    std::vector<Ship*> ship;
    std::vector<Enemy*> enemy;
private:
    int max_x;
    int max_y;
    std::vector<Tile*> coordinate;
};
#endif