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
	ttt.setMoves("a1c1b2a3c3", "b1a2c2b3");

	while (ttt.notDone()) {
		ttt.doMove();
		cout << endl << endl;
		ttt.writeOn(cout);
	};
}
