#ifndef _REVERSI_
#define _REVERSI_

#include <string>
#include <vector>
class Reversi 
{ 
	private:
		int boardLen;
		std::string board[8][8];
		std::string turn;
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
		bool validMoves(int tile);
		void flipTiles(int toTile, int fromTile);
		bool canPlace(int toTile, int fromTile);
		int getTileRow(int tile);
		int getTileColumn(int tile);
		int tileIndex[2];
		std::vector<int> getLegalMoves();
		void placePiece();
}; 

#endif