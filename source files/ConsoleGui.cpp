//
// Created by Tatry on 4. 1. 2024.
//

#include <iostream>
#include <thread>
#include <sstream>
#include <windows.h>
#include <random>
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
    ConsoleGui::clearConsole(world.size() + 10);
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
    std::cout << "Zadajte, či chcete vygenerovať náhodný vzor (n), zadať ručne(z):" << std::endl;

    std::string userInput;
    std::cin >> userInput;
    while (userInput != "z" && userInput != "n")
    {
        std::cout << "Zadajte vhodny prikaz: " << std::endl;
        std::cin >> userInput;
    }

    if (userInput == "z")
    {
        this->load_world_from_user();
    }
    else
    {
        this->generate_random_starting_world();
    }
}

void ConsoleGui::start_command() {
    std::cout << "Zadajte koľko krokov sa má generovať: " << std::endl;
    int steps = getNonZeroPositiveIntFromUser();


    for (int i = 0; i < steps; ++i) {
        this->forward_command();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/ConsoleGui::fps));
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
            else
            {
                this->printWorldToConsole(history.getCurrent());
            }
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
    std::cout << "Zadajte pocet riadkov <1;50>:" << std::endl;
    int rows = getNonZeroPositiveIntFromUser();
    while(rows > 50) {
        std::cout << "Zadajte pocet riadkov <1;50>:" << std::endl;
        rows = getNonZeroPositiveIntFromUser();
    }

    std::cout << "Zadajte pocet stlpcov: <1;100>:" << std::endl;
    int columns = getNonZeroPositiveIntFromUser();
    while(columns > 100) {
        std::cout << "Zadajte pocet riadkov <1;100>:" << std::endl;
        columns = getNonZeroPositiveIntFromUser();
    }
    std::vector<std::vector<bool>> loadedWorld;
    for (int i = 0; i < rows; ++i) {
        loadedWorld.emplace_back();
        for (int j = 0; j < columns; ++j) {
            loadedWorld.back().push_back(false);
        }
    }
    this->printWorldToConsole(loadedWorld);
#define message R"(Zadajte "hotovo" alebo suradnice zivej bunky vo formate: "0 0 [m]", m je volitene a znamena mrtve.:)"

    std::cout << message << std::endl;
    std::string userInput;

    std::cin.ignore();
    getline(std::cin,userInput);

    while (userInput != "hotovo")
    {
        std::stringstream ssUserInput(userInput);
        int row = -1;
        int column = -1;
        char mode = 0;
        ssUserInput >> row;
        ssUserInput >> column;

        //fist take out empty space then the char
        ssUserInput >> mode;

        bool fail = false;
        if (row < 0 || row > rows)
        {
            std::cout << "Zla suradnica riadku!" << std::endl;
            fail = true;
        }
        if (column < 0 || column > columns)
        {
            std::cout << "Zla suradnica stlpca!" << std::endl;
            fail = true;
        }
        if (mode != 0 && mode != 'm')
        {
            std::cout << "Posledny parameter môže byť jedine m alebo nič!" << std::endl;
            fail = true;
        }
        if (!fail)
        {
            if (mode == 0)
            {
                loadedWorld.at(row).at(column) = true;
            }
            else
            {
                loadedWorld.at(row).at(column) = false;
            }
            printWorldToConsole(loadedWorld);
        }
        std::cout << message << std::endl;
        getline(std::cin,userInput);
    }
    this->gameState.insert_current_world(loadedWorld);
    this->forward_command();
#undef message
}

void ConsoleGui::generate_random_starting_world() {
    //TODO reused code from load_world_from_user, possible extraction to method
    std::cout << "Zadajte pocet riadkov <1;50>:" << std::endl;
    int rows = getNonZeroPositiveIntFromUser();
    while(rows > 50) {
        std::cout << "Zadajte pocet riadkov <1;50>:" << std::endl;
        rows = getNonZeroPositiveIntFromUser();
    }

    std::cout << "Zadajte pocet stlpcov: <1;100>:" << std::endl;
    int columns = getNonZeroPositiveIntFromUser();
    while(columns > 100) {
        std::cout << "Zadajte pocet riadkov <1;100>:" << std::endl;
        columns = getNonZeroPositiveIntFromUser();
    }

    std::cout << "Zadajte pravdepodobnost zivota bunky na suradnici v percentách <1,100>:" << std::endl;
    int livingProbability = getNonZeroPositiveIntFromUser();

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 99);

    std::vector<std::vector<bool>> loadedWorld;
    for (int i = 0; i < rows; ++i) {
        loadedWorld.emplace_back();
        for (int j = 0; j < columns; ++j) {
            loadedWorld.back().push_back(distrib(gen) < livingProbability);
        }
    }
    this->printWorldToConsole(loadedWorld);
    this->gameState.insert_current_world(loadedWorld);
    this->forward_command();
}

int ConsoleGui::getNonZeroPositiveIntFromUser() {
    std::string userInput;
    std::cin >> userInput;
    std::stringstream ssUserInput(userInput);
    int number = 0;
    ssUserInput >> number;

    while (number <= 0)
    {
        std::cout << "Zadajte číslo väčšie ako 0" << std::endl;
        std::cin >> userInput;
        ssUserInput = std::stringstream(userInput);
        ssUserInput >> number;
    }
    return number;
}

void ConsoleGui::clearConsole(unsigned long long rows)
{
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), COORD{ 0, 0 } );
    //std::cout << "\033[1G"; // Move cursor to the beginning of the line
    for (unsigned long long i = 0; i < rows; ++i) {
        std::cout << "\033[500X"; // Erase 500 characters to the right of the cursor
        std::cout << std::endl;
    }
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), COORD{ 0, 0 } );
}