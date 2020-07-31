#include "reversi.hpp"
#include <iomanip>
#include <iostream>
#include <string>

Reversi::Reversi()
{
    boardLen = 8;
    int tile = 0;

    std::string sTile = " ";
    for (int i = 0; i < boardLen; i++) {
        for (int j = 0; j < boardLen; j++) {
            sTile = std::to_string(tile);

            Reversi::board[i][j] = sTile;
            tile++;
        }
    }
}

void Reversi::displayBoard()
{
    Reversi::board[3][4] = 'O';
    Reversi::board[3][3] = 'X';
    Reversi::board[4][3] = 'O';
    Reversi::board[4][4] = 'X';

    for (int i = 0; i < boardLen; i++) {
        for (int j = 0; j < boardLen; j++) {
            std::cout << std::setw(2) << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Reversi::play()
{
    Reversi::isGameFinished = false;
    char input;
    while (!Reversi::isGameFinished) {
        if (turn == 'X') {
            std::cin >> input;
        } else if (turn == 'O') {
        }
    }
}
