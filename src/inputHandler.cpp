#include <SFML/Graphics.hpp>
#include <time.h>

#include "InputHandler.h"
#include "frame.h"
using namespace sf;


void UpCommand::execute(Frame* frame) { frame->up(); }
void DownCommand::execute(Frame* frame) { frame->down(); }
void LeftCommand::execute(Frame* frame) { frame->left(); }
void RightCommand::execute(Frame* frame) { frame->right(); }

void InputHandler::handleInput(Frame* frame) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        button_up_->execute(frame);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        button_down_->execute(frame);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        button_left_->execute(frame);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        button_right_->execute(frame);
    }
};
