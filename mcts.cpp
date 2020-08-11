#include <iostream>
#include <algorithm>
#include <limits>
#include <map>
#include <random>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <random>
#include <iterator>
#include "mcts.hpp"
#include "reversi.hpp"
#include "main.hpp"

// https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

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
            int randomMove;
            
            if (gameCopy.getTurn() == "O") {
                if (this->player_struct.mcts) {
                    if (!this->player_struct.heuristic) {
                        randomMove = *select_randomly(legalMoves.begin(), legalMoves.end());
                    } else {
                        randomMove = heuristic(gameCopy);
                    }
                } else if (this->player_struct.heuristic) {
                    randomMove = heuristic(gameCopy);
                }
                // randomMove = heuristic(gameCopy);
            } else {
                if (this->player_struct.mcts) {
                    randomMove = *select_randomly(legalMoves.begin(), legalMoves.end());
                    // if (!player_s.heuristic) {
                    // } else {
                    //     randomMove = heuristic(gameCopy);
                    // }
                } else if (this->player_struct.heuristic) {
                    randomMove = heuristic(gameCopy);
                }
                // unsigned int randIndex = rand() % legalMoves.size();
                // randomMove = legalMoves.at(randIndex);
                // printf("randIndex %d\n", randIndex);

                // randomMove = *select_randomly(legalMoves.begin(), legalMoves.end());
            }
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
    auto start = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;

    for (auto move : legalMoves) {
        for (int i = 0; i < 200; i++) { 
            countWinningMoves[move] += this->doRandomPayout(move);

            auto end = std::chrono::system_clock::now();
            elapsed_seconds = end-start;
            if (elapsed_seconds > std::chrono::seconds(5)) {
                std::cout << "Elapsed time limit: " << elapsed_seconds.count() << "s\n";
                std::cout << "Playouts: " << i << "\n";
                break;
            }
        }
    }

    std::map<int, int>::iterator it;

    int maxWins    = (int) -INFINITY;
    int chosenMove = -1;

    for (it = countWinningMoves.begin(); it != countWinningMoves.end(); it++) {
        // printf("key: %d  Value: %d\n", it->first, it->second);

        if (it->second > maxWins) {
            chosenMove = it->first;
            maxWins    = it->second;
        }
    }
    std::cout << "Player " << this->game->getTurn() << " placing: " << chosenMove << std::endl;
    this->game->placePiece(chosenMove);
}

int mcts::heuristic(Reversi gameCopy)
{
    /**
     *
    { 20, -3, 11,  8,  8, 11, -3, 20 }
    { -3, -7, -4,  1,  1, -4, -7, -3 },
    { 11, -4,  2,  2,  2,  2, -4, 11 }
    {  8,  1,  2, -3, -3,  2,  1,  8 },
    {  8,  1,  2, -3, -3,  2,  1,  8 }
    { 11, -4,  2,  2,  2,  2, -4, 11 },
    { -3, -7, -4,  1,  1, -4, -7, -3 }
    { 20, -3, 11,  8,  8, 11, -3, 20 }
     *
    */
    //     std::string (*grid)[8];
    //     grid = (std::string(*)[8]) this->game->getBoard();

    int weightMap[8][8] = { { 20, -3, 11, 8, 8, 11, -3, 20 }, { -3, -7, -4, 1, 1, -4, -7, -3 },
                            { 11, -4, 2, 2, 2, 2, -4, 11 },   { 8, 1, 2, -3, -3, 2, 1, 8 },
                            { 8, 1, 2, -3, -3, 2, 1, 8 },     { 11, -4, 2, 2, 2, 2, -4, 11 },
                            { -3, -7, -4, 1, 1, -4, -7, -3 }, { 20, -3, 11, 8, 8, 11, -3, 20 } };

    std::vector<int> legalMoves = gameCopy.getLegalMoves();
    // std::map<int, int> getWeights;
    std::map<int, std::vector<int>> getFrontiers;
    for (auto move : legalMoves) {
        int row = gameCopy.getTileRow(move);
        int col = gameCopy.getTileColumn(move);
        // getWeights.insert(std::pair<int, int>(move, weightMap[row][col]));
        std::vector<int> frontierWeightPair;
        frontierWeightPair.push_back(checkFrontiers(move, gameCopy));
        frontierWeightPair.push_back(weightMap[row][col]);
        getFrontiers.insert(std::pair<int, std::vector<int>>(move, frontierWeightPair));
    }

    int largestWeight    = (int) -INFINITY;
    int smallestFrontier = (int) INFINITY;
    int chosenMove       = -1;
    // using std::map<int, int>
    for (std::map<int, std::vector<int>>::iterator it = getFrontiers.begin();
         it != getFrontiers.end();
         it++) {
        // printf("key: %d  Value: %d\n", it->first, it->second);
        if (it->second.at(0) < smallestFrontier) {
            chosenMove       = it->first;
            smallestFrontier = it->second.at(0);
        } else if (it->second.at(0) == smallestFrontier) {
            if (it->second.at(1) > largestWeight) {
                chosenMove    = it->first;
                largestWeight = it->second.at(1);
            }
        }
    }

    // std::cout << "Player " << gameCopy.getTurn() << " placing: " << chosenMove << std::endl;
    // this->game->placePiece(chosenMove);
    return chosenMove;
}

int mcts::checkFrontiers(int move, Reversi gameCopy)
{
    int downLeft  = move + 7;
    int down      = move + 8;
    int downRight = move + 9;
    int upLeft    = move - 9;
    int up        = move - 8;
    int upRight   = move - 7;
    int right     = move + 1;
    int left      = move - 1;

    int frontierCounter = 0;
    if ((move % 8) != 0) {  // if not left edge move
        if (downLeft < 56) {
            if (gameCopy.getBoardAt(downLeft) != "X" && gameCopy.getBoardAt(downLeft) != "O") {
                frontierCounter++;
            }
        }
        if (gameCopy.getBoardAt(left) != "X" && gameCopy.getBoardAt(left) != "O") {
            frontierCounter++;
        }
        if (upLeft > 0) {
            if (gameCopy.getBoardAt(upLeft) != "X" && gameCopy.getBoardAt(upLeft) != "O") {
                frontierCounter++;
            }
        }
    }
    if ((move + 1 % 8) != 0) {  // if not right edge
        if (downRight < 63) {
            if (gameCopy.getBoardAt(downRight) != "X" && gameCopy.getBoardAt(downRight) != "O") {
                frontierCounter++;
            }
        }
        if (gameCopy.getBoardAt(right) != "X" && gameCopy.getBoardAt(right) != "O") {
            frontierCounter++;
        }
        if (upRight > 0) {
            if (gameCopy.getBoardAt(upRight) != "X" && gameCopy.getBoardAt(upRight) != "O") {
                frontierCounter++;
            }
        }
    }

    if (move > 7) {
        if (gameCopy.getBoardAt(up) != "X" && gameCopy.getBoardAt(up) != "O") {
            frontierCounter++;
        }
    }
    if (move < 56) {
        if (gameCopy.getBoardAt(down) != "X" && gameCopy.getBoardAt(down) != "O") {
            frontierCounter++;
        }
    }
    return frontierCounter;
}
