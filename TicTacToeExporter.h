//============================================================================
// Name        : TicTacToeExporter.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

// Below are two lines serving as a so-called ``header guard''.
// Prevents from loading the same .h file multiple times
#ifndef TicTacToeExporter_H
#define TicTacToeExporter_H


#include <iostream>
#include "TicTacToe.h"


class TicTacToeExporter {
public:

/**
\n ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state.");
\n REQUIRE(! this->documentStarted(), "After constructor a TicTacToeExporter is *not* in the documentStarted state.");
*/
	TicTacToeExporter ();

	bool properlyInitialized();
	bool documentStarted();

/**
\n REQUIRE(! this->documentStarted(), "TicTacToeExporter was in documentStarted when calling documentStart.");
\n ENSURE(this->documentStarted(), "TicTacToeExporter should be in documentStarted after calling documentStart.");
*/
	virtual void documentStart (std::ostream& onStream);
/**
\n REQUIRE(this->documentStarted(), "TicTacToeExporter wasn't in documentStarted when calling documentEnd.");
\n ENSURE(! this->documentStarted(), "TicTacToeExporter should not be in documentStarted after calling documentEnd.");
*/
	virtual void documentEnd (std::ostream& onStream);



/**
\n REQUIRE(this->properlyInitialized(), "TicTacToeExporter wasn't initialized when calling exportOn.");
\n REQUIRE(this->documentStarted(), "TicTacToeExporter wasn't in documentStarted state when calling exportOn.");
\n REQUIRE(game.properlyInitialized(), "game wasn't initialized when passing to Exporter::exportOn.");
*/
	void exportOn (std::ostream& onStream, TicTacToe &game);

protected:
	virtual void sectionStart (std::ostream& onStream, const std::string sectionTitle);
	virtual void sectionEnd (std::ostream& onStream);
	virtual void boardStart (std::ostream& onStream);
	virtual void boardEnd (std::ostream& onStream);
	virtual void rowStart (std::ostream& onStream, const int row);
	virtual void rowEnd (std::ostream& onStream);
	virtual void cell (std::ostream& onStream, const char cellMarker);
	virtual void announceWinner (std::ostream& onStream, const char winnerMarker);

private:
	TicTacToeExporter * _initCheck; //!use pointer to myself to verify whether I am properly initialized
	bool _documentStarted;
	
};


class TicTacToeHTMLExporter : public TicTacToeExporter {

public:
	virtual void documentStart (std::ostream& onStream);
	virtual void documentEnd (std::ostream& onStream);


protected:
	virtual void sectionStart (std::ostream& onStream, const std::string sectionTitle);
	virtual void boardStart (std::ostream& onStream);
	virtual void boardEnd (std::ostream& onStream);
	virtual void rowStart (std::ostream& onStream, const int row);
	virtual void rowEnd (std::ostream& onStream);
	virtual void cell (std::ostream& onStream, const char cellMarker);
	virtual void announceWinner (std::ostream& onStream, const char winnerMarker);

};

class TicTacToeHTMLTablesIconExporter : public TicTacToeHTMLExporter {

public:


protected:
	virtual void boardStart (std::ostream& onStream);
	virtual void boardEnd (std::ostream& onStream);
	virtual void rowStart (std::ostream& onStream, const int row);
	virtual void rowEnd (std::ostream& onStream);
	virtual void cell (std::ostream& onStream, const char cellMarker);
	virtual void announceWinner (std::ostream& onStream, const char winnerMarker);

};




// Closing of the ``header guard''.
#endif