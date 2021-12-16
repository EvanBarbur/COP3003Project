/** @file ConnectFour.cpp

 *  @brief A Connect Four game

 *

 *  A collection of functions that produce a Connect Four game that is playable against a CPU opponent.

 *

 *  @author Evan Barbur

 *  @bug No known bugs.

 */

#include "ConnectFour.h"
#include "menu.h"
#include <iostream>

Menu CFourMenu;
ConnectFour cnf;


/** @brief This function begins the Connect 4 Menu

 *

 *  This function displays the Connect Four game menu and allows the user to select
 *	one of the options.


 *  @return void

 */
void Games::startCFour() {

	
	system("CLS");
	int choice;

	// Display Menu
	cout << "Welcome to Connect Four!" << endl;
	cout << "============================\n";
	cout << "   1) Play Connect 4\n";
	cout << "   2) Rules\n";
	cout << "   3) Back\n\n";

	// User enters choice
	cin >> choice; 

	// Plays Connect 4
	if (choice == 1) {
		cnf.playCFour();
	}
	// Displays the rules of the game
	if (choice == 2)
		cnf.displayCFourRules();

	// Back to Main Menu
	if (choice == 3)
		CFourMenu.Menu::displayMenu();
}


/** @brief This function starts playing the game

 *

 *  This function starts the Connect Four game. Each turn a player chooses a column to "drop" there piece into.
	Turns are looped until a winner or draw is decided.


 *  @return void

 */
void ConnectFour::playCFour() {

	ConnectFour thisGame;

	// variables
	int choice;
	int symbol;
	int cpuOptions[7] = { 1,2,3,4,5,6,7 };

	// randomly generate turn order
	srand((unsigned int)time(NULL));
	turn = rand() % 2 + 1;

	if (turn == 1)
		cout << "You go first.\n\n";
	else
		cout << "The CPU goes first.\n\n";

	system("PAUSE");

	// Do while to initiate first turn
	do {
		// displays current board
		thisGame.displayBoard();

		// Player's turn
		if (turn == 1) {
			symbol = 'O';
			cout << "Choose a column: ";
			cin >> choice;
			turn++;			// cpu's turn next
		}
		// CPU's turn
		else {
			symbol = 'X';

			// Generates random number 1-7
			do {
				srand((unsigned int)time(NULL));
				choice = rand() % 7 + 1;

			// Checks if number is available so "Invalid Response" isn't spammed
			} while (cpuOptions[choice - 1] == 0);

			turn--;			// player's turn next
		}

		// Replaces selection with current symbol
	
		while (choice > 7 || choice < 1) {
		invalid:
			cout << "Invalid Choice. Choose a different column";
			cin >> choice;
		}

		// Find row closest to the bottom that is available
		int row = thisGame.findRow(choice);

		int column = choice - 1;

		

		// Tells CPU that column is full
		if (row == 9 || row == 0) {
			cpuOptions[column] = 0;
			if (row == 9)
				goto invalid;
		}
		// Adds symbol to slot if valid
		if (row != 9)
			thisGame.board[row][column] = symbol;
				
		
	// Turns repeat until there is a win or draw
	} while (thisGame.checkForWin() == -1);

	// display ending board
	thisGame.displayBoard();

	// Displays winning message and adds to the stats
	if (thisGame.checkForWin() == 1) {
		
		// Win on your turn
		if (turn == 2) {
			cout << "You won!\n";
		}

		// Win on CPU's turn
		if (turn == 1) {
			cout << "Sorry, you lose!\n";
		}
	}
		// If 4 in a row isn't found, the game is draw
	else 
		cout << "Draw!\n";
		
		
	// Obligatory thanks for playing message and asks if you want to play Connect 4 again
	cout << "\nThanks for playing! Would you like to play again?\n1) Yes\n2) No\n\n";

	int again;
	cin >> again;

	// Clear Screen
	system("CLS");	

	if (again == 1)
		startCFour();				// Play again
	else
		CFourMenu.Menu::displayMenu();		// Go back to Menu
}
	

/** @brief This function finds the row closest to the bottom that is available
 *

 *  Function takes user or CPU choice and uses it at column parameter.
	This column is checked starting at the bottom row to see if that row
	has an empty slot. If not, it checks the next row above.

 *

 *  @param column		User choice. Used to find empty row from 2D array thisGame.board[][]

 *  @return row			Returns this int if column selected is available
 *  @return 9			Returns this int if column selected is not avaialbe

 */
int ConnectFour::findRow(int column) {
	for (int row = 5; row >= 0; row--) {
		if (board[row][column - 1] == '*')
			return row;
	}
	return 9;
}


/** @brief Displays the rules of Connect 4 to the user


 *  @return void

 */
void ConnectFour::displayCFourRules() {
	cout << "Players take turns choosing a column to drop their piece into.\n";
	cout << "The first player to connect four pieces in a row is the winner!\n";
	cout << "The winning line can be horizontal, vertical, or diagonal.\n";
}


/** @brief Displays the current Connect 4 board

 *

 *  Displays the current game board from the 2D array thisGame.board[][]


 *  @return void

 */
void ConnectFour::displayBoard() {

	system("CLS");
	cout << "Connect Four\n" << endl;
	cout << endl;
	cout << "|  1  |  2  |  3  |  4  |  5  |  6  |  7  |" << endl;

	for (int row = 0; row < 6; row++) {
		cout << "|_____|_____|_____|_____|_____|_____|_____|" << endl;
		cout << "|     |     |     |     |     |     |     |" << endl;
		for (int column = 0; column < 7; column++) {
			cout << "|  " << board[row][column] << "  ";
		}
		cout << "|";
		cout << endl;
	}
	cout << endl;
}


/** @brief This function checks to see if any player has achieved four symbols in a row on the board

 *

 *  Multiple loops to check if there are 4 spaces in a row from the 2D array that have matching player symbols.
 *  The loops check horizontally, vertically, and bi-diagonally


 *  @return void

 */
int ConnectFour::checkForWin() {
	for (int i = 5; i >= 0; i--) {
		for (int j = 6; j >= 0; j--) {
			if (board[i][j] == board[i-1][j - 1] && board[i-1][j - 1] == board[i-2][j - 2] && board[i-2][j - 2] == board[i-3][j - 3])
				if (board[i][j] != '*')
					return 1;
		
			if (board[i][j] == board[i][j-1] && board[i][j-1] == board[i][j-2] && board[i][j-2] == board[i][j-3])
				if (board[i][j] != '*')
					return 1;
			
			if (board[i][j] == board[i - 1][j] && board[i - 1][j] == board[i - 2][j] && board[i - 2][j] == board[i - 3][j])
				if (board[i][j] != '*')
					return 1;

			if (board[i][j] == board[i-1][j + 1] && board[i-1][j + 1] == board[i-2][j + 2] && board[i-2][j + 2] == board[i-3][j + 3])
				if (board[i][j] != '*')
					return 1;
			
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3])
				if (board[i][j] != '*')
					return 1;
		}
	}
	return -1;
}


