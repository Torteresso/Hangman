#ifndef HANDMAN_H
#define HANDMAN_H

#include <vector>
#include <string_view>

class Hangman
{
private:
	const int m_nbGuesses{ 6 };

	int m_GuessesLeft{ m_nbGuesses };
	std::vector<char> m_word{};
	std::vector<char> m_lettersEntered{};
	std::vector<std::string_view> m_wordList{"le silence"};

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