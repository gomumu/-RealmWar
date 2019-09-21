#ifndef _Enemy_
#define _Enemy_

#include <vector>

typedef std::pair<int, int> position;

class Enemy {

public:
    Enemy(int x, int y);
    ~Enemy();
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
    int x;
    int y;
    int dx;
    int dy;
};

class ZetEnemy : public Enemy {
public:
    ZetEnemy();
    ~ZetEnemy();
};

class BattleEnemy : public Enemy {
public:
    BattleEnemy();
    ~BattleEnemy();

    std::vector<position*> misile;
};

#endif