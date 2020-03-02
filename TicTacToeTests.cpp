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

	// virtual void SetUp() will be called before each test is run.  You
	// should define it if you need to initialize the variables.
	// Otherwise, this can be skipped.
	virtual void SetUp() {
	}

	// virtual void TearDown() will be called after each test is run.
	// You should define it if there is cleanup work to do.  Otherwise,
	// you don't have to provide it.
	virtual void TearDown() {
	}

	// Declares the variables your tests want to use.
	TicTacToe ttt_;
};

// Tests the default constructor.
TEST_F(TicTactToeTest, DefaultConstructor) {
	EXPECT_TRUE(ttt_.properlyInitialized()); // verify post-condition
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
	char col, row;
	for (col = 'a'; col <= 'c'; col++)
		for (row = '1'; row <= '3'; row++) {
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
	for (col = 'a'; col <= 'c'; col++)
		for (row = '1'; row <= '3'; row++) {
			if (markIsX)
				EXPECT_EQ('X', ttt_.getMark(col, row));
			else
				EXPECT_EQ('O', ttt_.getMark(col, row));
			markIsX = not markIsX;
		}
	EXPECT_FALSE(ttt_.notDone());
	EXPECT_EQ(9, ttt_.nrOfMoves());
}

// Verify whether unsatisfied pre-conditions indeed trigger failures
TEST_F(TicTactToeTest, ContractViolations) {
	EXPECT_DEATH(ttt_.getMark('1', 'a'), "failed assertion"); // verify switch between col and row
	EXPECT_DEATH(ttt_.getMark('a' - 1, '1'), "failed assertion"); // border condition: col one less than minimum
	EXPECT_DEATH(ttt_.getMark('c' + 1, '1'), "failed assertion"); // border condition: col one more than maximum
	EXPECT_DEATH(ttt_.getMark('a', '0'), "failed assertion"); // border condition: row one less than minimum
	EXPECT_DEATH(ttt_.getMark('a', '4'), "failed assertion"); // border condition: row one more than maximum
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
