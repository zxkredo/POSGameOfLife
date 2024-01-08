#include <iostream>
#include <thread>
#include "headers/GameState.h"
#include "headers/ConsoleGui.h"

static void startCalculator(GameState& gameState)
{
    gameState.start_checking_cells();
}

int main() {
    GameState gamestate;

    std::vector<std::thread*> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(new std::thread(startCalculator, std::ref(gamestate)));
    }

    ConsoleGui gui(gamestate);
    gui.start();
    gamestate.stop_simulation();
    for (auto & thread : threads) {
        thread->join();
        delete thread;
    }
    return 0;
}
