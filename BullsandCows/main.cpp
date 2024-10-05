#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

// This function will return a vector that will give us the string of numbers to be used for the guessing game
vector<int> generateAnswer(int maxDigits)
{
	// A vector of type int is built to hold the values 0-9 
	// maxDigits is declared to store the size of the vector
	vector<int> answerVec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	maxDigits = 4;

	// srand is needed to ensure we get a new number sequence each time
	srand(time(0));

	//  Random_shuffle is called and rearranges all the elements in the vector before resizing it to not lose any values
	random_shuffle(answerVec.begin(), answerVec.end());
	answerVec.resize(maxDigits);

	return answerVec;
}


// This is a range-based for loop that returns a bool
// It takes in a string called s and char c iterates through each char until a non-digit is found by using isdigit()
// If a non-digit return false, if digit return true
bool hasonlydigits(const string s)
{
	for (char c : s)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}
	return true;
}


// This function will return a bool after checking for any repeated values in our vector 
bool isunique(const vector<int>& v)
{
	// The for-loop will allow us to compare two values until we reach every value of the vector
	// Iterator i will check the value that's at a position one less than iterator i + 1,
	// Ending size() -1 makes sure that each element is checked
	for (int i = 0; i < v.size() - 1; i++)
	{
		if (v.at(i) == v.at(i + 1))
		{
			return false;
		}
	}
	return true;
}


/*
 Takes in user input (string) and eventually stores it into a vector called guessVec
 guessVec is called with pass-by-reference not value, so it's values are changed directly/ changes are seen in main too
 A do-while loop implements conditon statements that must be met before being allowed to exit the loop

 If the user's guess (userString) contains only digits and is four digits long, then retry will remain false
 The digits within the string will then get pushed as values to guessVec one at a time via for loop
 userString - '0' ensures that the characters inside the string convert from ASCII characters to integers
 (0 has ASCII value of 48, so removing 48 from every other ASCII character will give the correct number)

 isUnique is the last conditon that checks if the input is valid. If isUnique doesn't return true,
 then it'll exit the loop without errors
*/
void getValidGuess(int maxDigits, vector<int>& guessVec)
{
	// userString is initialized to null and bool retry is initialized to false
	// This ensures that the do while loop will execute as long as an error isn't thrown, 
	// which would convert retry to true and get new input
	string userString = "";
	bool retry = false;

	do
	{
		retry = false;
		cout << "  Enter guess: ";
		getline(cin, userString);

		if (!(userString.size() == maxDigits))
		{
			cout << "      Error: Guess must be 4 digits -- try again!" << endl;
			cout << endl;
			retry = true;
			continue;
		}

		if (!(hasonlydigits(userString)))
		{
			cout << "      Error: Guess can only contain digits -- try again!" << endl;
			cout << endl;
			retry = true;
			continue;
		}

		for (int i = 0; i < maxDigits; ++i)
		{
			guessVec.at(i) = userString.at(i) - '0';
		}

		if (!(isunique(guessVec)))
		{
			cout << "      Error: Digits can not be repeated -- try again!" << endl;
			cout << endl;
			retry = true;
			continue;
		}

	} while (retry);
	// while retry is true, keep looping
}


/*
 This function discovers if the number inside guess vector match the numbers in answer vector
 It also allows repeated guesses to be made
 The comparison operator is used inside a for loop to evaluate if value at index position i matches for entire vector
 If a match is found for value and index position, then bull is incremented
 If a match is found for value and not index position, then cow is incremented
*/
void getGuesses(vector<int>& answerVec, int maxDigits)
{
	int bullCount;
	int cowCount;
	int guessCount;
	char userKey = 'm';
	guessCount = 0;

	do
	{
		bullCount = 0;
		cowCount = 0;

		// Initializes a new vector called guessVec and sets size equal to maxDigits, which is set to 4 in main 
		vector<int> guessVec(maxDigits);

		// Calls getValidGuess here and not from main() so that it can use guessVec here and not call getValidGuess() twice
		getValidGuess(maxDigits, guessVec);

		for (int i = 0; i < maxDigits; ++i)
		{
			if (guessVec[i] == answerVec[i])
			{
				bullCount += 1;
			}
			// The find function checks if guessVec[i] is inside the entire answerVec and stores that into iterator
			// If iterator returns found, then it'll increment cowCount by 1
			else
			{
				auto iterator = find(answerVec.begin(), answerVec.end(), guessVec[i]);
				if (iterator != answerVec.end())
				{
					cowCount += 1;
				}
			}
		}
		guessCount++;
		cout << "      Guess #" << guessCount << ": ";
		cout << "Bulls " << bullCount << " ";
		cout << "Cows " << cowCount;
		cout << endl;
		cout << endl;
	} while (bullCount != 4);

	cout << endl;
	cout << "*** YOU WIN! ***" << endl;
}