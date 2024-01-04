//
// Created by Tatry on 4. 1. 2024.
//

#include "../headers/FormerWorlds.h"

FormerWorlds::FormerWorldsIterator::FormerWorldsIterator(FormerWorlds::FormerWorldsBlock &currentBlock) : currentBlock(
        currentBlock) {}

FormerWorlds::FormerWorldsBlock::FormerWorldsBlock(const std::vector<std::vector<bool>> &data,
                                                   FormerWorlds::FormerWorldsBlock *next,
                                                   FormerWorlds::FormerWorldsBlock *previous) : data(data), next(next),
                                                                                                previous(previous) {}

FormerWorlds::FormerWorlds(const unsigned int size) : size(size) {}

FormerWorlds::~FormerWorlds() {
    //TODO delete all blocks from dynamic memory
}
