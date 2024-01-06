//
// Created by Tatry on 4. 1. 2024.
//

#include <iostream>
#include "../headers/ConsoleGui.h"

ConsoleGui::ConsoleGui(GameState& gameState) : gameState(gameState), formerWorlds(10) {}

void ConsoleGui::start() {
    world_t currentWorld = std::vector(5, std::vector(5, false));
    currentWorld.at(1).at(2) = true;
    currentWorld.at(2).at(1) = true;
    currentWorld.at(2).at(2) = true;
    currentWorld.at(2).at(3) = true;
    currentWorld.at(3).at(2) = true;

    this->gameState.insert_current_world(currentWorld);

    unsigned long long i = 0;
    while (i < 200)
    {
        currentWorld = this->gameState.retrieve_current_world();
        printWorldToConsole(currentWorld);
        this->gameState.start_generating_future_world();
        i++;
        std::cout << i << std::endl;
    }

    this->gameState.stop_simulation();

}

void ConsoleGui::printWorldToConsole(const world_t& world) {

}
