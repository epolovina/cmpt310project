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
}

void Reversi::play()
{
	bool result = false;
	char input;
	while(!result) {
		if (turn == 'X') {
			std::cin >> input;
		} 
		else if (turn == 'O') {
			
		}
	}
}
