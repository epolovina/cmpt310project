#include "mcts.hpp"
#include <iostream>

int main()
{
    mcts a("name");
    mcts b("ery");

    std::cout << a.getName() << std::endl;
    std::cout << b.getName() << std::endl;

    return 0;
}

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
