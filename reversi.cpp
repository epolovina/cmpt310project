#include "reversi.hpp"
#include "mcts.hpp"
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
	Reversi::board[3][4] = "O";
    Reversi::board[3][3] = "X";
    Reversi::board[4][3] = "O";
    Reversi::board[4][4] = "X";
}

void Reversi::displayBoard()
{
	for (int i = 0; i < boardLen; i++) {
		for (int j = 0; j < boardLen; j++) {
			if (board[i][j] == "X") {
				std::cout << std::right <<std::setw(2) << " \033[92mX\033[0m" << " ";
			} else if (board[i][j] == "O") {
				std::cout << std::setw(2) << " \033[36mO\033[0m" << " ";
			} else if(validMoves(i*8+j) != -1) {
				if (i*8+j < 10) {
					std::cout << std::setw(2) << " \033[93m" << board[i][j] << "\033[0m" << " ";
				} else {
					std::cout << std::setw(2) << "\033[93m" << board[i][j] << "\033[0m" << " ";
				} 
			} else {
				std::cout << std::setw(2) << board[i][j] << " ";
			}
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

void Reversi::flipTiles(int toTile, int fromTile)
{
	// std::string oppTurn;
	int diff = toTile - fromTile;
	int curr = fromTile;
	bool valid = false;
	if (curr < 0 || curr > 63) {
		valid = false;
		return;
	}
	Reversi::checkOppTurn();
	board[getTileRow(curr)][getTileColumn(curr)] = turn;
	curr += diff;
	while (!valid) {
		if (board[getTileRow(curr)][getTileColumn(curr)] == oppTurn) {
			board[getTileRow(curr)][getTileColumn(curr)] = turn;
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
}

bool Reversi::canPlace(int toTile, int fromTile) 
{
	// std::string oppTurn;
	int diff = toTile - fromTile;
	int curr = fromTile + diff;
	bool valid = false;
	Reversi::checkOppTurn();
	// board[getTileRow(curr)][getTileColumn(curr)] = turn;
	while (!valid) {
		if (curr < 0 || curr > 63) {
			valid = false;
			break;
		}
		if (board[getTileRow(curr)][getTileColumn(curr)] == oppTurn) {
			// board[getTileRow(curr)][getTileColumn(curr)] = turn;
			curr += diff;
			continue;
		} else if (board[getTileRow(curr)][getTileColumn(curr)] == turn) {
			valid = true;
			break;
		} 
		else {
			valid = false;
			break;
		}
	}
	return valid;
}

int Reversi::validMoves(int tile)
{
	// std::string oppTurn;
	int downLeft  = tile + 7;
	int down      = tile + 8;
	int downRight = tile + 9;
	int upLeft    = tile - 9;
	int up        = tile - 8;
	int upRight   = tile - 7;
	int right     = tile + 1;
	int left      = tile - 1;
	int valid    = -1;
	Reversi::checkOppTurn();
	if (board[getTileRow(tile)][getTileColumn(tile)] == this->oppTurn) {
		return valid;
	}
	if ((upLeft > 0) && (tile % 8 != 0) && (board[getTileRow(upLeft)][getTileColumn(upLeft)] == oppTurn)) {
		if (canPlace(upLeft, tile)) {
			// flipTiles(upLeft, tile);
			valid = 0;
			return valid;
		}
	} 
	if ((upRight > 0) && ((tile+1) % 8 != 0) && (board[getTileRow(upRight)][getTileColumn(upRight)] == oppTurn)) {
		if (canPlace(upRight, tile)) {
			// flipTiles(upRight, tile);
			valid = 1;
			return valid;
		}
	} 
	if ((up > 0) && (board[getTileRow(up)][getTileColumn(up)] == oppTurn)) {
		if (canPlace(up, tile)) {
			// flipTiles(up, tile);
			valid = 2;
			return valid;
		}
	} 
	if ((downLeft < 64) && (tile % 8 != 0) && (board[getTileRow(downLeft)][getTileColumn(downLeft)] == oppTurn)) {
		if (canPlace(downLeft, tile)) {
			// flipTiles(downLeft, tile);
			valid = 3;
			return valid;
		}
	} 
	if ((downRight < 64) && ((tile+1) % 8 != 0) && (board[getTileRow(downRight)][getTileColumn(downRight)] == oppTurn)) {
		if (canPlace(downRight, tile)) {
			// flipTiles(downRight, tile);
			valid = 4;
			return valid;
		}
	} 
	if ((down < 64) && (board[getTileRow(down)][getTileColumn(down)] == oppTurn)) {
		if (canPlace(down, tile)) {
			// flipTiles(down, tile);
			valid = 5;
			return valid;
		}
	} 
	if (((tile+1) % 8 != 0) && (board[getTileRow(right)][getTileColumn(right)] == oppTurn)) {
		if (canPlace(right, tile)) {
			// flipTiles(right, tile);
			valid = 6;
			return valid;
		}
	} 
	if ((tile % 8 != 0) && (board[getTileRow(left)][getTileColumn(left)] == oppTurn)) {
		if (canPlace(left, tile)) {
			// flipTiles(left, tile);
			valid = 7;
			return valid;
		}
	}
	return -1;
}

void Reversi::chooseMove()
{
	std::string sTile;
	bool valid = false;
	std::string curr;
	while (!valid) {
		std::cout << "Player " << turn << ", Choose a tile" << std::endl;
		std::cin >> sTile;
		try {
			try {
				if (std::stoi(sTile) > 63) {
					throw std::invalid_argument("Out of bounds");
				}
			} catch(const std::out_of_range&) {
				throw std::invalid_argument("Out of bounds");
			}

			curr = board[getTileRow(std::stoi(sTile))][getTileColumn(std::stoi(sTile))];
			if (curr == "X" || curr == "O") {
				std::cout << "Invalid tile, choose again" << std::endl;
			}
			int fromTile = std::stoi(sTile);

			if (placePiece(fromTile)) {
				break;
			}
		} catch(const std::invalid_argument&) {
			std::cout << "Please enter a number !!" << std::endl;
		}
	}
}

void Reversi::checkOppTurn() 
{
	if (Reversi::turn == "X") {
		Reversi::oppTurn = "O";
	} else {
		Reversi::oppTurn = "X";
	}
}

std::vector<int> Reversi::getLegalMoves()
{
    std::vector<int> validMoveVec;

    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++ ) {
            int tile = i*8+j;
            if(validMoves(tile) != -1) {
				if (board[getTileRow(tile)][getTileColumn(tile)] != "X" 
					&& board[getTileRow(tile)][getTileColumn(tile)] != "O") {
					validMoveVec.push_back(tile);
				}
            }
        }
    }
    return validMoveVec;
}

bool Reversi::placePiece(int move) 
{
    int toTile;
    bool didWeMakeMove = false;
	int valMoves = 0;
	while ( valMoves != -1) {
		valMoves = validMoves(move);

		switch (valMoves)
		{
			case 0:
				toTile = move - 9;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			case 1:
				toTile = move - 7;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			case 2:
				toTile = move - 8;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			case 3:
				toTile = move + 7;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			case 4:
				toTile = move + 9;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			case 5:
				toTile = move + 8;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			case 6:
				toTile = move + 1;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			case 7:
				toTile = move - 1;
				flipTiles(toTile, move);
				didWeMakeMove = true;
				break;
			
			default:
				break;
		}
	}
	if (this->simulation) {
		if (this->getTurn() == "X") {
			this->setTurn("O");
		} else {
			this->setTurn("X");
		}
	}
	return didWeMakeMove;
}

void Reversi::checkNumTiles()
{
	this->setNumX(0);
	this->setNumO(0);
	for(int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int tile = i*8+j;
			if (board[getTileRow(tile)][getTileColumn(tile)] == "X") {
				int numX = getNumX();
				numX++;
				setNumX(numX);
			} else if (board[getTileRow(tile)][getTileColumn(tile)] == "O") {
				int numO = getNumO();
				numO++;
				setNumO(numO);
			}
		}
	}
}

bool Reversi::getIsGameFinished() 
{
	return this->isGameFinished;
}
void Reversi::setIsGameFinished(bool gameStatus)
{
	Reversi::isGameFinished = true;
}

bool Reversi::getIsGameTied() 
{
	bool isGameTied = Reversi::isGameTied;
	return isGameTied;
}

bool Reversi::checkWin()
{
	std::vector<int> legalMoves = this->getLegalMoves();
	if (legalMoves.size() == 0) {
		if (this->getTurn() == "X") {
			this->setTurn("O");
		} else {
			this->setTurn("X");
		}
		legalMoves = this->getLegalMoves();
		if (legalMoves.size() == 0) {
			this->setIsGameFinished(true);
			this->checkNumTiles();
			return true;
		} else {
			return false;
		}
	}
	return false;
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

std::string Reversi::getTurn()
{
	return this->turn;
}
void Reversi::setTurn(std::string t)
{
	this->turn = t;
}

int Reversi::getNumX() 
{
	return Reversi::numX;
}
int Reversi::getNumO()
{
	return Reversi::numO;
}

void Reversi::setNumX(int x)
{
	this->numX = x;
}
void Reversi::setNumO(int o)
{
	this->numO = o;
}

void Reversi::setSimulation(bool sim) {
	this->simulation = sim;
}
bool Reversi::getSimulation() {
	return this->simulation;
}
