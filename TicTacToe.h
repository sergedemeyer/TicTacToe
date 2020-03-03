//============================================================================
// Name        : TicTacToe.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef TicTacToe_H
#define TicTacToe_H


#include <iostream>

const char minCol = 'a', maxCol = 'c', minRow = '1', maxRow = '3';
const int maxMoves = 17;

class TicTacToe; // forward declaration

class TicTacToePlayer {
public:

/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	TicTacToePlayer ();

/**
\n REQUIRE(('X' == marker) || ('O' == marker), "Constructor requires 'X' or 'O' as marker");
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	TicTacToePlayer (char marker);

	bool properlyInitialized();

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToePlayer wasn't initialized when calling getMarker");
\n ENSURE(('X' == result) || ('O' == result), "getMarker must return 'X' or 'O'");
*/
	char getMarker();

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToePlayer wasn't initialized when calling setMarker");
\n REQUIRE(('X' == marker) || ('O' == marker), "setMarker requires 'X' or 'O' as marker");
\n ENSURE(getMarker() == marker, "setMarker post condition failure");
*/
	void setMarker(char marker);

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToePlayer wasn't initialized when calling setMoves");
\n REQUIRE(TicTacToePlayer::legalMoves(stringWithMoves), "TicTacToe::setMoves requires legal stringWithMoves");
*/
	void setMoves(const std::string stringWithMoves);

/**
\n Performs a move
\n REQUIRE(this->properlyInitialized(), "TicTacToePlayer wasn't initialized when calling doMove");
\n REQUIRE(game->properlyInitialized(), "game wasn't initialized when passed to Player->doMove");
*/
	char doMove(TicTacToe& game);

/**
// Static utility predicate, answering whether a string contains a valid sequence of moves
*/
static bool legalMoves(const std::string stringWithMoves);


private:
	TicTacToePlayer * _initCheck; //!use pointer to myself to verify whether I am properly initialized
	char _marker;
	char _moves [maxMoves];
	int _movesLength;
	int _currentMove;
};


class TicTacToe {
public:
/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
*/
	TicTacToe();

	bool properlyInitialized();

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling setMoves");
\n REQUIRE(TicTacToePlayer::legalMoves(oMoves));
\n REQUIRE(TicTacToePlayer::legalMoves(xMoves));
*/
	void setMoves(const std::string oMoves, const std::string xMoves);

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling notDone");
*/
	bool notDone();

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling doMove");
*/
	void doMove();

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling nrOfMoves");
*/
	int nrOfMoves();

/**
The state of the game is represented as 3x3 array of chars marked ' ', 'X', or 'O'.
We index the state using chess notation, i.e., column is 'a' through 'c' and row is '1' through '3'.
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling setMark");
\n REQUIRE((minCol <= col) && (col <= maxCol), "col must be between minCol and 'c'");
\n REQUIRE((minRow <= row) && (row <= maxRow), "row must be between '1' and '3'");
\n REQUIRE(('X' == marker) || ('O' == marker) || (' ' == marker), "marker must be 'X', 'O' or ' '");
\n ENSURE((getMark(col, row) == marker), "setMark postcondition failure");
*/
	void setMark(char col, char row, char marker);

/**
The state of the game is represented as 3x3 array of chars marked ' ', 'X', or 'O'.
We index the state using chess notation, i.e., column is 'a' through 'c' and row is '1' through '3'.
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling getMark");
\n REQUIRE((minCol <= col) && (col <= maxCol), "col must be between minCol and 'c'");
\n REQUIRE((minRow <= row) && (row <= maxRow), "row must be between '1' and '3'");
\n ENSURE(('X' == result) || ('O' == result) || (' ' == result), "getMark must return 'X', 'O' or ' '");
*/
	char getMark(char col, char row);

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling writeOn");
*/
	void writeOn (std::ostream& onStream);

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling getWinner");
\n ENSURE(('X' == result) || ('O' == result) || (' ' == result), "getWinner must return 'X', 'O' or ' '");
*/
	char getWinner();

/**
\n REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling reset");
\n ENSURE(properlyInitialized(), "reset must end in properlyInitialized state");
*/
	void reset();

private:
	TicTacToe * _initCheck; //!use pointer to myself to verify whether I am properly initialized
	int _nrOfMoves;
	char _board [maxCol - minCol + 1][maxRow - minRow + 1];
	TicTacToePlayer _players [2];
	char _winner;

};


// Closing of the ``header guard''.
#endif