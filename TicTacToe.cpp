//============================================================================
// Name        : TicTacToe.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "TicTacToe.h"
#include "DesignByContract.h"

TicTacToe::TicTacToe() {
	int i, j;
	_initCheck = this;
	_nrOfMoves = 0;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) {
			_board[i][j] = ' ';
		};
	ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

bool TicTacToe::properlyInitialized() {
	return _initCheck == this;
}

bool TicTacToe::notDone() {
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling notDone");
	return _nrOfMoves < 9;
}


void TicTacToe::doMove() {
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling doMove");
	char col, row, marker;
	col = (char) (_nrOfMoves % 3) + 'a';
	row = (char) (_nrOfMoves / 3) + '1';
	if (_nrOfMoves % 2) marker = 'X'; else marker = 'O'; // when _nrOfMoves is odd assign 'X'
	this->setMark(col, row, marker);
	_nrOfMoves++;
}

int TicTacToe::nrOfMoves() {
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling nrOfMoves");
	return _nrOfMoves;
}

void TicTacToe::setMark(char col, char row, char marker) {
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling setMark");
	REQUIRE(('a' <= col) && (col <= 'c'), "col must be between 'a' and 'c'");
	REQUIRE(('1' <= row) && (row <= '3'), "row must be between '1' and '3'");
	REQUIRE(('X' == marker) || ('O' == marker) || (' ' == marker), "marker must be 'X', 'O' or ' '");
	_board[(int) col - 'a'][(int) row - '1'] = marker;
	ENSURE((getMark(col, row) == marker), "setMark postcondition failure");
}

char TicTacToe::getMark(char col, char row) {
	char result;
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling getMark");
	REQUIRE(('a' <= col) && (col <= 'c'), "col must be between 'a' and 'c'");
	REQUIRE(('1' <= row) && (row <= '3'), "row must be between '1' and '3'");
	result = _board[(int) col - 'a'][(int) row - '1'];
	ENSURE(('X' == result) || ('O' == result) || (' ' == result), "getMark must return 'X', 'O' or ' '");
	return result;
}
