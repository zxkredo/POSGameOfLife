//
// Created by Tatry on 4. 1. 2024.
//

#include "../headers/FormerWorlds.h"

FormerWorlds::FormerWorldsIterator::FormerWorldsIterator(FormerWorlds::FormerWorldsBlock* currentBlock) : currentBlock(
        currentBlock) {}

bool FormerWorlds::FormerWorldsIterator::forward() {
    FormerWorlds::FormerWorldsBlock* nextBlock = this->currentBlock->getNext();
    if (nextBlock == nullptr)
    {
        return false;
    }

    this->currentBlock = nextBlock;
    return true;
}

bool FormerWorlds::FormerWorldsIterator::backward() {
    FormerWorlds::FormerWorldsBlock* previousBlock = this->currentBlock->getPrevious();
    if (previousBlock == nullptr)
    {
        return false;
    }

    this->currentBlock = previousBlock;
    return true;
}

std::vector<std::vector<bool>> &FormerWorlds::FormerWorldsIterator::getCurrent() {
    return this->currentBlock->getData();
}

FormerWorlds::FormerWorldsBlock::FormerWorldsBlock(const std::vector<std::vector<bool>> &data,
                                                   FormerWorlds::FormerWorldsBlock *next,
                                                   FormerWorlds::FormerWorldsBlock *previous) : data(data), next(next),
                                                                                                previous(previous) {}

std::vector<std::vector<bool>> &FormerWorlds::FormerWorldsBlock::getData() {
    return this->data;
}

FormerWorlds::FormerWorldsBlock *FormerWorlds::FormerWorldsBlock::getNext() {
    return this->next;
}

FormerWorlds::FormerWorldsBlock *FormerWorlds::FormerWorldsBlock::getPrevious() {
    return this->previous;
}

void FormerWorlds::FormerWorldsBlock::setPrevious(FormerWorlds::FormerWorldsBlock *block) {
    this->previous = block;
}

void FormerWorlds::FormerWorldsBlock::setNext(FormerWorlds::FormerWorldsBlock *block) {
    this->next = block;
}

FormerWorlds::FormerWorlds(const unsigned int size) : size(size), blockCount(0), newest(nullptr), oldest(nullptr) {}

FormerWorlds::~FormerWorlds() {
    FormerWorlds::FormerWorldsBlock* blockToDelete = this->newest;
    while (blockToDelete != nullptr)
    {
        this->newest = blockToDelete->getPrevious();
        delete blockToDelete;
        blockToDelete = this->newest;
    }
    this->oldest = nullptr;
    this->blockCount = 0;
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
        else
        {
            blockCount++;
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
    return FormerWorlds::FormerWorldsIterator(this->newest);
}
