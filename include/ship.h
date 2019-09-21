#ifndef _Ship_
#define _Ship_

#include <vector>
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

class Ship {

public:
    Ship();
    ~Ship();

    virtual void up();
    virtual void down();
    virtual void left();
    virtual void right();
    std::list<position*> getTrace() {
        return trace;
    }

    bool undo() {
        if (!trace.empty()) {
            trace.pop_back();
            return true;
        } else {
            return false;
        }
    }

    position* getCurrentPos() {
        return current_pos;
    }
    bool undo_;
    void Ship::drawShip(sf::RenderWindow* window, int tile_size);
protected:
    int v;
    std::list<position*> trace;
    position* current_pos;

    DIRECTION direction;
    int velocity;
};

class ZetShip : public Ship {
public:
    ZetShip();
    ~ZetShip();
};

class BattleShip : public Ship {
public:
    BattleShip();
    ~BattleShip();

    std::vector<position*> misile;
};

#endif