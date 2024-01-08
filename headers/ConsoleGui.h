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
    static const int fps = 2;
    FormerWorlds formerWorlds;
    GameState& gameState;
public:
    explicit ConsoleGui(GameState& gameState);
    void start();
private:
    static void printWorldToConsole(const world_t& world);

    void parseUserInput(const std::string& userInput);

    void start_command();

    void stop_command();

    void introduction();

    void forward_command();

    void save_command();

    void backward_command();

    void load_command();

    void upload_command();

    void download_command();

    void load_world_from_user();

    void generate_random_starting_world();

    static int getNonZeroPositiveIntFromUser();
};


#endif //POSGAMEOFLIFECLIENT_CONSOLEGUI_H
