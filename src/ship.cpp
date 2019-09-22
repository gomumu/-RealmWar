#include <SFML/Graphics.hpp>
#include <time.h>

#include "ship.h"

using namespace sf;

Ship::Ship() {
    //trace.push_back(new position(0, 0));
    //current_pos = trace.back();
    //v = 1;
    //sf::Texture* texture = new sf::Texture();
    //texture->loadFromFile("E:/study/1/xonix/images/spaceship2.png");

    //ship_ = new sf::Sprite(*texture);
    //undo_ = false;
}

void Ship::up() {
    for (int i = 0; i < v; ++i) {
        int x = current_pos->first;
        int y = current_pos->second - 1;
        for (auto pos : trace) {
            if (pos->first == x && pos->second == y) {
                undo_ = true;
            }
        }
        current_pos = new position(x, y);
        trace.push_back(current_pos);
    }
}

void Ship::down() {
    position* prev_pos = trace.back();
    for (int i = 0; i < v; ++i) {
        int x = current_pos->first;
        int y = current_pos->second + 1;
        for (auto pos : trace) {
            if (pos->first == x && pos->second == y) {
                undo_ = true;
            }
        }
        current_pos = new position(x, y);
        trace.push_back(current_pos);
    }
}

void Ship::left() {
    for (int i = 0; i < v; ++i) {
        int x = current_pos->first - 1;
        int y = current_pos->second;
        for (auto pos : trace) {
            if (pos->first == x && pos->second == y) {
                undo_ = true;
            }
        }
        current_pos = new position(x, y);
        trace.push_back(current_pos);
    }
}
void Ship::right() {
    for (int i = 0; i < v; ++i) {
        int x = current_pos->first + 1;
        int y = current_pos->second;
        for (auto pos : trace) {
            if (pos->first == x && pos->second == y) {
                undo_ = true;
                return;
            }
        }
        current_pos = new position(x, y);
        trace.push_back(current_pos);
    }
}


ZetShip::ZetShip() {
    v = 8;
}

BattleShip::BattleShip() {
    v = 4;
}

void Ship::drawShip(sf::RenderWindow* window, int tile_size) {
    //ship_->setPosition(current_pos->first*tile_size, current_pos->second*tile_size);
    //window->draw(*ship_);
}