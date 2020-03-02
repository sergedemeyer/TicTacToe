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
	for (i = 0; i < maxCol - minCol + 1; i++)
		for (j = 0; j < maxRow - minRow + 1; j++) {
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
	col = (char) (_nrOfMoves % 3) + minCol;
	row = (char) (_nrOfMoves / 3) + minRow;
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
	REQUIRE((minCol <= col) && (col <= maxCol), "col must be between 'a' and 'c'");
	REQUIRE((minRow <= row) && (row <= maxRow), "row must be between '1' and '3'");
	REQUIRE(('X' == marker) || ('O' == marker) || (' ' == marker), "marker must be 'X', 'O' or ' '");
	_board[(int) col - minCol][(int) row - minRow] = marker;
	ENSURE((getMark(col, row) == marker), "setMark postcondition failure");
}

char TicTacToe::getMark(char col, char row) {
	char result;
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling getMark");
	REQUIRE((minCol <= col) && (col <= maxCol), "col must be between 'a' and 'c'");
	REQUIRE((minRow <= row) && (row <= maxRow), "row must be between '1' and '3'");
	result = _board[(int) col - minCol][(int) row - minRow];
	ENSURE(('X' == result) || ('O' == result) || (' ' == result), "getMark must return 'X', 'O' or ' '");
	return result;
}

void TicTacToe::writeOn(std::ostream& onStream) {
	char col, row;
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling displayGame");
	onStream << "TicTacToe numberOfMoves = " << this->nrOfMoves() << std::endl;
	onStream << "    a   b   c   " << std::endl;
	onStream << "  ------------- " << std::endl;
	for (row = minRow; row <= maxRow; row++) {
		onStream << row;
		for (col = minCol; col <= maxCol; col++) {
			onStream << " | " << this->getMark(col, row);
		}
		onStream << " |" << std::endl;
	};
	onStream << "  ------------- " << std::endl;
}


void TicTacToe::displayGame() {
	char col, row;
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling displayGame");
	std::cout << "TicTacToe numberOfMoves = " << this->nrOfMoves() << std::endl;
	std::cout << "    a   b   c   " << std::endl;
	std::cout << "  ------------- " << std::endl;
	for (row = minRow; row <= maxRow; row++) {
		std::cout << row;
		for (col = minCol; col <= maxCol; col++) {
			std::cout << " | " << this->getMark(col, row);
		}
		std::cout << " |" << std::endl;
	};
	std::cout << "  ------------- " << std::endl;
}

