#include <iostream>
#include "headers/GameState.h"

void startCalculator(GameState& gamestate)
{
    gamestate.start_checking_cells();
}
int main() {
    std::vector<std::vector<bool>> vektor = std::vector(800, std::vector(350, false));
    vektor.at(1).at(2) = true;
    vektor.at(1).at(3) = true;
    vektor.at(2).at(2) = true;
    vektor.at(2).at(3) = true;

    GameState gamestate(800,350);
    gamestate.insert_current_world(vektor);

    std::vector<std::thread*> threads;

    threads.reserve(1);
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(new std::thread(startCalculator, std::ref(gamestate)));
    }

    unsigned long long i = 0;
    while (i < 200)
    {
        vektor = gamestate.retrieve_current_world();
        gamestate.start_generating_future_world();
        i++;
        std::cout << i << std::endl;
    }

    gamestate.stop_simulation();
    for (auto & thread : threads) {
        thread->join();
        delete thread;
    }
    return 0;
}
