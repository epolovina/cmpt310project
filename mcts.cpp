#include "mcts.hpp"
#include <iostream>

mcts::mcts(std::string n)
{
    name = n;
}

mcts::~mcts()
{
}

std::string mcts::getName()
{
    return mcts::name;
}

int mcts::checkOutcome()
{
    return 0;
}

int mcts::doRandomPayout()
{
    return 0;
}