//
// Created by Tatry on 4. 1. 2024.
//

#include <iostream>
#include <thread>
#include <sstream>
#include <windows.h>
#include "../headers/ConsoleGui.h"
#include "../headers/ServerSaver.h"

#define EXIT_COMMAND "koniec"
#define START_COMMAND "start"
#define STOP_COMMAND "stop"
#define FORWARD_COMMAND "dopredu"
#define BACKWARD_COMMAND "dozadu"
#define SAVE_COMMAND "save"
#define LOAD_COMMAND "load"
#define UPLOAD_COMMAND "upload"
#define DOWNLOAD_COMMAND "download"

ConsoleGui::ConsoleGui(GameState& gameState) : gameState(gameState), formerWorlds(10) {}

void ConsoleGui::start() {
    this->introduction();

    std::string userInput;

    std::cout << "Zadajte prikaz: " << std::endl;
    std::cin >> userInput;
    while (userInput != EXIT_COMMAND)
    {
        this->parseUserInput(userInput);

        std::cout << "Zadajte prikaz: " << std::endl;
        std::cin >> userInput;
    }
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

void ConsoleGui::parseUserInput(const std::string& userInput) {
    if (userInput == START_COMMAND)
    {
        this->start_command();
    }
    else if (userInput == STOP_COMMAND)
    {
        this->stop_command();
    }
    else if (userInput == FORWARD_COMMAND)
    {
        this->forward_command();
    }
    else if (userInput == BACKWARD_COMMAND)
    {
        this->backward_command();
    }
    else if (userInput == SAVE_COMMAND)
    {
        this->save_command();
    }
    else if (userInput == LOAD_COMMAND)
    {
        this->load_command();
    }
    else if (userInput == UPLOAD_COMMAND)
    {
        this->upload_command();
    }
    else if (userInput == DOWNLOAD_COMMAND)
    {
        this->download_command();
    }
    else
    {
        std::cout << "Neznamy prikaz: " << userInput << std::endl;
    }
}

void ConsoleGui::introduction() {
    std::cout << "Zadajte, či chcete vygenerovať náhodný vzor (n), zadať ručne(z) alebo zo suboru(f) :" << std::endl;

    std::string userInput;
    std::cin >> userInput;
    while (userInput != "z" && userInput != "n" && userInput != "f")
    {
        std::cout << "Zadajte vhodny prikaz: " << std::endl;
        std::cin >> userInput;
    }

    if (userInput == "z")
    {
        this->load_world_from_user();
    }
    else if (userInput == "f")
    {
        this->load_command();
    }
    else
    {
        this->generate_random_starting_world();
    }
}

void ConsoleGui::start_command() {
    std::cout << "Zadajte koľko krokov sa má generovať: " << std::endl;

    std::string userInput;
    std::cin >> userInput;

    std::stringstream ssUserInput(userInput);
    int steps = 0;
    ssUserInput >> steps;

    while (steps <= 0)
    {
        std::cout << "Zadajte číslo väčšie ako 0" << std::endl;
        std::cin >> userInput;
        ssUserInput = std::stringstream(userInput);
        ssUserInput >> steps;
    }

    for (int i = 0; i < steps; ++i) {
        this->forward_command();
    }
}

void ConsoleGui::stop_command() {
    std::cout << "Nie je implementovaný" << std::endl;
}

void ConsoleGui::forward_command() {
    this->formerWorlds.add(this->gameState.retrieve_current_world());
    this->gameState.start_generating_future_world();
    this->printWorldToConsole(this->formerWorlds.getNewest());
}

void ConsoleGui::save_command() {
    std::cout << "Nie je implementovaný" << std::endl;
}

void ConsoleGui::backward_command() {
    if (this->formerWorlds.isEmpty() || &this->formerWorlds.getNewest() == &this->formerWorlds.getOldest())
    {
        std::cout << "Neexistuje história." << std::endl;
        return;
    }

    auto history = this->formerWorlds.getIterator();
    history.backward();
    this->printWorldToConsole(history.getCurrent());
    while (true)
    {
        std::cout << "Zadajte dopredu, dozadu alebo zaciatok:" << std::endl;
        std::string userInput;
        std::cin >> userInput;
        while (userInput != "dopredu" && userInput !="dozadu" && userInput !="zaciatok")
        {
            std::cin >> userInput;
        }
        if (userInput == "dopredu")
        {
            if (!history.forward())
            {
                this->forward_command();
                return;
            }
            this->printWorldToConsole(history.getCurrent());
        }
        else if(userInput == "dozadu")
        {
            if (!history.backward())
            {
                std::cout << "Ste na konci historie." << std::endl;
            }
            this->printWorldToConsole(history.getCurrent());
        }
        else
        {
            this->printWorldToConsole(this->formerWorlds.getNewest());
            return;
        }
    }
}

void ConsoleGui::load_command() {
    std::cout << "Nie je implementovaný" << std::endl;
}

void ConsoleGui::upload_command() {
    std::cout << "Zadajte názov súboru:" << std::endl;
    std::string userInput;
    std::cin >> userInput;
    try {
        ServerSaver::saveWorldToServer(this->formerWorlds.getNewest(), userInput);
    } catch(const std::exception& e)
    {
        std::cout << "Nastala chyba: " << e.what() << std::endl;
    }
}

void ConsoleGui::download_command() {
    std::cout << "Zadajte názov súboru:" << std::endl;
    std::string userInput;
    std::cin >> userInput;
    try {
        std::vector<std::vector<bool>> loadedWorld;
        if (!ServerSaver::tryGetWorldFromServer(loadedWorld, userInput))
        {
            std::cout << "Zadaný svet:" << userInput << " na serveri neexistuje!" << std::endl;
            return;
        }
        this->gameState.insert_current_world(loadedWorld);
        this->forward_command();
    } catch(const std::exception& e) {
        std::cout << "Nastala chyba: " << e.what() << std::endl;
    }
}

void ConsoleGui::load_world_from_user() {

}

void ConsoleGui::generate_random_starting_world() {

}
