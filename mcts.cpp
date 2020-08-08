#include "mcts.hpp"
#include "reversi.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <string>
#include <vector>

mcts::mcts(Reversi* game)
{
    this->game = game;
}

mcts::~mcts()
{
}

int mcts::checkOutcome(Reversi gameCopy)
{
    if (gameCopy.getIsGameFinished() && (gameCopy.getNumX() == gameCopy.getNumO())) {
        return 0;
    } else if (gameCopy.getIsGameFinished() && (gameCopy.getNumO() > gameCopy.getNumX())) {
        return 1;
    } else if (gameCopy.getIsGameFinished() && (gameCopy.getNumO() < gameCopy.getNumX())) {
        return -1;
    }
    return -2;
}

int mcts::doRandomPayout(int move)
{
    // srand(time(0));
    Reversi* gameCopy_p = this->game;
    Reversi gameCopy = *(Reversi*) gameCopy_p;
    gameCopy.setSimulation(true);
    gameCopy.placePiece(move);
    gameCopy.checkOppTurn();
    gameCopy.setNumO(0);
    gameCopy.setNumX(0);

    while (!gameCopy.getIsGameFinished()) {
        std::vector<int> legalMoves = gameCopy.getLegalMoves();

        if (legalMoves.size() == 0) {
            if (gameCopy.getTurn() == "X") {
                gameCopy.setTurn("O");
            } else {
                gameCopy.setTurn("X");
            }

            legalMoves = gameCopy.getLegalMoves();
            if (legalMoves.size() == 0) {
                gameCopy.setIsGameFinished(true);
                gameCopy.checkNumTiles();
                
                break;
            }
        } else {
            unsigned int randIndex  = rand() % legalMoves.size();
            // printf("randIndex %d\n", randIndex);
            int          randomMove = legalMoves.at(randIndex);
            gameCopy.placePiece(randomMove);
            gameCopy.checkOppTurn();
            // gameCopy.displayBoard();
        }
        // if (this->checkOutcome(gameCopy) == -1) {
        //     return this->checkOutcome(gameCopy);
        // }
        // if (this->checkOutcome(gameCopy) == 0) {
        //     return this->checkOutcome(gameCopy);
        // }
        // if (this->checkOutcome(gameCopy) == 1) {
        //     return this->checkOutcome(gameCopy);
        // }
        // return this->checkOutcome(gameCopy);
    }
    // std::cout << "Score: \033[92mX\033[0m: " << gameCopy.getNumX() << " \033[36mO\033[0m: " << gameCopy.getNumO() << std::endl;
    // gameCopy.displayBoard();
    // std::cout << std::endl;
    return this->checkOutcome(gameCopy);
}

void mcts::chooseMove()
{
    Reversi game = *(Reversi*)this->game;
    std::map<int, int> countWinningMoves;
    std::vector<int>   legalMoves = game.getLegalMoves();
    for (auto move : legalMoves) {
        countWinningMoves.insert(std::pair<int, int>(move, 0));
    }

    for (auto move : legalMoves) {
        for (int i = 0; i < 500; i++) { // TODO:
            countWinningMoves[move] += this->doRandomPayout(move);
        }
    }

    std::map<int, int>::iterator it;

    int maxWins    = (int) -INFINITY;
    int chosenMove = -1;

    for (it = countWinningMoves.begin(); it != countWinningMoves.end(); it++) {

        printf("key: %d  Value: %d\n", it->first, it->second);

        if (it->second > maxWins) {
            chosenMove = it->first;
            maxWins    = it->second;
        }
    }
    std::cout << "Player " << this->game->getTurn() <<" placing: " << chosenMove << std::endl;
    this->game->placePiece(chosenMove);
}
