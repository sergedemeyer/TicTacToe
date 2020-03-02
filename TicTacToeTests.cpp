//============================================================================
// Name        : TicTacToeTests.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

#include "TicTacToe.h"

class TicTactToeTest: public ::testing::Test {
protected:
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	// Declares the variables your tests want to use.
	TicTacToe ttt_;
};

// Tests the default constructor.
TEST_F(TicTactToeTest, DefaultConstructor) {
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
	char col, row;
	for (col = 'a'; col < 'd'; col++)
		for (row = '0'; row < '3'; row++) {
			EXPECT_EQ(' ', ttt_.getMark(col, row));
		};
}

// Tests the "happy day" scenario
TEST_F(TicTactToeTest, HappyDay) {
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
	while (ttt_.notDone()) {
		ttt_.doMove();
	};
	char col, row;
	bool markIsX = false; // start with 'O'
	for (col = 'a'; col < 'd'; col++)
		for (row = '0'; row < '3'; row++) {
			if (markIsX)
				EXPECT_EQ('X', ttt_.getMark(col, row));
			else
				EXPECT_EQ('O', ttt_.getMark(col, row));
			markIsX = not markIsX;
		}EXPECT_FALSE(ttt_.notDone());
	EXPECT_EQ(9, ttt_.nrOfMoves());
}

// Tests the "happy day" scenario
TEST_F(TicTactToeTest, ManualBADHappyDayTest) {
	// You can access data in the test fixture here.
	cout << "Start of game: ttt.nrOfMoves() = " << ttt_.nrOfMoves() << endl;
	cout << "Start of game: ttt.notDone() = " << ttt_.notDone() << endl;
	while (ttt_.notDone()) {
		ttt_.doMove();
	}
	char col, row;
	bool markIsX = false; // start with 'O'
	for (col = 'a'; col < 'd'; col++)
		for (row = '0'; row < '3'; row++) {
			cout << col << " - " << row << ": " << ttt_.getMark(col, row) << " =? ";
			if (markIsX) cout << "X" << endl; else cout << "O" << endl;
			markIsX = not markIsX;
		}
	cout << "End of game: ttt.nrOfMoves() = " << ttt_.nrOfMoves() << endl;
	cout << "End of game: ttt.notDone() = " << ttt_.notDone() << endl;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
