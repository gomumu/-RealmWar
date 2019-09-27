#ifndef _Enemy_
#define _Enemy_

#include <vector>

namespace sf {
    class Sprite;
    class RenderWindow;
}

class Enemy {

public:
    Enemy();
    ~Enemy();

    static Enemy* createEnemy(int x, int y, bool boss);

    void move();

    int getx() {
        return x;
    }
    int gety() {
        return y;
    }
    int getdx() {
        return dx;
    }
    int getdy() {
        return dy;
    }
    size_t getSize() {
        return size_;
    }

    void Enemy::drawEnemy(sf::RenderWindow* window);

    int x;
    int y;
    int dx;
    int dy;
    sf::Sprite* sp;
    size_t size_;
};

#endif