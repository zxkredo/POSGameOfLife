//
// Created by Tatry on 4. 1. 2024.
//

#ifndef POSGAMEOFLIFECLIENT_CONSOLEGUI_H
#define POSGAMEOFLIFECLIENT_CONSOLEGUI_H


#include "FormerWorlds.h"
#include "GameState.h"

class ConsoleGui {
    typedef std::vector<std::vector<bool>> world_t;
private:
    FormerWorlds formerWorlds;
    GameState& gameState;
public:
    explicit ConsoleGui(GameState& gameState);
    void start();
private:
    static void printWorldToConsole(const world_t& world);
};


#endif //POSGAMEOFLIFECLIENT_CONSOLEGUI_H
