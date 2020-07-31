#include <iostream>
#include <string>

using namespace std;

class Reversi 
{ 
	private:
		int boardLen;

	public: 
		Reversi(int n) {
			boardLen = n;
		}
	  
	// printname is not defined inside class definition 
	void displayBoard();
	  
}; 

void Reversi::displayBoard()
{
	int n = 10; // board size
	for (int i = 0; i < n; i++) {
		
	}
}

// Definition of printname using scope resolution operator :: 
// int main() { 
	  
// 	Reversi game; 
// 	game.displayBoard();
	
// 	return 0; 
// }