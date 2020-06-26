#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>

//loads the word list before anything else lol
std::vector<std::string> loadWords()
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

	//sets random seed based on time: will be used to get a random word if needed
	unsigned int seed = static_cast<unsigned int>(time(NULL));
	std::srand(seed);

	return wordList;
}
std::vector<std::string> wordList = loadWords();

class HiddenGuess
{
	const std::string getRandWord();
	const std::string word = getRandWord();
	bool guessed = false;
public:
	
	std::string getHint(std::string);
	std::string getWord() {return word;}
	bool isGuessed() {return guessed;}
};

const std::string HiddenGuess::getRandWord()
{
	std::string randWord;
	//picks a random word
	int randomIndex = rand() % wordList.size();
	randWord = wordList.at(randomIndex);

	//makes the word lower case
	std::transform(randWord.begin(), randWord.end(), randWord.begin(), [](unsigned char c) -> unsigned char { return std::tolower(static_cast<unsigned char>(c)); });

	return randWord;
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
				output += "#";
		}

		//check if the word is finished
		if (output == word)
			guessed = true;
	}
	return output + "\n";
}