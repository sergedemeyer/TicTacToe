//============================================================================
// Name        : TicTacToeMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TicTacToe.h"
#include "TicTacToeExporter.h"

using namespace std;

int main(int argc, char **argv) {
	TicTacToe ttt;
	TicTacToeHTMLTablesIconExporter exporter;
	
	exporter.documentStart(cout);
	ttt.setMoves("a1c1b2a3c3", "b1a2c2b3");

	while (ttt.notDone()) {
		ttt.doMove();
		cout << endl << endl;
		exporter.exportOn(cout, ttt);
	};
	exporter.documentEnd(cout);
}
