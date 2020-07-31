#include <iostream>
#include <string> 
#include <iomanip>
#include "reversi.hpp"

Reversi::Reversi()
{
	boardLen = 8;
	int tile = 0;
	std::string sTile = " ";
	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			sTile =  std::to_string(tile);
			board[i][j] = sTile;
			tile++;
		}
	}
}

bool Reversi::validMoves()
{
	char currTurn = turn;

	return false;
}

void Reversi::displayBoard()
{
	board[3][4] = 'O';
	board[3][3] = 'X';
	board[4][3] = 'O';
	board[4][4] = 'X';

	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			std::cout << std::setw(2) << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < boardLen; i++) {
		std::cout << i <<  ": [";
		for (int j = 0; j < boardLen; j++) {
			std::cout << std::setw(2) << j << " ";
		}
		std::cout << "]" << std::endl;
	}
}

int Reversi::getTileIndex(int tile)
{

}

void Reversi::chooseMove()
{
	char input;
	bool valid = false;
	while (!valid) {
		std::cin >> input;
		if (input) {
			break;
		}
	}
}

void Reversi::play()
{
	bool result = false;
	
	while(!result) {
		if (turn == 'X') {
			chooseMove();
			turn = 'O';
		} 
		else if (turn == 'O') {
			

			turn = 'X';
		}
	}
}
