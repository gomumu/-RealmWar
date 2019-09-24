#ifndef _Tile_
#define _Tile_

enum STATE {
    WHITE_STATE = 0,
    GREY_STATE,
    BLUE_STATE,
    BLUE_TEMP_STATE,
    RED_STATE,
    RED_TEMP_STATE,
    GREEN_STATE,
    GREEN_TEMP_STATE,
    YELLOW_STATE,
    YELLOW_TEMP_STATE,
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

    const size_t getWidth() const {
        return width_;
    }

    const size_t getheight() const {
        return height_;
    }

private:
    STATE state;

    static sf::Sprite* WHITE;
    static sf::Sprite* GREY;
    static sf::Sprite* BLUE;
    static sf::Sprite* BLUE_TEMP;
    static sf::Sprite* RED;
    static sf::Sprite* RED_TEMP;
    static sf::Sprite* YELLOW;
    static sf::Sprite* YELLOW_TEMP;
    static sf::Sprite* GREEN;
    static sf::Sprite* GREEN_TEMP;

    static size_t width_;
    static size_t height_;
};
#endif