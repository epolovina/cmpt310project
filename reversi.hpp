#ifndef _REVERSI_
#define _REVERSI_

class Reversi 
{ 
	private:
		int boardLen;
		std::string board[8][8];
		char turn;

	public: 
		Reversi();
		void displayBoard();
		void play();
		void chooseMove();
		void checkWin();
}; 

#endif