//============================================================================
// Name        : TicTacToe.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>

const char minCol = 'a', maxCol = 'c', minRow = '1', maxRow = '3';

class TicTacToe; // forward declaration

class TicTacToePlayer {
public:
/**
ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	TicTacToePlayer ();

/**
REQUIRE(('X' == marker) || ('O' == marker), "Constructor requires 'X' or 'O' as marker");
ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	TicTacToePlayer (char marker);

	bool properlyInitialized();

/**
REQUIRE(this->properlyInitialized(), "TicTacToePlayer wasn't initialized when calling getMarker");
ENSURE(('X' == result) || ('O' == result), "getMarker must return 'X' or 'O'");
*/
	char getMarker();

/**
REQUIRE(this->properlyInitialized(), "TicTacToePlayer wasn't initialized when calling setMarker");
REQUIRE(('X' == marker) || ('O' == marker), "setMarker requires 'X' or 'O' as marker");
ENSURE(getMarker() == marker, "setMarker post condition failure");
*/
	void setMarker(char marker);

/**
Performs a move
REQUIRE(this->properlyInitialized(), "TicTacToePlayer wasn't initialized when calling doMove");
REQUIRE(game->properlyInitialized(), "game wasn't initialized when passed to Player->doMove");
*/
	void doMove(TicTacToe& game);

private:
	TicTacToePlayer * _initCheck; //use pointer to myself to verify whether I am properly initialized
	char _marker;

};


class TicTacToe {
public:
/**
ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	TicTacToe();

	bool properlyInitialized();

/**
REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling notDone");
*/
	bool notDone();

/*
REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling doMove");
*/
	void doMove();
/**
REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling nrOfMoves");
*/
	int nrOfMoves();

/**
The state of the game is represented as 3x3 array of chars marked ' ', 'X', or 'O'.
We index the state using chess notation, i.e., column is 'a' through 'c' and row is '1' through '3'.
REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling setMark");
REQUIRE((minCol <= col) && (col <= maxCol), "col must be between minCol and 'c'");
REQUIRE((minRow <= row) && (row <= maxRow), "row must be between '1' and '3'");
REQUIRE(('X' == marker) || ('O' == marker) || (' ' == marker), "marker must be 'X', 'O' or ' '");
ENSURE((getMark(col, row) == marker), "setMark postcondition failure");
*/
	void setMark(char col, char row, char marker);

/**
The state of the game is represented as 3x3 array of chars marked ' ', 'X', or 'O'.
We index the state using chess notation, i.e., column is 'a' through 'c' and row is '1' through '3'.
REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling getMark");
REQUIRE((minCol <= col) && (col <= maxCol), "col must be between minCol and 'c'");
REQUIRE((minRow <= row) && (row <= maxRow), "row must be between '1' and '3'");
ENSURE(('X' == result) || ('O' == result) || (' ' == result), "getMark must return 'X', 'O' or ' '");
*/
	char getMark(char col, char row);


/**
REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling writeOn");
*/
	void writeOn (std::ostream& onStream);

private:
	TicTacToe * _initCheck; //use pointer to myself to verify whether I am properly initialized
	int _nrOfMoves;
	char _board [maxCol - minCol + 1][maxRow - minRow + 1];
	TicTacToePlayer _players [2];

};
