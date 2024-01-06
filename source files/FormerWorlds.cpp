//
// Created by Tatry on 4. 1. 2024.
//

#include "../headers/FormerWorlds.h"

FormerWorlds::FormerWorldsIterator::FormerWorldsIterator(FormerWorlds::FormerWorldsBlock &currentBlock) : currentBlock(
        currentBlock) {}

bool FormerWorlds::FormerWorldsIterator::forward() {
    return false;
}

bool FormerWorlds::FormerWorldsIterator::backward() {
    return false;
}

std::vector<std::vector<bool>> &FormerWorlds::FormerWorldsIterator::getCurrent() {
    return <#initializer#>;
}

FormerWorlds::FormerWorldsBlock::FormerWorldsBlock(const std::vector<std::vector<bool>> &data,
                                                   FormerWorlds::FormerWorldsBlock *next,
                                                   FormerWorlds::FormerWorldsBlock *previous) : data(data), next(next),
                                                                                                previous(previous) {}

std::vector<std::vector<bool>> &FormerWorlds::FormerWorldsBlock::getData() {
    return ;
}

FormerWorlds::FormerWorldsBlock *FormerWorlds::FormerWorldsBlock::getNext() {
    return nullptr;
}

FormerWorlds::FormerWorldsBlock *FormerWorlds::FormerWorldsBlock::getPrevious() {
    return nullptr;
}

void FormerWorlds::FormerWorldsBlock::setPrevious(FormerWorlds::FormerWorldsBlock *block) {

}

void FormerWorlds::FormerWorldsBlock::setNext(FormerWorlds::FormerWorldsBlock *block) {

}

FormerWorlds::FormerWorlds(const unsigned int size) : size(size), blockCount(0) {}

FormerWorlds::~FormerWorlds() {
    //TODO delete all blocks from dynamic memory
}

std::vector<std::vector<bool>> &FormerWorlds::getNewest() {
    return this->newest->getData();
}

std::vector<std::vector<bool>> &FormerWorlds::getOldest() {
    return this->oldest->getData();
}

void FormerWorlds::add(const std::vector<std::vector<bool>> &data) {

    if (this->blockCount == 0)
    {
        this->blockCount++;
        this->newest = new FormerWorlds::FormerWorldsBlock(data, nullptr, nullptr);
        this->oldest = this->newest;
    }
    else
    {
        if (this->blockCount == this->size)
        {
            FormerWorlds::FormerWorldsBlock* secondToLastBlock = this->oldest->getNext();

            secondToLastBlock->setPrevious(nullptr);
            delete this->oldest;

            this->oldest = secondToLastBlock;
        }

        auto newBlock = new FormerWorlds::FormerWorldsBlock(data, nullptr, this->newest);
        this->newest->setNext(newBlock);

        this->newest = newBlock;
    }
}

bool FormerWorlds::isEmpty() const {
    return this->blockCount == 0;
}

FormerWorlds::FormerWorldsIterator FormerWorlds::getIterator() {
    return FormerWorlds::FormerWorldsIterator(*this->newest);
}
