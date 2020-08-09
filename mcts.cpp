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
    Reversi  gameCopy   = *(Reversi*) gameCopy_p;
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
            unsigned int randIndex = rand() % legalMoves.size();
            // printf("randIndex %d\n", randIndex);
            int randomMove = legalMoves.at(randIndex);
            gameCopy.placePiece(randomMove);
            gameCopy.checkOppTurn();
            // gameCopy.displayBoard();
        }
    }
    // std::cout << "Score: \033[92mX\033[0m: " << gameCopy.getNumX() << " \033[36mO\033[0m: " <<
    // gameCopy.getNumO() << std::endl; gameCopy.displayBoard(); std::cout << std::endl;
    return this->checkOutcome(gameCopy);
}

void mcts::chooseMove()
{
    Reversi            game = *(Reversi*) this->game;
    std::map<int, int> countWinningMoves;
    std::vector<int>   legalMoves = game.getLegalMoves();
    for (auto move : legalMoves) {
        countWinningMoves.insert(std::pair<int, int>(move, 0));
    }

    for (auto move : legalMoves) {
        for (int i = 0; i < 500; i++) {  // TODO:
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
    std::cout << "Player " << this->game->getTurn() << " placing: " << chosenMove << std::endl;
    this->game->placePiece(chosenMove);
}

void mcts::heuristic()
{
    int weightMap[8][8] = { { 20, -3, 11, 8, 8, 11, -3, 20 }, { -3, -7, -4, 1, 1, -4, -7, -3 },
                            { 11, -4, 2, 2, 2, 2, -4, 11 },   { 8, 1, 2, -3, -3, 2, 1, 8 },
                            { 8, 1, 2, -3, -3, 2, 1, 8 },     { 11, -4, 2, 2, 2, 2, -4, 11 },
                            { -3, -7, -4, 1, 1, -4, -7, -3 }, { 20, -3, 11, 8, 8, 11, -3, 20 } };

    std::vector<int>   legalMoves = this->game->getLegalMoves();
    std::map<int, int> getWeights;
    for (auto move : legalMoves) {
        int row = this->game->getTileRow(move);
        int col = this->game->getTileColumn(move);
        getWeights.insert(std::pair<int, int>(move, weightMap[row][col]));
    }

    int largestWeight = -1;
    int chosenMove = -1;
    for (std::map<int, int>::iterator it = getWeights.begin(); it != getWeights.end(); it++) {
        printf("key: %d  Value: %d\n", it->first, it->second);
        if(it->second > largestWeight) {
            chosenMove = it->first;
        }
    }
    this->game->placePiece(chosenMove);
}