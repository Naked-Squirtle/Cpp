#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

class HiddenGuess
{
	static std::string loadWord() {}
	bool guessed = false;
public:
	
	std::string getHint(std::string) {}
	std::string getWord() {return loadWord();}
	bool isGuessed() {return guessed;}
};

std::string HiddenGuess::loadWord()
{
	//where the file is
	std::string path = "Resources\\words.txt";

	//makes the input stream for the file
	std::ifstream ifs(path, std::ifstream::in);

	//vector for all the words
	std::vector<std::string> wordList;

	//gets indivudual words using getline
	std::string word;

	while (std::getline(ifs, word))
	{
		//adds word to the word list
		wordList.push_back(word);
	}
	ifs.close();

	//picks a random word
	std::srand((unsigned int)(time(NULL)));
	int randomIndex = rand() % wordList.size();
	word = wordList.at(randomIndex);
	wordList.clear();

	return word;
}

std::string HiddenGuess::getHint(std::string guess)
{
	std::string word = loadWord();
	std::string output;

	//only processes the guess if it's the same length as the word
	if (guess.length() < word.length())
		output = "Too short!";

	else if (guess.length() > word.length())
		output = "Too long!";

	//goes through the guess and sees if anything is matching
	else
	{
		for (unsigned int i = 0; i < word.length(); i++)
		{
			char guessChar = guess[i];

			//if it is in the word
			if (word.find(guessChar) != std::string::npos)
			{
				//if it is in the same spot
				if (guessChar == word[i])
					output += guessChar;
				else // not in the same spot
					output += "*";
			}
			else
				output += "_";
		}

		//check if the word is finished
		if (output == word)
			guessed = true;
	}
	return output;
}