//
// Created by olafurj on 11/07/18.
//

#ifndef NAME_GAME_H
#define NAME_GAME_H

#include "window.h"
#include <stdint-gcc.h>

class Game {

public:
    Game(uint32_t height, uint32_t width) :
            window( new Window( "test", width, height )) {

    }

    ~Game() {
        delete ( this->window );
    }

private:
    Window *window;
};


#endif //NAME_GAME_H
