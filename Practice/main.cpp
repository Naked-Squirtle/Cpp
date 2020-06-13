#include <iostream>
#include "randomwords.h"
using namespace std;

class Game
{
private:
	int gameID;
	string title;
public:
	static int totalGames;
	Game() : title("TITLE") { totalGames++; gameID = totalGames; }
	Game(const string& title)
	{
		this->title = title;
		totalGames++;
		gameID = totalGames;
	}
	int getID()
	{
		return gameID;
	}
	void print()
	{
		cout << gameID << ". " << title << endl;
	}
	void play()
	{
		cout << "\nPlaying game ...\n" << endl;
	}
};

//Initialize static member of class Game
int Game::totalGames = 0;

class HiddenGuess
{
	string word = RandomWords::getWord();
	bool guessed = false;
public:
	string getHint(string guess)
	{
		string output;

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
				if (word.find(guessChar) != string::npos)
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

	string getWord()
	{
		return word;
	}

	bool isGuessed()
	{
		return guessed;
	}
};

class GuessingGame: public Game
{
public:
	GuessingGame() : Game("Word Guesser") {}
	void play()
	{
		int total_guesses;
		int total_tries;

		//introduction for the user
		const string line = "-------------------------------------------------------------------------------------";
		cout << line << "\nWelcome to Word Guesser!\n" << line << endl;
		cout << "\nHow to Play:\n" << "_ | means that the letter is not in the word\n"
			<< "* | means that the letter is in the word but not in the spot\n"
			<< "a | when you see a letter then it's in the right spot\n"
			<< line << endl;

		cout << "How many guesses do you want?: ";
		while (!(cin >> total_guesses))
		{
			// Explain the error
			cout << "ERROR: Enter a valid number: ";
			// Clear the input stream
			cin.clear();
		}

		cout << "How many tries do you want for each guess?: ";
		while (!(cin >> total_tries))
		{
			// Explain the error
			cout << "ERROR: Enter a valid number: ";
			// Clear the input stream
			cin.clear();
		}
		cout << endl;

		//makes a new guess n times
		for (int i = 0; i < total_guesses; i++)
		{
			HiddenGuess* guess = new HiddenGuess();

			//the times it takes for the guess
			clock_t guessTime = clock();

			//outputs text based on input
			for (int j = 0; j < total_tries; j++)
			{
				string input;
				cout << j + 1 << ") ";
				cin >> input;

				string answer = guess->getHint(input);
				cout << answer << "\n";

				if (guess->isGuessed())
				{
					guessTime = clock() - guessTime; // the new time is the difference between the present and starting time
					break;
				}
			}

			//shows time to get correct answer
			if (guess->isGuessed())
			{
				printf("It took you %.1f seconds to get the right answer.\n", ((float)guessTime) / CLOCKS_PER_SEC);
			}
			//says what the word was
			else
				cout << "The word was: " << guess->getWord() << endl;
			if (i < total_guesses - 1)
				cout << "\nNext Guess!\n" << endl;
			delete guess;				// deletes the content that guess points to
		}
	}
};

int main()
{
	//initializes games
	GuessingGame game1;
	Game test("Just a test");


	//where all the games are stored
	vector<Game> games;
	games.push_back(game1);
	games.push_back(test);

	int option = Game::totalGames + 1;

	do
	{
		//prints games
		for (auto g : games)
		{
			g.print();
		}

		//prints exit prompt
		cout << Game::totalGames + 1 << ". Exit" << endl;

		//user picks game
		while (!(cin >> option) && option <= Game::totalGames + 1)
		{
			cout << "Error Enter Number again" << endl;
			cin.clear();
		}
		
		//plays game
		for (auto g : games)
		{
			if(g.getID() == option)
				g.play();
		}

	} while (option < Game::totalGames + 1);
	cout << "\nThanks for Playing!" << endl;
}