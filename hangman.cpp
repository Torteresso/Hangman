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

	m_plumesLeft = m_nbPlumes;
	m_lettersEntered.clear();
}

void Hangman::sayRules()
{
	std::cout << "Welcome to Hangman !\n";
	std::cout << "To win: guess the word. To lose: run out of plumes.\n";
}

void Hangman::displayWord()
{
	std::cout << "The word:";
	m_lettersEntered.
}

void Hangman::letterInWord(const char c)
{

}

void Hangman::play()
{
	sayRules();
	generateWord();
}