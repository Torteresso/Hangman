#ifndef HANDMAN_H
#define HANDMAN_H

#include <vector>

class Hangman
{
private:
	const int m_nbPlumes{ 6 };

	int m_plumesLeft{ m_nbPlumes };
	std::vector<char> m_word{};
	std::vector<char> m_lettersEntered{};

	void generateWord();
	void sayRules();
	void displayWord();
	bool letterInWord(const char c);

public:
	void play();
};

#endif