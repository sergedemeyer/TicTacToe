//============================================================================
// Name        : TicTacToe.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================


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
REQUIRE(('a' <= col) && (col <= 'c'), "col must be between 'a' and 'c'");
REQUIRE(('1' <= row) && (row <= '3'), "row must be between '1' and '3'");
REQUIRE(('X' == marker) || ('O' == marker) || (' ' == marker), "marker must be 'X', 'O' or ' '");
ENSURE((getMark(col, row) == marker), "setMark postcondition failure");
*/
	void setMark(char col, char row, char marker);

/**
The state of the game is represented as 3x3 array of chars marked ' ', 'X', or 'O'.
We index the state using chess notation, i.e., column is 'a' through 'c' and row is '1' through '3'.
REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling getMark");
REQUIRE(('a' <= col) && (col <= 'c'), "col must be between 'a' and 'c'");
REQUIRE(('1' <= row) && (row <= '3'), "row must be between '1' and '3'");
ENSURE(('X' == result) || ('O' == result) || (' ' == result), "getMark must return 'X', 'O' or ' '");
*/
	char getMark(char col, char row);

private:
	TicTacToe * _initCheck; //use pointer to myself to verify whether I am properly initialized
	int _nrOfMoves;
	char _board [3][3];

};
