This project generates random numbers and lets a user guess the correct number repeatedly, until all guesses match
Once the game runs one time, the user is asked if they would like to play again
A do-while loop interprets the user's answer and runs the game until the next win from that point forward

The program starts by introducing a function that creates a new vector called answerVector, which stores the random 4-digit
that the user is guessing. This number is also outputted in main() for the user to see

Two boolean functions hasonlydigits and isunique help determine if a user's guess meets criteria (see line 51 in main)
getValidGuess uses both of these functions for error-checking before storing the numbers into a new vector called guessVec
If the criteria is met, then the guess can be interpreted. If not, a do-while loop asks the user to try again until valid
getGuesses calls getValidGuess and both of them are used to help find the correct number of bulls and/or cows
The first game ends once the player guesses answerVector correctly
