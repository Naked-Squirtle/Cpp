#include <iostream>
#include "hiddenguess.h"
using namespace std;

class Game
{
protected:
	int gameID;
	string title;
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

			//the starting time for the guess
			clock_t guessTime = clock();

			//creates a numbered list where user can input their guesses
			for (int j = 0; j < total_tries; j++)
			{
				string input;
				cout << j + 1 << ") ";
				cin >> input;

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
				printf("It took you %.1f seconds to get the right answer.\n", ((float)guessTime) / CLOCKS_PER_SEC);
			}
			//If the user didn't guess the right word then they are given the correct word
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
	Game* gamePtr1 = new GuessingGame;
	Game* gamePtr2 = new Game("Just a test");
	Game* gamePtr3 = new Game("Also a test");

	//where all the games are stored
	vector<Game*> all_games;
	all_games.push_back(gamePtr1);
	all_games.push_back(gamePtr2);
	all_games.push_back(gamePtr3);
	
	//option by default is set to the last one so the user can quit
	int option = Game::totalGames + 1;

	do
	{
		//prints games
		for (int i = 0; i < Game::totalGames; i++)
		{
			all_games.at(i)->print();
		}

		//prints exit prompt
		cout << Game::totalGames + 1 << ". Exit" << endl;

		//user picks game
		while (!(cin >> option) && option <= Game::totalGames + 1 && option > 0)
		{
			cout << "Error Enter Number again" << endl;
			cin.clear();
		}
		
		//plays game
		for (int i = 0; i < Game::totalGames; i++)
		{
			if (all_games.at(i)->getID() == option)
			{
				all_games.at(i)->play();
			}
		}

	} while (option < Game::totalGames + 1);
	cout << "\nThanks for Playing!" << endl;
	
}