//
// Created by Tatry on 4. 1. 2024.
//

#include <iostream>
#include <sstream>
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

    std::string userInput;
    while (userInput.empty())
    {
        currentWorld = this->gameState.retrieve_current_world();
        this->gameState.start_generating_future_world();
        printWorldToConsole(currentWorld);

        std::cin >> userInput;
    }

    this->gameState.stop_simulation();

}

void ConsoleGui::printWorldToConsole(const world_t& world) {
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    for (const auto &row: world)
    {
        std::stringstream rowToPrint;
        for (const auto &cell: row)
        {
            if (cell)
            {
                rowToPrint << ".";
            }
            else
            {
                rowToPrint << "O";
            }
        }
        std::cout << rowToPrint.str() << std::endl;
    }
    std::cout << "-------------------------------------------------------------------" << std::endl;
}
