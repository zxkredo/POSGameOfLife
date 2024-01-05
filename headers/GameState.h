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

    bool stopThreads;
    //whether StateCheckers are mutexGenerating
    bool isGenerating;
    //how many cells have been checked so far
    unsigned long alreadyCheckedCells;

    //count of all cells in a world
    unsigned long cellCount;

    std::vector<std::vector<bool>> world1;
    std::vector<std::vector<bool>> world2;

    std::vector<std::vector<bool>>* currentWorld;
    std::vector<std::vector<bool>>* futureWorld;

    //top left corner is row = 0 , column = 0
    unsigned int rows;
    unsigned int columns;
    unsigned int toBeCheckedRow;
    unsigned int toBeCheckedColumn;

    //variables for thread synchronization, to be determined
    std::mutex mutexFutureWorld;
    std::mutex mutexToBeChecked;
    std::mutex mutexGenerating;

    std::condition_variable startGenerating;
    std::condition_variable finishedGenerating;

    std::condition_variable allChecked;

public:
    //contructor
    //Game world uses matrix coordinates top left is 0, 0 ; top right is 0, columns (number of columns)
    GameState(unsigned int rows, unsigned int columns);

    //controls

    /// If already generating waits until the previous request has been generated.
    /// \return The updated (most recently generated) current world
    std::vector<std::vector<bool>> retrieve_current_world();

    /// If already generating waits until the previous request has been generated.
    void insert_current_world(const std::vector<std::vector<bool>>& starting_world);

    /// Requests the checkers to start generating the future world from the current.
    /// If already generating waits until the previous request has been generated.
    void start_generating_future_world();

    /// Function for purposes of calculating living cells.
    /// Can be called from multiple thread to parallelize the calculation.
    void start_checking_cells();

    /// Peacefully let all threads leave infinite loop of calculation
    void stop_simulation();
private:
    //data processing
    /// Get coordinates on which it is necessary to check the state of a cell
    /// \param row x position to be checked in world, top is 0
    /// \param column y position to be checked in world, left is 0
    void get_cell_coordinates_to_check(unsigned int& row, unsigned int& column);

    /// Get the state of a cell in the world
    /// \param row x position in world, top is 0
    /// \param column y position in world, left is 0
    /// \return The state of the cell on provided coordinates
    bool get_current_world_cell_value(const unsigned int& row, const unsigned int& column);

    void update_future_world_cell(const unsigned int& row,const unsigned int& column, bool cellState);

    void swap_worlds();
};


#endif //POSGAMEOFLIFECLIENT_GAMESTATE_H
