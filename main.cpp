#include <iostream>
#include "reversi.hpp"
#include "mcts.hpp"
#include "main.hpp"


void play(Reversi* game_p, flags flagStruct)
{
	// player_s player_s;
    mcts AI = mcts(game_p);
	// Reversi game = *(Reversi*) game_p;
	bool result = false;
	std::string inputS = "";
	char input;
	bool optionChosen = true;
	AI.player_struct.heuristic = false;
	AI.player_struct.human = false;
	AI.player_struct.mcts = false;

	printf("If you did not start the game with any CLI arguments, the default mode will be Pure MCTS\n");
	printf("If you would like to change the modes:\n");
	printf("Run the program with ./main -h to use heuristic function\n");
	printf("Run the program with ./main -m to use Pure MCTS function\n");
	printf("\n");
	printf("You are \033[92mX\033[0m and the computer is \033[36mO\033[0m\n");
	printf("the \033[93mYellow tiles\033[0m are the available moves for the current player\n");
	printf("\n");
	
	std::cout << "Please select a gamemode:" << std::endl;
	std::cout << "0: Player (X) vs. MCTS (O)" << std::endl;
	std::cout << "1: Player (X) vs. Heuristic MCTS (O)" << std::endl;
	std::cout << "2: MCTS (X) vs. MCTS (O)" << std::endl;
	std::cout << "3: MCTS (X) vs. Heuristic MCTS (O)" << std::endl;
	std::cout << "4: Heuristic MCTS (X) vs. Heuristic MCTS (O)" << std::endl;
	// std::cin >> input;
	do {
		std::cin.clear();
		// input = std::cin.get();
		std::cin >> input;
		switch (input)
		{
			case '0':
				AI.player_struct.human = true;
				AI.player_struct.mcts = true;
				optionChosen = true;
				std::cout << "Chosen: Player (X) vs. MCTS (O)" << std::endl;
				break;
			
			case '1':
				AI.player_struct.human = true;
				AI.player_struct.heuristic = true;
				optionChosen = true;
				std::cout << "Chosen: Player (X) vs. Heuristic MCTS (O)" << std::endl;
				break;
			
			case '2':
				AI.player_struct.mcts = true;
				std::cout << "Chosen: MCTS (X) vs. MCTS (O)" << std::endl;
				break;

			case '3':
				AI.player_struct.mcts = true;
				AI.player_struct.heuristic = true;
				optionChosen = true;
				std::cout << "Chosen: MCTS (X) vs. Heuristic MCTS (O)" << std::endl;
				break;

			case '4':
				AI.player_struct.heuristic = true;
				optionChosen = true;
				std::cout << "Chosen: Heuristic MCTS (X) vs. Heuristic MCTS (O)" << std::endl;
				break;
			
			default:
				std::cout << "Please select a valid option" << std::endl;
				optionChosen = false;
				break;
		}
	} while (!optionChosen);
	// std::cout << "Player vs computer?" << std::endl;
	// if (input == "Y" || input == "y") {
	// 	player_s.human = true;
	// } else {
	// 	player_s.human = false;
	// 	std::cout << "Player vs computer?" << std::endl;
	// 	std::cin >> input;
	// }
	std::cout << "X goes first? Y/N" << std::endl;
	std::cin >> inputS;
	game_p->setSimulation(false);
	if (inputS == "Y" || inputS == "y") {
		game_p->setTurn("X");
	} else {
		game_p->setTurn("O");
	}
	while(!result) {
		game_p->displayBoard();
		if (game_p->getTurn() == "X") {
			if (AI.player_struct.human) {
				game_p->chooseMove();
			} else {
				AI.chooseMove();
			}
			std::cout << std::endl;
			game_p->checkNumTiles();
			std::cout << "Score: \033[92mX\033[0m: " << game_p->getNumX() << " \033[36mO\033[0m: " << game_p->getNumO() << std::endl;
			game_p->setTurn("O");
		} 
		else if (game_p->getTurn() == "O") {
			AI.chooseMove();
			// if (flagStruct.heuristic) {
			// 	// AI.heuristic();
			// 	AI.chooseMove();
			// } else if (flagStruct.pureMCTS) {
			// 	AI.chooseMove();
			// } else {
			// 	AI.chooseMove();
			// }
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