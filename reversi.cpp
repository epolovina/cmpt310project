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
	Reversi::board[3][4] = "O";
    Reversi::board[3][3] = "X";
    Reversi::board[4][3] = "O";
    Reversi::board[4][4] = "X";
}

void Reversi::displayBoard()
{
	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			std::cout << std::setw(2) << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int Reversi::getTileRow(int tile)
{
	int row = tile / 8;
	return row;
}

int Reversi::getTileColumn(int tile)
{
	int row = tile / 8;
	int column = tile - (row * 8);
	return column;
}

bool Reversi::canPlace(int toTile, int fromTile) 
{
	std::string oppTurn;
	int diff = toTile - fromTile;
	int curr = fromTile + diff;
	bool valid = false;

	if (turn == "X") {
		oppTurn = "O";
	} else {
		oppTurn = "X";
	}
	// board[getTileRow(curr)][getTileColumn(curr)] = turn;
	while (!valid) {
		if (board[getTileRow(curr)][getTileColumn(curr)] == oppTurn) {
			// board[getTileRow(curr)][getTileColumn(curr)] = turn;
			curr += diff;
			continue;
		} else if (board[getTileRow(curr)][getTileColumn(curr)] == turn) {
			valid = true;
			break;
		} else {
			valid = false;
			break;
		}
	}
	return valid;
}

bool Reversi::validMoves(int tile)
{
	std::string oppTurn;
	int downLeft  = tile + 7;
	int down      = tile + 8;
	int downRight = tile + 9;
	int upLeft    = tile - 9;
	int up        = tile - 8;
	int upRight   = tile - 7;
	int right     = tile + 1;
	int left      = tile - 1;
	bool valid    = false;
	
	if (turn == "X") {
		oppTurn = "O";
	} else {
		oppTurn = "X";
	}

	if ((upLeft > 0) && (tile % 8 != 0) && (board[getTileRow(upLeft)][getTileColumn(upLeft)] == oppTurn)) {
		if (canPlace(upLeft, tile)) {
			flipTiles(upLeft, tile);
			valid = true;
		}
	} 
	if ((upRight > 0) && ((tile+1) % 8 != 0) && (board[getTileRow(upRight)][getTileColumn(upRight)] == oppTurn)) {
		if (canPlace(upRight, tile)) {
			flipTiles(upRight, tile);
			valid = true;
		}
	} 
	if ((up > 0) && (board[getTileRow(up)][getTileColumn(up)] == oppTurn)) {
		if (canPlace(up, tile)) {
			flipTiles(up, tile);
			valid = true;
		}
	} 
	if ((downLeft < 64) && (tile % 8 != 0) && (board[getTileRow(downLeft)][getTileColumn(downLeft)] == oppTurn)) {
		if (canPlace(downLeft, tile)) {
			flipTiles(downLeft, tile);
			valid = true;
		}
	} 
	if ((downRight < 64) && ((tile+1) % 8 != 0) && (board[getTileRow(downRight)][getTileColumn(downRight)] == oppTurn)) {
		if (canPlace(downRight, tile)) {
			flipTiles(downRight, tile);
			valid = true;
		}
	} 
	if ((down < 64) && (board[getTileRow(down)][getTileColumn(down)] == oppTurn)) {
		if (canPlace(down, tile)) {
			flipTiles(down, tile);
			valid = true;
		}
	} 
	if (((tile+1) % 8 != 0) && (board[getTileRow(right)][getTileColumn(right)] == oppTurn)) {
		if (canPlace(right, tile)) {
			flipTiles(right, tile);
			valid = true;
		}
	} 
	if ((tile % 8 != 0) && (board[getTileRow(left)][getTileColumn(left)] == oppTurn)) {
		if (canPlace(left, tile)) {
			flipTiles(left, tile);
			valid = true;
		}
	}
	return valid;
}

void Reversi::flipTiles(int toTile, int fromTile)
{
	std::string oppTurn;
	int diff = toTile - fromTile;
	int curr = fromTile;
	bool valid = false;

	if (turn == "X") {
		oppTurn = "O";
	} else {
		oppTurn = "X";
	}
	board[getTileRow(curr)][getTileColumn(curr)] = turn;
	curr += diff;
	while (!valid) {
		if (board[getTileRow(curr)][getTileColumn(curr)] == oppTurn) {
			board[getTileRow(curr)][getTileColumn(curr)] = turn;
			curr += diff;
			continue;
		} else if (board[getTileRow(curr)][getTileColumn(curr)] == turn) {
			valid = true;
		}
	}
}

void Reversi::chooseMove()
{
	std::string sTile;
	bool valid = false;
	std::string curr;
	while (!valid) {
		std::cout << "Player " << turn << ", Choose a tile" << std::endl;
		std::cin >> sTile;
		curr = board[getTileRow(std::stoi(sTile))][getTileColumn(std::stoi(sTile))];
		if (curr == "X" || curr == "O") {
			std::cout << "Invalid tile, choose again" << std::endl;
		}
		else if (validMoves(std::stoi(sTile))) {
			// flipTiles(tile);
			break;
		} else {
			std::cout << "Invalid tile, choose again" << std::endl;
		}
	}
}

void Reversi::play()
{
	bool result = false;
	std::string firstPlayer = "";
	std::cout << "Who goes first, Player(X) or Computer(O)?" << std::endl;
	std::cin >> firstPlayer;
	if (firstPlayer == "X" || firstPlayer == "x") {
		turn = "X";
	} else {
		turn = "O";
	}
	while(!result) {
		displayBoard();
		if (turn == "X") {
			chooseMove();
			turn = "O";
		} 
		else if (turn == "O") {
			chooseMove();
			turn = "X";
		}
	}
}
