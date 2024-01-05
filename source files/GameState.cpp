//
// Created by Tatry on 1. 1. 2024.
//

#include "../headers/GameState.h"

GameState::GameState(unsigned int xSize, unsigned int ySize) : xSize(xSize), ySize(ySize), stopThreads(false), isGenerating(
        false), alreadyCheckedCells(0), toBeCheckedX(0), toBeCheckedY(0)
        {
    this->world1, this->world2 = std::vector(this->xSize, std::vector<bool>(this->ySize, false));
    this->currentWorld = &this->world2;
    this->futureWorld = &this->world1;
}

void GameState::start_generating_future_world() {
    std::unique_lock<std::mutex> lock(this->mutexGenerating);
    while (this->isGenerating) {
        finishedGenerating.wait(lock);
    }

    this->isGenerating = true;
    this->startGenerating.notify_all();
}

std::vector<std::vector<bool>> GameState::retrieve_current_world() {
    std::unique_lock<std::mutex> lock(this->mutexGenerating);
    while (this->isGenerating) {
        finishedGenerating.wait(lock);
    }
    return *this->currentWorld;
}

void GameState::insert_current_world(const std::vector<std::vector<bool>> &starting_world) {
    std::unique_lock<std::mutex> lock(this->mutexGenerating);
    while (this->isGenerating) {
        finishedGenerating.wait(lock);
    }
    *this->currentWorld = starting_world;
}

void GameState::start_checking_cells() {

}

bool GameState::get_cell_coordinates_to_check(unsigned int &posX, unsigned int &posY) {
    return false;
}

bool GameState::get_current_world_cell_value(unsigned int posX, unsigned int posY) {
    return false;
}

void GameState::update_future_world_cell(unsigned int posX, unsigned int posY, bool cellState) {

    //TODO if all has been generated
    //this->swap_worlds();
}

void GameState::stop_simulation() {

}

void GameState::swap_worlds() {
    {
        std::unique_lock lock(this->mutexFutureWorld);
        std::swap(futureWorld, currentWorld);
    }
    {
        std::unique_lock lock(this->mutexToBeChecked);
        this->toBeCheckedX = 0;
        this->toBeCheckedY = 0;
        this->alreadyCheckedCells = 0;
    }
}
