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

int main(int argc, char **argv) {
	TicTacToe ttt;

	cout << "START: ttt.nrOfMoves() = " << ttt.nrOfMoves() << endl;
	while (ttt.notDone()) {
		ttt.doMove();
		cout << endl << endl << "ttt.numberOfMoves() = " << ttt.nrOfMoves()
				<< endl;
		char col, row;
		for (row = '0'; row < '3'; row++) {
			for (col = 'a'; col < 'd'; col++)
				cout << "ttt.getMark('" << col << "', '" << row << "') = '"
						<< ttt.getMark(col, row) << "'" << endl;
		}
	};
}
