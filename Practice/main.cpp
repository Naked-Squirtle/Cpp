#include <iostream>
#include <algorithm>
#include "hiddenguess.h"
//dictionary headers
#include <unordered_map>
#include <sstream>
using namespace std;

class Game
{
protected:
	int gameID;
	string title;
	string line = "-------------------------------------------------------------------------------------";
public:
	static int totalGames;
	Game() : title("TITLE"), gameID(++totalGames) {}
	Game(const string& t) : title(t), gameID(++totalGames) {}
	
	//methods
	void print() {cout << gameID << ". " << title << endl;}
	int getID() {return gameID;}
	virtual void play() {cout << "\nPlaying game...\n" << endl;}
};
//Initialize static member of class Game
int Game::totalGames = 0;

class GuessingGame: public Game
{
public:
	GuessingGame() : Game("Word Guesser") {}
	void play()
	{
		int total_guesses;
		int total_tries;

		//introduction for the user
		cout << line << "\nWelcome to Word Guesser!\n" << line << endl;
		cout << "\nHow to Play:\n" << "# | means that the letter is not in the word\n"
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

			//the starting time for the guess
			clock_t guessTime = clock();

			//creates a numbered list where user can input their guesses
			for (int j = 0; j < total_tries; j++)
			{
				string input;
				cout << j + 1 << ") ";
				cin >> input;
				std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) -> unsigned char {return std::tolower(c); });
				string answer = guess->getHint(input);
				cout << answer << "\n";

				if (guess->isGuessed())
				{
					guessTime = clock() - guessTime; // the time difference between when the user started and guessed the correct answer
					break;
				}
			}

			//If the user guesses correctly then they are shown the time it took them to complete it
			if (guess->isGuessed())
			{
				int min = (int)(((float)guessTime) / CLOCKS_PER_SEC) / 60;
				int sec = (int)(((float)guessTime) / CLOCKS_PER_SEC) % 60;
				cout << "You took " << min << ":"; if (sec < 10) { cout << 0; } 
				cout << sec << " to get the right answer.\n" << endl;
			}
			//If the user didn't guess the right word then they are given the correct word
			else
				cout << "The word was: " << guess->getWord() << endl << endl;
			if (i < total_guesses - 1)
				cout << "Next Guess!\n" << endl;
			delete guess;				// deletes the content that guess points to
		}
	}
};

class DictionaryGame: public Game
{
public:
	DictionaryGame() : Game("Recursive Dictionary") {}
	void play()
	{
		
	}
};

int main()
{
	//unordered_map<string, string> dictionary;
	
	//initializes games
	Game* gamePtr1 = new GuessingGame;
	Game* gamePtr2 = new Game("Just a test");
	Game* gamePtr3 = new Game("Also a test");

	//where all the games are stored
	vector<Game*> all_games;
	all_games.push_back(gamePtr1);
	all_games.push_back(gamePtr2);
	all_games.push_back(gamePtr3);
	
	//option by default is set to the last one so the user can quit;
	int option = Game::totalGames + 1;

	do
	{
		//prints games
		for (const auto& g : all_games)
			g->print();

		//prints exit prompt
		cout << Game::totalGames + 1 << ". Exit" << endl;

		//user picks game
		cout << "Select an option: ";
		while( !(cin >> option) || option <= 0 || option > Game::totalGames + 1)
		{
			cout << "\nError: Enter valid number: ";
			cin.clear();
		}
		cout << endl;
		
		//plays game
		for (const auto& g : all_games)
		{
			if (g->getID() == option)
				g->play();
		}

	} while (option < Game::totalGames + 1);

	all_games.clear();
	cout << "Thanks for Playing!" << endl;
	
}