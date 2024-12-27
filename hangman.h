#ifndef HANDMAN_H
#define HANDMAN_H

#include <vector>
#include <string_view>
#include <string>

class Hangman
{
private:
	const int m_nbGuesses{ 6 };
	constexpr static int nbNewLines{ 35 };

	int m_GuessesLeft{ m_nbGuesses };
	std::vector<char> m_word{};
	std::vector<char> m_lettersEntered{};
	std::vector<std::string> m_wordList{};

	void generateWord();
	void displayWord(bool asString);
	bool isLetterInArray(const char c, const std::vector<char>& arr);
	void displayTurn();
	void displayGuesses();
	char askUserLetter();
	void update(const char newLetter);
	bool checkNewLetter(const char newLetter);
	bool isLetterInAlphabet(const char letter) const;
	bool userHasWon();
	void userHasLost();
	void resetData();
	void setWord(const std::string_view word);
	void printEmptyLines() const;

public:
	void play(const std::string_view word="");
	bool generateWordList(const char filename[]);
	void sayRules();
	bool wordIsValid(const std::string_view word) const;
};

#endif