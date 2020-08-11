#include <iostream>
#include "reversi.hpp"
#include "mcts.hpp"
#include "main.hpp"


void play(Reversi* game_p, flags flagStruct)
{
    mcts AI = mcts(game_p);
	// Reversi game = *(Reversi*) game_p;
	bool result = false;
	std::string firstPlayer = "";

	printf("If you did not start the game with any CLI arguments, the default mode will be Pure MCTS\n");
	printf("If you would like to change the modes:\n");
	printf("Run the program with ./main -h to use heuristic function\n");
	printf("Run the program with ./main -m to use Pure MCTS function\n");
	printf("\n");
	printf("You are \033[92mX\033[0m and the computer is \033[36mO\033[0m\n");
	printf("the \033[93mYellow tiles\033[0m are the available moves for the current player\n");
	printf("\n");

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
			// game_p->chooseMove();
			AI.chooseMove();
			std::cout << std::endl;
			game_p->checkNumTiles();
			std::cout << "Score: \033[92mX\033[0m: " << game_p->getNumX() << " \033[36mO\033[0m: " << game_p->getNumO() << std::endl;
			game_p->setTurn("O");
		} 
		else if (game_p->getTurn() == "O") {
			// AI.chooseMove();
			if (flagStruct.heuristic) {
				// AI.heuristic();
				AI.chooseMove();
			} else if (flagStruct.pureMCTS) {
				AI.chooseMove();
			} else {
				AI.chooseMove();
			}
			game_p->setTurn("X");
			game_p->checkNumTiles();
			std::cout << std::endl;
			std::cout << "Score: \033[92mX\033[0m: " << game_p->getNumX() << " \033[36mO\033[0m: " << game_p->getNumO() << std::endl;
		}
		if (game_p->checkWin()) {
			result = game_p->getIsGameFinished();
			game_p->displayBoard();
		}
	}
	std::cout << "Game finished" << std::endl;
}

int main(int argc, char** argv)
{
	Reversi game;

	flags flagsStruct = {false, false};
	
	if (argc > 1) {
		for (int i = 0; i < argc; i++) {
			if(argv[i][0] == '-' && argv[i][1] == 'h') {
				flagsStruct.heuristic = true;
				printf("Using Heuristic to play!!\n");
				break;
			} else if (argv[i][0] == '-' && argv[i][1] == 'm') {
				flagsStruct.pureMCTS = true;
				printf("Using Pure MCTS to play!!\n");
				break;
			}
		}
	}
	play(&game, flagsStruct);

	return 0;
}