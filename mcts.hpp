#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include "reversi.hpp"
#include <iostream>

class mcts {
  private:
    Reversi game;

  public:
    mcts(Reversi game);
    ~mcts();

    std::string getName();

    int checkOutcome(Reversi gameCopy);
    int doRandomPayout(int move);
    void chooseMove();
};

#endif