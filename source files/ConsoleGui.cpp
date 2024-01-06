//
// Created by Tatry on 4. 1. 2024.
//

#include <iostream>
#include <sstream>
#include <windows.h>
#include "../headers/ConsoleGui.h"

ConsoleGui::ConsoleGui(GameState& gameState) : gameState(gameState), formerWorlds(10) {}

void ConsoleGui::start() {
    world_t startingWorld = std::vector(10, std::vector(100, false));
    startingWorld.at(1+3).at(2+30) = true;
    startingWorld.at(2+3).at(1+30) = true;
    startingWorld.at(2+3).at(2+30) = true;
    startingWorld.at(2+3).at(3+30) = true;
    startingWorld.at(3+3).at(2+30) = true;

    this->gameState.insert_current_world(startingWorld);

    std::string userInput = "a";
    while (userInput == "a")
    {
        this->formerWorlds.add(this->gameState.retrieve_current_world());
        this->gameState.start_generating_future_world();
        printWorldToConsole(this->formerWorlds.getNewest());
        std::cin >> userInput;
    }

    this->gameState.stop_simulation();

}

void ConsoleGui::printWorldToConsole(const world_t& world) {
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), COORD{ 0, 0 } );
    std::cout << std::endl << std::endl << std::endl;
    for (const auto &row: world)
    {
        std::stringstream rowToPrint;
        for (const auto &cell: row)
        {
            if (cell)
            {
                rowToPrint << "X";
            }
            else
            {
                rowToPrint << ".";
            }
        }
        std::cout << rowToPrint.str() << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000/ConsoleGui::fps));
}
