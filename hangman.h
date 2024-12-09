#ifndef HANDMAN_H
#define HANDMAN_H

#include <vector>

class Hangman
{
private:
	const int m_nbGuesses{ 6 };

	int m_GuessesLeft{ m_nbGuesses };
	std::vector<char> m_word{};
	std::vector<char> m_lettersEntered{};

	void generateWord();
	void sayRules();
	void displayWord(bool asString);
	bool isLetterInArray(const char c, const std::vector<char>& arr);
	void displayTurn();
	void displayGuesses();
	char askUserLetter();
	void update(const char newLetter);
	bool checkNewLetter(const char newLetter);
	bool isLetterInAlphabet(const char letter);
	bool userHasWon();
	void userHasLost();

public:
	void play();
};

#endif