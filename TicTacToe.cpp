//============================================================================
// Name        : TicTacToe.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "TicTacToe.h"
#include "DesignByContract.h"

TicTacToePlayer::TicTacToePlayer() {
	_initCheck = this;
	_marker = 'X';
	ENSURE(properlyInitialized(),
			"constructor must end in properlyInitialized state");
}

TicTacToePlayer::TicTacToePlayer(char marker) {
	REQUIRE(('X' == marker) || ('O' == marker), "Constructor requires 'X' or 'O' as marker");
	_initCheck = this;
	_marker = marker;
	ENSURE(properlyInitialized(),
			"constructor must end in properlyInitialized state");
}

bool TicTacToePlayer::properlyInitialized() {
	return _initCheck == this;
}

void TicTacToePlayer::setMarker(char marker) {
	REQUIRE(this->properlyInitialized(),
			"TicTacToePlayer wasn't initialized when calling setMarker");
	REQUIRE(('X' == marker) || ('O' == marker), "setMarker requires 'X' or 'O' as marker");
	_marker = marker;
	ENSURE(getMarker() == marker, "setMarker post condition failure");
}

char TicTacToePlayer::getMarker() {
	char result;
	REQUIRE(this->properlyInitialized(),
			"TicTacToePlayer wasn't initialized when calling getMarker");
	result = _marker;
	ENSURE(('X' == result) || ('O' == result),
			"getMarker must return 'X' or 'O'");
	return result;
}


void TicTacToePlayer::doMove(TicTacToe& game) {
	REQUIRE(this->properlyInitialized(),
			"TicTacToePlayer wasn't initialized when calling doMove");
	REQUIRE(game.properlyInitialized(), "game wasn't initialized when passed to Player->doMove");
	char col, row;
	col = (char) (game.nrOfMoves() % 3) + minCol;
	row = (char) (game.nrOfMoves() / 3) + minRow;
	game.setMark(col, row, _marker);
}




//
//----------------------- TicTacToe
//

TicTacToe::TicTacToe() {
	int i, j;
	_initCheck = this;
	_nrOfMoves = 0;
	for (i = 0; i < maxCol - minCol + 1; i++)
		for (j = 0; j < maxRow - minRow + 1; j++) {
			_board[i][j] = ' ';
		};
	_players[0].setMarker('O');
	_players[1].setMarker('X');
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
	_players[_nrOfMoves % 2].doMove(*this);
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
