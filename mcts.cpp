#include "mcts.hpp"
#include "reversi.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

mcts::mcts(Reversi game)
{
    this->game = game;
}

mcts::~mcts()
{
}

int mcts::checkOutcome(Reversi gameCopy)
{
    if (gameCopy.getIsGameTied()) {
        return 0;
    } else if (gameCopy.getDidWeWin()) {
        return 1;
    } else if (gameCopy.getDidWeLose()) {
        return -1;
    }
    return -2;
}

int mcts::doRandomPayout(int move)
{
    srand(time(0));
    Reversi gameCopy = this->game;
    gameCopy.placePiece(move);

    while (!gameCopy.getIsGameFinished()) {
        std::vector<int> legalMoves = gameCopy.getLegalMoves();

        unsigned int randIndex  = rand() % legalMoves.size();
        int          randomMove = legalMoves.at(randIndex);
        gameCopy.placePiece(randomMove);
        if (this->checkOutcome(gameCopy) == -1) {
            return this->checkOutcome(gameCopy);
        }
        if (this->checkOutcome(gameCopy) == 0) {
            return this->checkOutcome(gameCopy);
        }
        if (this->checkOutcome(gameCopy) == 1) {
            return this->checkOutcome(gameCopy);
        }
    }
    return this->checkOutcome(gameCopy);
}

void mcts::chooseMove()
{
    std::map<int, int> countWinningMoves;
    std::vector<int>   legalMoves = this->game.getLegalMoves();
    for (auto move : legalMoves) {
        countWinningMoves.insert(std::pair<int, int>(move, 0));
    }

    for (auto move : legalMoves) {
        for (int i = 0; i < 1000; i++) {
            countWinningMoves[i] += this->doRandomPayout(move);
        }
    }

    std::map<int, int>::iterator it;

    int maxWins    = -1;
    int chosenMove = -1;

    for (it = countWinningMoves.begin(); it != countWinningMoves.end(); it++) {
        if (it->second > maxWins) {
            chosenMove = it->first;
            maxWins    = it->second;
        }
    }
    this->game.placePiece(chosenMove);
}
