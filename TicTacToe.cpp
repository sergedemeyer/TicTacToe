//============================================================================
// Name        : TicTacToe.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "TicTacToe.h"

TicTacToe::TicTacToe() {
	int i, j;
	_nrOfMoves = 0;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) {
			_board[i][j] = ' ';
		}
}

bool TicTacToe::notDone() {
	return _nrOfMoves < 9;
}


void TicTacToe::doMove() {
	char col, row, marker;
	col = (char) (_nrOfMoves % 3) + 'a';
	row = (char) (_nrOfMoves / 3) + '0';
	if (_nrOfMoves % 2) marker = 'X'; else marker = 'O'; // when _nrOfMoves is odd assign 'X'
	this->setMark(col, row, marker);
	_nrOfMoves++;
}

int TicTacToe::nrOfMoves() {
	return _nrOfMoves;
}

void TicTacToe::setMark(char col, char row, char marker) {
	_board[(int) col - 'a'][(int) row - '0'] = marker;
}

char TicTacToe::getMark(char col, char row) {
	return _board[(int) col - 'a'][(int) row - '0'];
}
