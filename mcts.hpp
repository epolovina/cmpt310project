#ifndef __MCTS_HPP__
#define __MCTS_HPP__

#include "reversi.hpp"
#include <iostream>

class mcts {
  private:
    Reversi* game;

  public:
    mcts(Reversi* game);
    ~mcts();

    std::string getName();

    int  checkOutcome(Reversi gameCopy);
    int  doRandomPayout(int move);
    void chooseMove();
    int heuristic(Reversi gameCopy);
    int checkFrontiers(int move, Reversi gameCopy);
    int playOutNTimes(int move);
    // static void *playoutHelper(void *context);
};

#endif