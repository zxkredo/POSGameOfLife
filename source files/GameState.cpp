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

void GameState::start_generating() {

}

std::vector<std::vector<bool>> *GameState::retrieve_updated_current_world() {
    return nullptr;
}

void GameState::insert_current_world(const std::vector<std::vector<bool>> &starting_world) {

}

void GameState::start_checking() {

}

bool GameState::get_cell_coordinates_to_check(unsigned int &posX, unsigned int &posY) {
    return false;
}

bool GameState::get_current_world_cell_value(unsigned int posX, unsigned int posY) {
    return false;
}

void GameState::update_future_world_cell(unsigned int posX, unsigned int posY, bool cellState) {

}

void GameState::stop_simulation() {

}
