#include "hangman.h"
#include <iostream>
#include <string>


void Hangman::generateWord()
{
	std::string word{ "ordinateur" };

	for (const auto& letter : word)
	{
		m_word.push_back({ letter });
	}

	m_GuessesLeft = m_nbGuesses;
	m_lettersEntered.clear();
}

void Hangman::sayRules()
{
	std::cout << "Welcome to Hangman !\n";
	std::cout << "To win: guess the word. To lose: run out of plumes.\n\n";
}

void Hangman::displayWord()
{
	std::cout << "The word:";
	
	for (const auto& letter : m_word)
	{
		if (isLetterInArray(letter, m_lettersEntered))
		{
			std::cout << letter;
		}
		else
		{
			std::cout << '_';
		}
	}

}

void Hangman::displayGuesses()
{
	std::cout << "\tWrong guesses: ";
	
	for (int i{}; i < m_nbGuesses; i++)
	{
		for (const auto& letter : m_lettersEntered)
		{
			if (isLetterInArray(letter, m_word)) {}


		}
	}
}

void Hangman::displayTurn()
{
	displayWord();
}

bool Hangman::isLetterInArray(const char c, const std::vector<char>& arr)
{
	for (const auto& letter : arr)
	{
		if (c == letter)
		{
			return true;
		}
	}

	return false;
}

void Hangman::play()
{
	/*do
	{*/
		sayRules();
		generateWord();

		displayTurn();

	//} while (m_plumesLeft > 0);
	
}