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
		std::string oppTurn;
		bool didWeWin;
		bool didWelose;
		bool isGameTied;
		bool isGameFinished;
		int numX;
		int numO;
		bool simulation;

	public: 
		Reversi();
		void displayBoard();
		void play();
		void chooseMove();
		void checkWin();
		int validMoves(int tile);
		void flipTiles(int toTile, int fromTile);
		bool canPlace(int toTile, int fromTile);
		int getTileRow(int tile);
		int getTileColumn(int tile);
		std::vector<int> getLegalMoves();
		bool placePiece(int move);
		bool getIsGameTied();
		bool getDidWeWin();
		bool getDidWeLose();
		bool getIsGameFinished();
		std::string getTurn();
		void setTurn(std::string turn);
		void changeTurn();
		void setIsGameFinished(bool gameStatus);
		int getNumX();
		int getNumO();
		void setNumX(int x);
		void setNumO(int o);
		void checkNumTiles();
		void setSimulation(bool sim);
		bool getSimulation();
}; 

#endif