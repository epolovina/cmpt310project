#include <iostream>
#include "reversi.hpp"
#include "mcts.hpp"
#include "main.hpp"


void play(Reversi* game_p)
{
    mcts AI = mcts(game_p);
	bool result = false;
	std::string inputS = "";
	char input;
	bool optionChosen = true;

	AI.player_struct.heuristic = false;
	AI.player_struct.human = false;
	AI.player_struct.mcts = false;

	printf("You are \033[92mX\033[0m and the computer is \033[36mO\033[0m\n");
	printf("the \033[93mYellow tiles\033[0m are the available moves for the current player\n");
	printf("\n");
	
	std::cout << "Please select a gamemode:" << std::endl;
	std::cout << "0: Player (X) vs. MCTS (O)" << std::endl;
	std::cout << "1: Player (X) vs. Heuristic MCTS (O)" << std::endl;
	std::cout << "2: MCTS (X) vs. MCTS (O)" << std::endl;
	std::cout << "3: MCTS (X) vs. Heuristic MCTS (O)" << std::endl;
	std::cout << "4: Heuristic MCTS (X) vs. Heuristic MCTS (O)" << std::endl;

	do {
		std::cin.clear();
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
	play(&game);

	return 0;
}