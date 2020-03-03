//============================================================================
// Name        : TicTacToeDomainTests.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "TicTacToe.h"

class TicTactToeDomainTest: public ::testing::Test {
protected:
	friend class TicTacToe;
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	TicTacToe ttt_;
	TicTacToePlayer tttPlayer_;

};

/**
Tests the default constructor.
*/
TEST_F(TicTactToeDomainTest, DefaultConstructor) {
	EXPECT_TRUE(ttt_.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
	char col, row;
	for (col = minCol; col <= maxCol; col++)
		for (row = minRow; row <= maxRow; row++) {
			EXPECT_EQ(' ', ttt_.getMark(col, row));
		};
	EXPECT_TRUE(tttPlayer_.properlyInitialized());
	EXPECT_EQ('X', tttPlayer_.getMarker());
}

/**
Tests the "happy day" scenario
*/
TEST_F(TicTactToeDomainTest, HappyDay) {
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
	ttt_.setMoves("a1c1b2a3c3", "b1a2c2b3");
	while (ttt_.notDone()) {
		ttt_.doMove();
	};
	char col, row;
	bool markIsX = false; // start with 'O'
	// The diagonal is recognised as a winner. Sow we stop after verifying first two rows
	for (row = minRow; row < maxRow; row++)
		for (col = minCol; col <= maxCol; col++) {
			if (markIsX)
				EXPECT_EQ('X', ttt_.getMark(col, row));
			else
				EXPECT_EQ('O', ttt_.getMark(col, row));
			markIsX = not markIsX;
		};
	EXPECT_FALSE(ttt_.notDone());
	EXPECT_EQ(7, ttt_.nrOfMoves());
}

/**
Tests whether a given string of moves is legal
*/
TEST_F(TicTactToeDomainTest, LegalMoves) {
	EXPECT_TRUE(tttPlayer_.properlyInitialized());
	EXPECT_TRUE(TicTacToePlayer::legalMoves(""));
	EXPECT_TRUE(TicTacToePlayer::legalMoves("a1"));
	EXPECT_TRUE(TicTacToePlayer::legalMoves("a1b2c3"));
	EXPECT_TRUE(TicTacToePlayer::legalMoves("a1a2a3b1b2b3c1c2c3"));
	//illegal moves
	EXPECT_FALSE(TicTacToePlayer::legalMoves(" "));
	EXPECT_FALSE(TicTacToePlayer::legalMoves("a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a"));
	EXPECT_FALSE(TicTacToePlayer::legalMoves(" "));
	EXPECT_FALSE(TicTacToePlayer::legalMoves("b1k1a1"));
	EXPECT_FALSE(TicTacToePlayer::legalMoves("b1c4a1"));
}

/**
Tests the various "configurations" of winning boards
*/
TEST_F(TicTactToeDomainTest, TestWinningColumns) {
	ttt_.setMoves("a1a2a3", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("b1b2b3", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("c1c2c3", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "a1a2a3");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "b1b2b3");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "c1c2c3");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
}

TEST_F(TicTactToeDomainTest, TestWinningRows) {
	ttt_.setMoves("a1b1c1", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("a2b2c2", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("a3b3c3", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "a1b1c1");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "a2b2c2");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "a3b3c3");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
}

TEST_F(TicTactToeDomainTest, TestWinningDiagonals) {
	ttt_.setMoves("a1b2c3", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("a3b2c1", "");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('O', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "a1b2c3");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
	ttt_.reset();
	ttt_.setMoves("", "a3b2c1");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ('X', ttt_.getWinner());
}

TEST_F(TicTactToeDomainTest, TestNoWinner) {
	ttt_.setMoves("b2c1a2c3b3", "b1a3c2a1");
	while (ttt_.notDone()) ttt_.doMove();
	EXPECT_EQ(' ', ttt_.getWinner());
	ttt_.reset();
}


/**
Tests the "happy day" scenario for a player
*/
TEST_F(TicTactToeDomainTest, HappyDayPlayer) {
	EXPECT_TRUE(tttPlayer_.properlyInitialized());
	tttPlayer_.setMarker('O');
	EXPECT_EQ('O', tttPlayer_.getMarker());
	tttPlayer_.setMarker('X');
	EXPECT_EQ('X', tttPlayer_.getMarker());
}

/**
Verify whether unsatisfied pre-conditions indeed trigger failures
*/
TEST_F(TicTactToeDomainTest, ContractViolations) {
	EXPECT_DEATH(ttt_.getMark('1', 'a'), "failed assertion"); // verify switch between col and row
	EXPECT_DEATH(ttt_.getMark('a' - 1, '1'), "failed assertion"); // border condition: col one less than minimum
	EXPECT_DEATH(ttt_.getMark('c' + 1, '1'), "failed assertion"); // border condition: col one more than maximum
	EXPECT_DEATH(ttt_.getMark('a', '0'), "failed assertion"); // border condition: row one less than minimum
	EXPECT_DEATH(ttt_.getMark('a', '4'), "failed assertion"); // border condition: row one more than maximum
    
	EXPECT_DEATH(tttPlayer_.setMarker(' '), "failed assertion"); // off value
}