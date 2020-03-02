//============================================================================
// Name        : TicTacToeTests.cpp
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

class TicTactToeTest: public ::testing::Test {
protected:
	friend class TicTacToe;
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
	EXPECT_TRUE(ttt_.properlyInitialized());
	// verify post-condition
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
	char col, row;
	for (col = minCol; col <= maxCol; col++)
		for (row = minRow; row <= maxRow; row++) {
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
	for (col = minCol; col <= maxCol; col++)
		for (row = minRow; row <= maxRow; row++) {
			if (markIsX)
				EXPECT_EQ('X', ttt_.getMark(col, row));
			else
				EXPECT_EQ('O', ttt_.getMark(col, row));
			markIsX = not markIsX;
		}EXPECT_FALSE(ttt_.notDone());
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

bool DirectoryExists(const std::string dirname) {
	struct stat st;
	return stat(dirname.c_str(), &st) == 0;
}

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
	ifstream leftFile, rightFile;
	char leftRead, rightRead;
	bool result;

	// Open the two files.
	leftFile.open(leftFileName);
	if (!leftFile.is_open()) {
		return false;
	};
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	};

	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		result = (leftRead == rightRead);
	};
	if (result) {
		 // last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	};

	leftFile.close();
	rightFile.close();
	return result;
}

// Tests the compare files
TEST_F(TicTactToeTest, FileCompare) {
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

// Tests the output of the "happy day" scenario
TEST_F(TicTactToeTest, OutputHappyDay) {
	ASSERT_TRUE(DirectoryExists("testOutput"));
	//if directory doesn't exist then no need in proceeding with the test

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

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
