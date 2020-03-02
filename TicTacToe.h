//============================================================================
// Name        : TicTacToe.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================


class TicTacToe {
public:
	TicTacToe();
	bool notDone();
	void doMove();
	int nrOfMoves();
	/**
	The state of the game is represented as 3x3 array of chars marked ' ', 'X', or 'O'.
	We index the state using chess notation, i.e., column is 'a' through 'c' and row is '1' through '3'.*)
	*/
	void setMark(char col, char row, char marker);
	char getMark(char col, char row);

private:
	int _nrOfMoves;
	char _board [3][3];

};
