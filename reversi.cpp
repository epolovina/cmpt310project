#include "reversi.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

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
    Reversi::board[3][4] = "\033[95mO\033[0m";
    Reversi::board[3][3] = "\033[36mX\033[0m";
    Reversi::board[4][3] = "\033[95mO\033[0m";
    Reversi::board[4][4] = "\033[36mX\033[0m";

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
std::vector<int> Reversi::getLegalMoves()
{
    static const int arr[] = {16,2,77,29};
    std::vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
    return vec;
}
void Reversi::placePiece(int move) 
{
	return;
}

bool Reversi::getIsGameFinished() 
{
	bool isGameFinished = Reversi::isGameFinished;
	return isGameFinished;
}
bool Reversi::getIsGameTied() 
{
	bool isGameTied = Reversi::isGameTied;
	return isGameTied;
}
bool Reversi::getDidWeWin()
{
	bool didWeWin = Reversi::didWeWin;
	return didWeWin;
}
bool Reversi::getDidWeLose()
{
	bool didWeLose = Reversi::didWelose;
	return didWeLose;
}
