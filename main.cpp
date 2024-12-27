#include "hangman.h"
#include <iostream>
#include <string>

int main()
{
	Hangman hangman{};

	hangman.generateWordList("liste_francais.txt");

	hangman.sayRules();

	while (true)
	{
		std::cout << "\n\nEnter a new word to guess, or type 'r' to generate a random word, or 'q' to quit : ";

		std::string input{};
		while (true)
		{
			std::cin.clear();
			std::getline(std::cin, input);
			if (!hangman.wordIsValid(input) )
			{
				std::cout << "Please try again : ";
				continue;
			}
			if (input.empty()) continue;

			break;
		}

		if (input == "q") break;
		if (input == "r")
		{
			hangman.play();
		}
		else
		{
			hangman.play(input);
		}
	}

	std::cout << "Thanks for playing ! Goodbye.\n";

	return 0;
}