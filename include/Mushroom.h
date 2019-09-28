#ifndef _Mushroom_
#define _Mushroom_

#include <list>

typedef std::pair<int,int> position;

enum DIRECTION {
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_NONE
};


namespace sf {
    class Sprite;
    class RenderWindow;
}

enum MUSHROOM_TYPE {
    RED_MUSHROOM = 0,
    BLUE_MUSHROOM,
    GREEN_MUSHROOM,
    YELLOW_MUSHROOM,
    BLACK_MUSHROOM
};

class Mushroom {

public:
    Mushroom();
    ~Mushroom();

    static Mushroom* createMushroom(MUSHROOM_TYPE mushroom);

    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    std::list<position> getTmp() {
        return tmp;
    }

    void pushTmp(position pos) {
        tmp.push_back(pos);
    }

    void eraseAllTmp() {
        tmp.clear();
    }


    position getCurrentPos() {
        return current_pos;
    }

    void setCurrentPos(position pos) {
        current_pos = pos;
    }

    void Mushroom::drawMushroom(sf::RenderWindow* window);
    MUSHROOM_TYPE mushroom_type_;

    static size_t getTileSize() {
        return tile_size_;
    }

    static size_t getSize() {
        return size_;
    }

protected:
    std::list<position> tmp;
    position current_pos;
    DIRECTION direction;
    static size_t size_;
    static size_t tile_size_;
    static sf::Sprite* sp;
};


#endif