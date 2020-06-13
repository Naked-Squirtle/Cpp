#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

class RandomWords
{
  public:
	static std::string getWord()
	{
		//where the file is
		const std::string path = "C:\\Users\\crown\\OneDrive\\Desktop\\playground\\Practice\\Debug\\words.txt";

		//makes the input stream for the file
		std::ifstream ifs(path, std::ifstream::in);

		//vector for all the words
		std::vector<std::string> wordList;

		//gets indivudual words using getline
		std::string word;

		while(std::getline(ifs, word))
		{
			//adds word to the word list
			wordList.push_back(word);
		}
		
		ifs.close();
		word.clear();

		//picks a random word
		std::srand((unsigned int)(time(NULL)));
		int randomIndex = rand() % wordList.size();
		word = wordList.at(randomIndex);

		return word;
	}
};

