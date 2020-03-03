//============================================================================
// Name        : TicTacToeImporter.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef TicTacToeImporter_H
#define TicTacToeImporter_H


#include <iostream>
#include "TicTacToe.h"


enum SuccessEnum {ImportAborted, PartialImport, Success};


class TicTacToeImporter {
public:

/**
// Read an XML description of a TicTacToeGame from inStream and add it to the board state of game.
// If errors occur, report them on errStream.
// Return whether succesful in the errorcode:
//	- ImportAborted = TicTacToeGame is unchanged; reason for abortion is reported on errStream 
//  - PartialImport = Some semantic errors reported on errStream; state is partially imported and board might have changed
//  - Succes = No importer errors; no errors reported
//\n REQUIRE(game.properlyInitialized(), "game wasn't initialized when passed to TicTacToeImporterimportTicTacToeGame");
//
*/
static SuccessEnum importTicTacToeGame(const char * inputfilename, std::ostream& errStream, TicTacToe& game);

};



// Closing of the ``header guard''.
#endif