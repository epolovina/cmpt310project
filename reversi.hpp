#ifndef _REVERSI_
#define _REVERSI_

#include <string>
#include <vector>
class Reversi 
{ 
	private:
		int boardLen;
		std::string board[8][8];
		char turn;
		bool didWeWin;
		bool didWelose;
		bool isGameTied;
		bool isGameFinished;

	public: 
		Reversi();
		void displayBoard();
		void play();
		void chooseMove();
		void checkWin();
		std::vector<int> getLegalMoves();
		void placePiece();
}; 

#endif