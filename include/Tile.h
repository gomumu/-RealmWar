#ifndef _Tile_
#define _Tile_

enum STATE {
    BLACK_STATE = 0,
    GREY_STATE,
    RED_STATE,
    RED_TEMP_STATE,
    YELLOW_STATE,
    YELLOW_TEMP_STATE,
    GREEN_STATE,
    GREEN_TEMP_STATE,
    BLUE_STATE,
    BLUE_TEMP_STATE
};
namespace sf {
    class RenderWindow;
    class Sprite;
}

class Tile {
public:
    static Tile* createTile(STATE state);

    static void initTile();

    Tile();

    void drawTile(sf::RenderWindow* window, size_t pos_x, size_t pos_y);

    STATE getState() {
        return state;
    }

    void setState(STATE state);

    bool isChecked() {
        return checked;
    }

    void setChecked(bool checked) {
        this->checked = checked;
    }

    static size_t getSize() {
        return size_;
    }

private:
    STATE state;

    bool checked;

    static sf::Sprite* tile;

    static size_t size_;
};
#endif