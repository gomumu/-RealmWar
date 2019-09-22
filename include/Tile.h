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

    Tile();

    void drawTile(sf::RenderWindow* window, size_t pos_x, size_t pos_y);

    STATE getState() {
        return state;
    }

    void setState(STATE state) {
        this->state = state;
    }

    void setSprite(sf::Sprite* sp) {
        this->sp = sp;
    }

    sf::Sprite* getSprite() {
        return sp;
    }

    const size_t getWidth() const {
        return width_;
    }

    const size_t getheight() const {
        return height_;
    }

private:
    STATE state;
    sf::Sprite* sp;
    size_t width_;
    size_t height_;
};
#endif