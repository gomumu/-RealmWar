#ifndef _Tile_
#define _Tile_

enum STATE {
    BLACK_STATE = 0,
    BLUE_STATE,
    PURPLE_STATE,
    RED_STATE,
    GREEN_STATE,
    YELLOW_STATE,
    SKYBLUE_STATE,
    ORANGE_STATE
};

class Sprite;
class RenderWindow;

const int tile_size = 5;
Sprite sTile;

class Tile {
private:
public:
    int x;
    int y;
    STATE state;

    static int getTileSize() {
        return tile_size;
    };

    Tile(int x, int y);

    int getx() {
        return x;
    }
    int gety() {
        return y;
    }

    void drawTile(RenderWindow* window);

    STATE getState() {
        return state;
    }

    void setState(STATE state) {
        this->state = state;
    }
};
#endif