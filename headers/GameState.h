//
// Created by Tatry on 1. 1. 2024.
//

#ifndef POSGAMEOFLIFECLIENT_GAMESTATE_H
#define POSGAMEOFLIFECLIENT_GAMESTATE_H


#include <vector>
#include <mutex>
#include <condition_variable>

class GameState {
private:
    //variable to be able to return from start_checking() function
    bool stopThreads;
    //whether StateCheckers are generating
    bool isGenerating;
    //how many cells have been checked so far
    unsigned long alreadyCheckedCells;

    std::vector<std::vector<bool>> world1;
    std::vector<std::vector<bool>> world2;

    std::vector<std::vector<bool>>* currentWorld;
    std::vector<std::vector<bool>>* futureWorld;

    //top left corner is x = 0 , y = 0
    unsigned int xSize;
    unsigned int ySize;
    unsigned int toBeCheckedX;
    unsigned int toBeCheckedY;

    //variables for thread synchronization, to be determined
    std::mutex mutexFutureWorld;
    std::mutex mutexLastChecked;
    std::condition_variable allChecked;
    std::condition_variable currentWorldUpdated;

public:
    //contructor
    GameState(unsigned int xSize, unsigned int ySize);

    //controls
    void start_generating();
    /// Only for one thread, because it is necessary to wait for the class to stop generating the future world
    /// and it has been swapped to current world
    /// \return current world
    std::vector<std::vector<bool>>* retrieve_updated_current_world();
    void insert_current_world(const std::vector<std::vector<bool>>& starting_world);

    //function to begin checking (usable in multiple threads)
    void start_checking();

private:
    //data processing
    /// Get coordinates on which it is necessary to check the state of a cell
    /// \param posX x position to be checked in world, top is 0
    /// \param posY y position to be checked in world, left is 0
    /// \return Whether it is necessary to terminate the thread generating values
    bool get_cell_coordinates_to_check(unsigned int& posX, unsigned int& posY);

    /// Get the state of a cell in the world
    /// \param posX x position in world, top is 0
    /// \param posY y position in world, left is 0
    /// \return The state of the cell on provided coordinates
    bool get_current_world_cell_value(unsigned int posX, unsigned int posY);

    void update_future_world_cell(unsigned int posX, unsigned int posY, bool cellState);

    void stop_simulation();
};


#endif //POSGAMEOFLIFECLIENT_GAMESTATE_H
