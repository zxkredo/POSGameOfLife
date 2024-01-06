//
// Created by Tatry on 4. 1. 2024.
//

#ifndef POSGAMEOFLIFECLIENT_FORMERWORLDS_H
#define POSGAMEOFLIFECLIENT_FORMERWORLDS_H


#include <vector>

class FormerWorlds {
private:
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
public:
    class FormerWorldsIterator {
    private:
        FormerWorldsBlock* currentBlock;
    public:
        explicit FormerWorldsIterator(FormerWorldsBlock *currentBlock);

        ///return false if at the end
        bool forward();
        ///return false if at the beginning
        bool backward();

        //return data
        std::vector<std::vector<bool>>& getCurrent();
    };
private:
    FormerWorldsBlock* newest;
    FormerWorldsBlock* oldest;
    const unsigned int size;
    unsigned int blockCount;

public:
    ///Undefined behaviour for size less than 2
    explicit FormerWorlds(unsigned int size);

    virtual ~FormerWorlds();

    std::vector<std::vector<bool>>& getNewest();
    std::vector<std::vector<bool>>& getOldest();

    ///If an item is added over the limit (size), the oldest element is deleted
    ///Does not take into account situations where size of container is less than 2
    void add(const std::vector<std::vector<bool>>& data);

    [[nodiscard]] bool isEmpty() const;

    ///Throws exception if empty
    ///returns iterator with current block as newest block in FormerWorlds
    FormerWorldsIterator getIterator();
};


#endif //POSGAMEOFLIFECLIENT_FORMERWORLDS_H
