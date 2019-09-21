#ifndef _Input_Handler_
#define _Input_Handler_

#include "ship.h"

class Command {
public:
    virtual ~Command() {}
    virtual void execute(Ship* ship) = 0;
};

class UpCommand : public Command {
public:
    virtual void execute(Ship* ship);
};

class DownCommand : public Command {
public:
    virtual void execute(Ship* ship);
};

class LeftCommand : public Command {
public:
    virtual void execute(Ship* ship);
};

class RightCommand : public Command {
public:
    virtual void execute(Ship* ship);
};

class InputHandler {
public:
    InputHandler() {
        button_up_ = new UpCommand();
        button_down_ = new DownCommand();
        button_left_ = new LeftCommand();
        button_right_ = new RightCommand();
    }
    ~InputHandler() {
        delete button_up_;
        delete button_down_;
        delete button_left_;
        delete button_right_;
    }
    void handleInput(Ship* obj);

private:

    Command* button_up_;
    Command* button_down_;
    Command* button_left_;
    Command* button_right_;
};
#endif