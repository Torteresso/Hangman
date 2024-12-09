#include "hangman.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "error.h"


void Hangman::generateWord()
{
	std::string word{ "gobelin" };

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
	std::cout << "To win: guess the word. To lose: run out of pluses.\n\n";
}

void Hangman::displayWord(bool asString=false)
{
	if (asString)
	{
		for (const auto& letter : m_word)
		{
			std::cout << letter;
		}
		return;
	}

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
	
	for (int i{}; i < m_GuessesLeft; i++)
	{
		std::cout << "+";
	}

	for (const auto& letter : m_lettersEntered)
	{
		if (isLetterInArray(letter, m_word)) continue;

		std::cout << letter;
	}

	std::cout << '\n';
}

void Hangman::displayTurn()
{
	displayWord();
	displayGuesses();
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

char Hangman::askUserLetter()
{
	std::cout << "Enter your next letter: ";

	char letter{};

	std::cin >> letter;

	return letter;
}

void Hangman::update(const char newLetter)
{
	m_lettersEntered.push_back({ newLetter });
	std::sort(m_lettersEntered.begin(), m_lettersEntered.end());

	if (isLetterInArray(newLetter, m_word)) return;

	m_GuessesLeft -= 1;
}

bool Hangman::checkNewLetter(const char newLetter)
{
	if (ErrorInput::hasUnextractedInput() || !std::cin)
	{
		ErrorInput::clearFailedExtraction();
		ErrorInput::ignoreLine();

		std::cout << "That wasn't a valid input. Try again.\n\n";
		return false;
	}

	if (!isLetterInAlphabet(newLetter))
	{
		std::cout << "That wasn't a valid input. Try again.\n\n";
		return false;
	}

	if (isLetterInArray(newLetter, m_lettersEntered))
	{
		std::cout << "You already guess that. Try again.\n\n";
		return false;
	}

	if (isLetterInArray(newLetter, m_word))
	{
		std::cout << "Yes, '" << newLetter << "' is in the word !\n\n";
		return true;
	}

	std::cout << "No, '" << newLetter << "' is not in the word !\n\n";
	return true;

}

bool Hangman::isLetterInAlphabet(const char letter)
{
	for (const auto& l : "abcdefghijklmnopqrstuvwxyz")
	{
		if (l == letter) return true;
	}
	
	return false;
}

bool Hangman::userHasWon()
{
	for (const auto& letter : m_word)
	{
		if (!isLetterInArray(letter, m_lettersEntered)) return false;
	}

	displayTurn();
	std::cout << "You won ! Congratulation ;)\n";
	return true;
}

void Hangman::userHasLost()
{
	displayTurn();
	std::cout << "Sorry you lost ;(  The correct word was : ";
	displayWord(true);
	std::cout << "\n";
}

void Hangman::play()
{
	sayRules();
	generateWord();
	
	do
	{ 
		char newLetter{};
		do
		{
			displayTurn();
			newLetter = askUserLetter();
		} while (!checkNewLetter(newLetter));

		update(newLetter);

		if (userHasWon()) return;
		
	} while (m_GuessesLeft > 0);
	
	userHasLost();
}