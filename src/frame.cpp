#include <SFML/Graphics.hpp>
#include <time.h>

#include "frame.h"

using namespace sf;

Frame::Frame() {
    current_pos = position(0, 0);
}

Frame* Frame::createFrame(FRAME_TYPE frame_t) {
    Frame* frame = new Frame();
    frame->frame_type_ = frame_t;
    sf::Texture* texture = new sf::Texture();

    switch (frame_t) {
    case BLUE_FRAME:
        texture->loadFromFile("../images/blue_frame.png");
        break;
    case RED_FRAME:
        texture->loadFromFile("../images/red_frame.png");
        break;
    case GREEN_FRAME:
        texture->loadFromFile("../images/green_frame.png");
        break;
    case YELLOW_FRAME:
        texture->loadFromFile("../images/yellow_frame.png");
        break;
    }

    sf::Sprite* sp = new sf::Sprite();
    sp->setTexture(*texture);
    frame->setFrameSprite(sp);
    sf::Vector2u v = texture->getSize();
    frame->width_ = v.x;
    frame->height_ = v.y;

    return frame;
}

void Frame::up() {
    int x = current_pos.first;
    int y = current_pos.second - 1;
    current_pos = position(x, y);
}

void Frame::down() {
    int x = current_pos.first;
    int y = current_pos.second + 1;
    current_pos = position(x, y);
}

void Frame::left() {
    int x = current_pos.first - 1;
    int y = current_pos.second;
    current_pos = position(x, y);
}
void Frame::right() {
    int x = current_pos.first + 1;
    int y = current_pos.second;
    current_pos = position(x, y);
}

void Frame::drawFrame(sf::RenderWindow* window) {
    sp->setPosition(current_pos.first*width_, (float)current_pos.second*height_);
    window->draw(*sp);
}