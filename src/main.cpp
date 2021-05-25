#include "Controller.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <exception>

int main() try
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	
	Controller game;
	
	while(game.startGame());

	return EXIT_SUCCESS;
}

catch (std::exception & e) {

	std::ofstream myfile("log.txt");
	myfile << "Exception: " << e.what() << "\n";
	return EXIT_FAILURE;
}

catch (...) {
	std::cerr << "Unknown exception\n";
	return EXIT_FAILURE;
}