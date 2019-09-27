#include <SFML/Graphics.hpp>
#include <time.h>

#include "InputHandler.h"
#include "Mushroom.h"
using namespace sf;


void UpCommand::execute(Mushroom* mushroom) { mushroom->up(); }
void DownCommand::execute(Mushroom* mushroom) { mushroom->down(); }
void LeftCommand::execute(Mushroom* mushroom) { mushroom->left(); }
void RightCommand::execute(Mushroom* mushroom) { mushroom->right(); }

void InputHandler::handleInput(Mushroom* mushroom) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        button_up_->execute(mushroom);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        button_down_->execute(mushroom);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        button_left_->execute(mushroom);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        button_right_->execute(mushroom);
    }
};
