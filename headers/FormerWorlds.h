//
// Created by Tatry on 4. 1. 2024.
//

#ifndef POSGAMEOFLIFECLIENT_FORMERWORLDS_H
#define POSGAMEOFLIFECLIENT_FORMERWORLDS_H


#include <vector>

class FormerWorlds {
    class FormerWorldsBlock {
    private:
        std::vector<std::vector<bool>> data;
        FormerWorldsBlock* next;
        FormerWorldsBlock* previous;
    public:
        FormerWorldsBlock(const std::vector<std::vector<bool>> &data, FormerWorldsBlock *next,
                          FormerWorldsBlock *previous);

        std::vector<std::vector<bool>>& getData();
        FormerWorldsBlock* getNext();
        FormerWorldsBlock* getPrevious();

        void setPrevious(FormerWorldsBlock* block);
        void setNext(FormerWorldsBlock* block);
    };

    class FormerWorldsIterator {
    private:
        FormerWorldsBlock& currentBlock;
    public:
        explicit FormerWorldsIterator(FormerWorldsBlock &currentBlock);

        //return false if at the end
        bool forward();
        //return false if at the beginning
        bool backward();

        //return data
        std::vector<std::vector<bool>>& getCurrent();
    };
private:
    FormerWorldsBlock* first;
    FormerWorldsBlock* last;
    const unsigned int size;

public:
    explicit FormerWorlds(unsigned int size);

    virtual ~FormerWorlds();

    std::vector<std::vector<bool>>& getFirst();
    std::vector<std::vector<bool>>& getLast();

    //if an item is added over the limit (size), the last element is deleted
    void add(const std::vector<std::vector<bool>>& data);

    bool isEmpty();

    //throws exception if empty
    //returns iterator with current block as first block in FormerWorlds
    FormerWorldsIterator getIterator();
};


#endif //POSGAMEOFLIFECLIENT_FORMERWORLDS_H
