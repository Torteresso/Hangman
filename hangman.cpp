#include "hangman.h"
#include <fstream>
#include <iostream>
#include <string_view>
#include <algorithm>
#include "error.h"
#include "random.h"

bool Hangman::generateWordList(const char filename[])
{
	std::ifstream listWords{ filename };

	if (!listWords)
	{
		std::cout << "Impossible de charger le fichier contenant les mots a faire deviner\n";
		return false;
	}

	std::string word{};
	while (std::getline(listWords, word))
	{
		m_wordList.push_back(word);
	}

	return true;
}

void Hangman::generateWord()
{
	if (m_wordList.empty())
	{
		std::cout << "No database to generate a word from, the appropriate word was generated instead\n";
		m_word = { 'e', 'r', 'r', 'o', 'r' };
		return;
	}

	std::string_view word{m_wordList[Random::get<std::size_t>(0, m_wordList.size() - 1)]};

	if (!wordIsValid(word))
	{
		std::cout << word << " is not a valid word, please check the database," 
			<< " the appropriate word was generated instead\n";
		m_word = { 'e', 'r', 'r', 'o', 'r' };
		return;
	}

	for (const auto& letter : word)
	{
		m_word.push_back({ letter });
	}
}

void Hangman::setWord(const std::string_view word)
{
	for (const auto& letter : word)
	{
		m_word.push_back({ letter });
	}
}

void Hangman::resetData()
{
	m_GuessesLeft = m_nbGuesses;
	m_lettersEntered.clear();
	m_lettersEntered.push_back(' ');
	m_word.clear();
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
		if (isLetterInArray(letter, m_word) || letter == ' ') continue;

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

bool Hangman::wordIsValid(const std::string_view word) const
{
	for (const auto& l : word)
	{
		if (!isLetterInAlphabet(l))
		{
			std::cout << l << " is not a valid caracter.\n";
			return false;
		}
	}

	return true;
}

bool Hangman::isLetterInAlphabet(const char letter) const
{
	for (const auto& l : "abcdefghijklmnopqrstuvwxyz'-. ")
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

void Hangman::printEmptyLines() const
{
	for (int i{}; i < nbNewLines; i++)
	{
		std::cout << "\n";
	}
}

void Hangman::play(const std::string_view word)
{
	resetData();
	printEmptyLines();

	if (word == "")
	{
		generateWord();
	}
	else
	{
		setWord(word);
	}
	
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