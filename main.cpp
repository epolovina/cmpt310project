#include <iostream>
#include "reversi.hpp"
#include "mcts.hpp"


void play(Reversi* game_p)
{
    mcts AI = mcts(game_p);
	// Reversi game = *(Reversi*) game_p;
	bool result = false;
	std::string firstPlayer = "";
	std::cout << "Would you like to go first? Y/N" << std::endl;
	std::cin >> firstPlayer;
	game_p->setSimulation(false);
	if (firstPlayer == "Y" || firstPlayer == "y") {
		game_p->setTurn("X");
	} else {
		game_p->setTurn("O");
	}
	while(!result) {
		game_p->displayBoard();
		if (game_p->getTurn() == "X") {
			game_p->chooseMove();
			std::cout << std::endl;
			game_p->checkNumTiles();
			std::cout << "Score: \033[92mX\033[0m: " << game_p->getNumX() << " \033[36mO\033[0m: " << game_p->getNumO() << std::endl;
			game_p->setTurn("O");
		} 
		else if (game_p->getTurn() == "O") {
			AI.chooseMove();
			game_p->setTurn("X");
			game_p->checkNumTiles();
			std::cout << std::endl;
			std::cout << "Score: \033[92mX\033[0m: " << game_p->getNumX() << " \033[36mO\033[0m: " << game_p->getNumO() << std::endl;
		}
	}
}

int main()
{
	Reversi game;
	// game.displayBoard();
	play(&game);

	return 0;
}