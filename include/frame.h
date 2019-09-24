#ifndef _Frame_
#define _Frame_

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

enum FRAME_TYPE {
    BLUE_FRAME,
    RED_FRAME,
    GREEN_FRAME,
    YELLOW_FRAME,
};

class Frame {

public:
    Frame();
    ~Frame();

    static Frame* createFrame(FRAME_TYPE frame);

    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    std::list<position> getTmp() {
        return tmp;
    }

    position getCurrentPos() {
        return current_pos;
    }

    void setCurrentPos(position pos) {
        current_pos = pos;
    }

    void Frame::drawFrame(sf::RenderWindow* window);
    FRAME_TYPE frame_type_;

    void setFrameSprite(sf::Sprite* sp) {
        this->sp = sp;
    }

    sf::Sprite* getFrameSprite() {
        return sp;
    }

protected:
    std::list<position> tmp;
    position current_pos;
    DIRECTION direction;
    sf::Sprite* sp;
    size_t width_;
    size_t height_;
};


#endif