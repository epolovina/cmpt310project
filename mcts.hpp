#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include <iostream>

class mcts {
  private:
    std::string name;

  public:
    mcts(std::string n);
    ~mcts();

    std::string getName();

    int checkOutcome();
    int doRandomPayout();
};

#endif