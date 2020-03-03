//============================================================================
// Name        : TicTactToeOutputTest.cpp
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
#include "TicTacToeUtils.h"

class TicTactToeOutputTest: public ::testing::Test {
protected:
	friend class TicTacToe;

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}

	TicTacToe ttt_;
	TicTacToePlayer tttPlayer_;

};


// Tests the compare files
TEST_F(TicTactToeOutputTest, FileCompare) {
	ASSERT_TRUE(DirectoryExists("testOutput"));

	ofstream myfile;
	myfile.open("testOutput/file1.txt");
	myfile.close();
	myfile.open("testOutput/file2.txt");
	myfile.close();

	//compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
//	EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
//	EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare an empty and a non-empty files
	myfile.open("testOutput/file1.txt");
	myfile << "xxx" << endl << "yyy";
	myfile.close();
	EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare two equal files
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << endl << "yyy";
	myfile.close();
	EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare 2 non-empty files which are off by a character in the middle
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << endl << "xyy";
	myfile.close();
	EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare 2 non-empty files where one is one character shorter than the other
	myfile.open("testOutput/file2.txt");
	myfile << "xxx" << endl << "yy";
	myfile.close();
	EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
	EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

	//compare existig against non existing file
	EXPECT_FALSE(
			FileCompare("testOutput/file1.txt", "testOutput/nonexisting.txt"));
	EXPECT_FALSE(
			FileCompare("testOutput/nonexisting.txt", "testOutput/file1.txt"));
}

/**
Tests the output of the "happy day" scenario (one winner).
*/
TEST_F(TicTactToeOutputTest, OutputHappyDay) {
	ASSERT_TRUE(DirectoryExists("testOutput"));
	//if directory doesn't exist then no need in proceeding with the test

	ttt_.setMoves("a1c1b2a3c3", "b1a2c2b3");

	ofstream myfile;
	myfile.open("testOutput/happyDayOut.txt");
	while (ttt_.notDone()) {
		ttt_.doMove();
		ttt_.writeOn(myfile);
	};
	myfile.close();
	EXPECT_TRUE(
			FileCompare("testOutput/happyDayExpectedOut.txt", "testOutput/happyDayOut.txt"));
}


/**
Tests the output of another "happy day" scenario (without a winner).
*/
TEST_F(TicTactToeOutputTest, OutputNoWinner) {
	ASSERT_TRUE(DirectoryExists("testOutput"));
	//if directory doesn't exist then no need in proceeding with the test

	ttt_.setMoves("b2c1a2c3b3", "b1a3c2a1");
	ofstream myfile;
	myfile.open("testOutput/noWinnerOut.txt");
	while (ttt_.notDone()) {
		ttt_.doMove();
		ttt_.writeOn(myfile);
	};
	myfile.close();
	EXPECT_TRUE(
			FileCompare("testOutput/noWinnerExpectedOut.txt", "testOutput/noWinnerOut.txt"));
}