/** @file ConnectFour.h

 *  @brief Header file for Connect Four

 *  @author Evan Barbur

 *  @bug No known bugs.

 */

#pragma once
#include "Games.h"

class ConnectFour : public Games {

private:
	void displayBoard();
	char board[6][7] = { {'*','*','*','*','*','*','*',}, {'*','*','*','*','*','*','*',},{'*','*','*','*','*','*','*',}, {'*','*','*','*','*','*','*',}, {'*','*','*','*','*','*','*',},{'*','*','*','*','*','*','*',} };

public:
	void playCFour();
	void displayCFourRules();
	int findRow(int column);
	int checkForWin();
};

