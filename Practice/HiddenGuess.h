#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>

class HiddenGuess
{
	const std::string loadWord();
	const std::string word = loadWord();
	bool guessed = false;
public:
	
	std::string getHint(std::string);
	std::string getWord() {return word;}
	bool isGuessed() {return guessed;}
};

const std::string HiddenGuess::loadWord()
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

	//makes the word lower case
	std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
	
	//clears the list
	wordList.clear();

	return word;
}

std::string HiddenGuess::getHint(std::string guess)
{
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
				{
					std::tolower((unsigned char)guessChar);
					output += guessChar;
				}
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
	return output + "\n";
}