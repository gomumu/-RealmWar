#include <SFML/Graphics.hpp>
#include <time.h>

#include "InputHandler.h"
#include "ship.h"
using namespace sf;


void UpCommand::execute(Ship* ship) { ship->up(); }
void DownCommand::execute(Ship* ship) { ship->down(); }
void LeftCommand::execute(Ship* ship) { ship->left(); }
void RightCommand::execute(Ship* ship) { ship->right(); }

void InputHandler::handleInput(Ship* ship) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        button_up_->execute(ship);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        button_down_->execute(ship);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        button_left_->execute(ship);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        button_right_->execute(ship);
    }
};
