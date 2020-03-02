//============================================================================
// Name        : TicTacToeMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TicTacToe.h"

using namespace std;

void displayGame(TicTacToe& ttt) {
	char col, row;
	cout << "TicTacToe numberOfMoves = " << ttt.nrOfMoves() << endl;
	cout << "    a   b   c   " << endl;
	cout << "  ------------- " << endl;
	for (row = minRow; row <= maxRow; row++) {
		cout << row;
		for (col = minCol; col <= maxCol; col++) {
			cout << " | " << ttt.getMark(col, row);
		}
		cout << " |" << endl;
	};
	cout << "  ------------- " << endl;
}

int main(int argc, char **argv) {
	TicTacToe ttt;

	while (ttt.notDone()) {
		ttt.doMove();
		cout << endl << endl;
		displayGame(ttt);
	};
}
