/* Oscar Hoegler, MP2 Flying Pigs, October 12th 2022
 * OscarHoeglerMP2Pigs.cpp, Plays pig amongst 2 players*/

#include <cstdlib>
#include <iostream>

using namespace std;

int rollDie(void);

bool isTurnScoreLost(int die1value, int die2value);
bool isTotalScoreLost(int die1value, int die2value);
char getUserInput(void);
bool isWinningScore(int score);
bool computerChoice(int die1value, int die2value,double difficulty);
int main(void) {

	
	srand(time(0));
	int die1 = 0, die2 = 0, scorePlayer = 0, scoreComp = 0, winner=0;
	double levelComp;
	char input;
	
	cout << "Choose your computer level (0-100): "; cin >> levelComp;
	while (true)
	{
		input = getUserInput();
		int rollScore = 0;
		while (input == 'r' || input == 'R')
		{
			die1 = rollDie();
			die2 = rollDie();
			cout << "You rolled " << die1 << " and " << die2<< endl;
			if (isTotalScoreLost(die1, die2))
			{
				cout << "Ouch! Score reset " << endl;
				scorePlayer = 0;
				rollScore = 0;
				break;
			}
			if (isTurnScoreLost(die1,die2))
			{
				cout << "Rough, this turn doesn't count " << endl;
				rollScore = 0;
				break;
			}
			rollScore += die1 + die2;
			cout << "Current score: " << scorePlayer << endl;
			cout << "Current sum of rolls: " << rollScore << endl;
			cout << "Current score + sum " << scorePlayer + rollScore << endl;
			input = getUserInput();
		}
		if (input == 'p' || input == 'P')
		{
			cout << "Smart choice" << endl;
		}
		scorePlayer += rollScore;
		cout << "Your current score is: " << scorePlayer << endl;
		
		if (isWinningScore(scorePlayer))
		{
			winner++;
			break;
		}

		die1 = rollDie();
		die2 = rollDie();
		rollScore = 0;
		while (computerChoice(die1, die2, levelComp))
		{
			cout << "I rolled " << die1 << " and " << die2 << endl;
			if (isTotalScoreLost(die1, die2))
			{
				cout << "Drat...I lost all my points..." << endl;
				scoreComp = 0;
				rollScore = 0;
				break;
			}
			if (isTurnScoreLost(die1, die2))
			{
				cout << "Darn...I lose my turn..." << endl;
				rollScore = 0;
				break;
			}
			rollScore += die1 + die2;
			if (scoreComp + rollScore >= 100)
			{
				cout << "I win..." << endl;
				break;
			}
			cout << "My current score + sum " << scoreComp + rollScore << endl;
			die1 = rollDie();
			die2 = rollDie();

			if (!computerChoice(die1, die2, levelComp))
			{
				break;
			}
		}
		cout << "I finish my turn" << endl;
		scoreComp += rollScore;
		cout << "My score is: " << scoreComp<< endl;
		cout << "Your score is: " << scorePlayer << endl;
		
		if (isWinningScore(scoreComp))
		{
			break;
		}
		for (int i = 0; i < 40; i++) { cout << "*"; }
		cout << endl;
	}

	if (winner)
	{
		cout << "User wins!" << endl << "Final score player : " << scorePlayer << endl << "Final score computer:" << scoreComp;
	}
	else
	{
		cout << "Computer wins!" << endl << "Final score player : " << scorePlayer << endl << "Final score computer: " << scoreComp;
	}
	return 0;
}

int rollDie(void)
{
	return (rand() % 6 + 1);
}

bool isTurnScoreLost(int die1value, int die2value)
{
	if (die1value == 1 || die2value == 1)
		return true;
	return false;
}

bool isTotalScoreLost(int die1value, int die2value)
{
	if (die1value == die2value && die1value == 1)
		return true;
	return false;
}

char getUserInput(void)
{
	char userChoice;
	cout << "Press r to roll or p to pass: "; cin >> userChoice;
	while (!(userChoice == 'r' || userChoice == 'R' || userChoice == 'p' || userChoice == 'P'))
	{
		cout << "Press r to roll or p to pass: "; cin >> userChoice;
	}
	return userChoice;
}

bool isWinningScore(int score)
{
	if (score >= 100)
	{
		return true;
	}
	return false;
}

bool computerChoice(int die1value, int die2value, double difficulty)
{
	if (difficulty == 100)
	{
		if (die1value == 1 || die2value == 1)
		{
			return false;

		}
		return true;
	}
	else
	{
		if (time(0)%100/10.0<sqrt(difficulty))
		{
			if (die1value == 1 || die2value == 1)
			{
				return false;

			}
			return true;
		}
		else
		{
			if (die1value == 1 || die2value == 1)
			{
				return true;

			}
			return false;
		}
	}
}