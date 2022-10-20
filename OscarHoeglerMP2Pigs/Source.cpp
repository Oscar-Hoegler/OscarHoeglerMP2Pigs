/* Oscar Hoegler, MP2 Flying Pigs, October 12th 2022
 * OscarHoeglerMP2Pigs.cpp, Plays pig amongst 1 user and a computer*/

#include <cstdlib>
#include <iostream>

using namespace std;

int rollDie(void);
/* This function does not take any parameters and returns an integer
 * this integer is between the numbers 1 and 6, the same as the numbers one can get on a die */
bool isTurnScoreLost(int die1value, int die2value);
/*This function takes two integers, and returns a boolean 
 * The integers can be of any value but it is designed to be used with 1 through 6
 * the function determines if either value is 1, which in a game of pig would result in the loss of ones turn
 * the boolean returned is false if neither is 1, and is true if either is 1*/
bool isTotalScoreLost(int die1value, int die2value);
/*This function takes two integers, and returns a boolean
 * The integers can be of any value but it is designed to be used with 1 through 6
 * the function determines if both values are 1, which in a game of pig would result in the loss of all of ones points
 * the boolean returned is false if not both 1, and is true if both are 1*/
char getUserInput(void);
/*This function does not take any parameters
 * This function returns the 4 select characters r, R, p, and P depending on the user input
 * This function ensures that the user only inputs the 4 characters above, and reprompts them iff it is not one of the above
 * This function encounters an error if the user inputs multiple characters at once, where it will carry over the input into the next prompt*/
bool isWinningScore(int score);
/* This function takes an integer
 * The function is designed to work in the set of whole numbers, however would theoretically work with negative numbers
 * The function determines if the number given is greater than 100
 * The boolean returned is true iff the given integer is >= 100, and false otherwise*/
bool computerChoice(int die1value, int die2value,double difficulty);
/* This function takes 2 integers and a double
 * The function takes two integers, which can be any integer however is designed to work with 1-6
 * The double must be greater than 0, and has an intended cap of 100, however will work in the set of all reals greater than 0
 * The function takes the next roll of the dice that is to appear and has the computer make a decision
 * The function, based off the difficulty determines if it is to make the correct or incorrect move
 * If it is to make the correct move (100% of the time at 100 difficulty), it sees the dice that it would be acting on and makes the correct move (passing if either is one)
 * If it is to make the incorrect move, it sees the dice it would be acting on and makes the incorrect move ('rolling' if either is one, and passing if neither is one) */
void stars(int starcount);
/* This funciton takes an integer
 * This integer should be >=1
 * This function makes a line of stars*/
int main(void) {
	//This seeds the game randomly at the start of each round to ensure a different game each time
	srand(time(0));
	//Various initializations
	//die1 and die2 represent the number of pips on the die
	//scorePlayer represents the current score of the player
	//scoreComp represents the current score of the computer
	//winner is checked at the end of the program to see who won
	//0 means the computer won
	//1 means the player won
	int die1 = 0, die2 = 0, scorePlayer = 0, scoreComp = 0, winner=0;
	//levelComp represents the level of the computer, this should be > 0
	double levelComp;
	//input represents the user input
	char input;
	//This prompts the user for a computer difficulty, and puts it into levelComp
	cout << "Choose your computer level (0-100): "; cin >> levelComp;
	//This is required for the code to not break
	//This checks to ensure that the data that was attempted to be but into levelComp was a real number greater than 0
	//If not this causes a recursion error, so we merely exit the code instead
	if (cin.fail() || levelComp<0)
	{
		cout << "error encountered, please restart"; return 1;
	}
	//Main body of the game
	while (true)
	{
		//This calls the getUserInput() function to store the result to input
		input = getUserInput();
		//This defines the variable rollScore to be 0 whilst initializing it to be 0
		int rollScore = 0;
		//Starts the players turn loop, which is exited if the user input is either form of r
		while (input == 'r' || input == 'R')
		{
			//Sets both dies to a value between 1 and 6
			die1 = rollDie();
			die2 = rollDie();
			//Puts out what the dice are
			cout << "You rolled " << die1 << " and " << die2<< endl;
			//if isTotalScoreLost() returns true, a snide remark is made, the players score is reset, the roll score is reset, and the players turn is forcibly ended
			//The player loses all of their points in this instance
			if (isTotalScoreLost(die1, die2))
			{
				cout << "Ouch! Score reset " << endl;
				scorePlayer = 0;
				rollScore = 0;
				break;
			}
			//if isTurnScoreLost() returns true, a snide remark is made, the roll score is reset, and the players turn is forcibly ended
			//The player gains no points in this instance
			if (isTurnScoreLost(die1,die2))
			{
				cout << "Rough, this turn doesn't count " << endl;
				rollScore = 0;
				break;
			}
			//This sums the die to the current score of the players turn
			rollScore += die1 + die2;
			//These put out various information that the player may make a decision on
			cout << "Current score: " << scorePlayer << endl;
			cout << "Current sum of rolls: " << rollScore << endl;
			cout << "Current score + sum " << scorePlayer + rollScore << endl;
			stars(20);
			//gets the user input for the next loop
			input = getUserInput();
		}
		//if the player scored any, it is put into their score here, and is output for viewing
		scorePlayer += rollScore;
		cout << "Your current score is: " << scorePlayer << endl;
		//This checks if the player is currently winning, and if so sets the flag that they are and breaks the loop
		if (isWinningScore(scorePlayer))
		{
			winner++;
			break;
		}
		stars(40);
		//sets the dice for the computers turn
		die1 = rollDie();
		die2 = rollDie();
		//resets the roll score
		rollScore = 0;
		//This loops while the computer decides that the best decision is to 'roll' the dice
		while (computerChoice(die1, die2, levelComp))
		{
			//the computer says what they rolled
			cout << "I rolled " << die1 << " and " << die2 << endl;
			//if isTotalScoreLost returns true, the computer wallows in its sorrows, its score is reset, and the roll score is reset, and its turn is ended
			if (isTotalScoreLost(die1, die2))
			{
				cout << "Drat...I lost all my points..." << endl;
				scoreComp = 0;
				rollScore = 0;
				break;
			}
			//if isTurnScoreLost returns true, the computer wallows in its sorrows, the roll score is reset, and its turn is ended
			if (isTurnScoreLost(die1, die2))
			{
				cout << "Darn...I lose my turn..." << endl;
				rollScore = 0;
				break;
			}
			//This sums the die to the current score of the computers turn
			rollScore += die1 + die2;
			//The computer is aware of the win condition, and if it meets it will end its turn
			if (isWinningScore((scoreComp+rollScore)))
			{
				cout << "I win..." << endl;
				break;
			}
			//The computer is nice to the user and tells them what its current score would be if it ended its turn
			cout << "My current score + sum " << scoreComp + rollScore << endl;
			//the die are cast
			die1 = rollDie();
			die2 = rollDie();
			//if the computer choice is false, meaning it does not want to play this turn, this reads it as true and will end its turn
			if (!computerChoice(die1, die2, levelComp))
			{
				break;
			}
			stars(20);
		}
		//Computer talks
		cout << "I finish my turn..." << endl;
		//Its score is stored
		scoreComp += rollScore;
		//Information for the user
		cout << "My score is: " << scoreComp<< endl;
		cout << "Your score is: " << scorePlayer << endl;
		//This checks if the computer is winning
		if (isWinningScore(scoreComp))
		{
			break;
		}
		stars(80);
	}
	//winner is 0, false, if the computer wins and the computer says this
	//winner is 1, true, if the user wins and the proper message is output
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
/* This function takes no input
 * This function returns an integer between 1 and 6
 * I suggest one  uses this when they need to roll a die*/
int rollDie(void)
{
	//this uses the rand function and modulus function to get a random number between 0 and 5, and then adds 1 to get 1-6
	return (rand() % 6 + 1);
}
/* This function takes 2 integers as input
 * both die1value and die2value should be integers between 1 and 6, but works with all integers
 * This function returns true if either die is 1, and false otherwise
 * This should be used for determining if either value of 2 values is 1, such as in a game of pig*/
bool isTurnScoreLost(int die1value, int die2value)
{
	//if either integer input is 1, this returns true
	if (die1value == 1 || die2value == 1)
		return true;
	//in all other cases this returns false
	return false;
}
/* This function takes 2 integers as input
 * both die1value and die2value should be integers between 1 and 6, but works with all integers
 * this funciton returns true if both die are 1, and false otherwise
 * This should be used for determining if both values input are 1, such as in a game of pig*/
bool isTotalScoreLost(int die1value, int die2value)
{
	//if the dice are equal to each other, and one of them is equal to 1, then it return true
	if (die1value == die2value && die1value == 1)
		return true;
	//in all other cases it returns false
	return false;
}
/* This function takes no input 
 * This function returns the characters r,R,p or P
 * This function should be used to verify the inputs of the user, to ensure that they are r,R,p, or P*/
char getUserInput(void)
{
	//initializes the userChoice variable
	char userChoice;
	//prompts the user for input of r or p, but the secret is that R and P work aswell
	cout << "Press r to roll or p to pass: "; cin >> userChoice;
	//While the user puts in incorrect letters, the code repreats the prompt to put in good input
	while (!(userChoice == 'r' || userChoice == 'R' || userChoice == 'p' || userChoice == 'P'))
	{
		cout << "Press r to roll or p to pass: "; cin >> userChoice;
	}
	//When the user has cooperated, their choice is returned
	return userChoice;
}
/* This funciton takes and integer as input
 * score is any integer, but in a practical sense should be a whole number
 * This function returns true if score>= 100, and returns false otherwise
 * Use this Function when determining if a number is greater than 100, such as determining a winning score in pig*/
bool isWinningScore(int score)
{
	//returns true if score is >= 100, and false otherwise
	if (score >= 100)
	{
		return true;
	}
	return false;
}
/* This funciton takes and 2 integers and a double as input
 * both die1value and die2value can be in the set of integers, but should usually be between 1-6
 * difficulty should be a positive real number, with no effect being noticed if it is > 100
 * this function returns a boolean as the following chart dictates
 * if computer is to make the correct move if die1value or die2value are 1, return false, else return true
 * if computer is to make the incorrect move if die1value or die2value are 1, return true, else return false
 * Use this Fucntion when one wants a computer to make a decision on the potential results on two dice, such as in a game of pig, with an adjustable difficulty*/
bool computerChoice(int die1value, int die2value, double difficulty)
{
	//Makes code faster, does not bother using the expensive sqrt function if rand%100/10 would be gaurenteed to be less than it
	//returns false if either die1value or die2value is 1, and true otherwise
	if (difficulty >= 100)
	{
		if (die1value == 1 || die2value == 1)
		{
			return false;

		}
		return true;
	}
	else
	{
		//if a random number, [0,10), is less than the sqrt of the difficulty, the computer will make the correct decision and return false if either die is 1,
		//and return true if neither dice is one
		//if said random number is greater than the difficulty, the computer will make the incorrect decision and return true if either die is 1,
		//and return false if neither dice is one
		if (rand()% 100 / 10.0<sqrt(difficulty))
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
/*This function takes an integer as input
 * starcount should be an integer greater than or equal to 1, else this will just output an endl
 * this function does not return anything
 * Use this to create a horizontal bar*/
void stars(int starcount)
{
	for (int i = 0; i < starcount; i++) { cout << "*"; }
	cout << endl;
}