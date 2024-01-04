//
// Created by Tatry on 4. 1. 2024.
//

#ifndef POSGAMEOFLIFECLIENT_CONSOLEGUI_H
#define POSGAMEOFLIFECLIENT_CONSOLEGUI_H


#include "FormerWorlds.h"
#include "GameState.h"

class ConsoleGui {
private:
    FormerWorlds formerWorlds;
    GameState* gameState;
public:
    explicit ConsoleGui(GameState *gameState);
    void start();
};


#endif //POSGAMEOFLIFECLIENT_CONSOLEGUI_H
