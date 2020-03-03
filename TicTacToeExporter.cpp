//============================================================================
// Name        : TicTacToeExporter.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "DesignByContract.h"
#include "TicTacToeExporter.h"

using namespace std;


TicTacToeExporter::TicTacToeExporter() {
	_initCheck = this;
	_documentStarted = false;
	ENSURE(properlyInitialized(),
			"constructor must end in properlyInitialized state");
}


bool TicTacToeExporter::properlyInitialized() {
	return _initCheck == this;
}

bool TicTacToeExporter::documentStarted() {
	return _documentStarted;
}


void TicTacToeExporter::exportOn (std::ostream& onStream, TicTacToe &game) {
	char col, row;
	REQUIRE(this->properlyInitialized(), "TicTacToeExporter wasn't initialized when calling exportOn.");
	REQUIRE(game.properlyInitialized(), "TicTacToe wasn't initialized when calling exportOn");
	REQUIRE(this->documentStarted(), "TicTacToeExporter wasn't in documentStarted when calling exportOn.");

	if (game.nrOfMoves() == 1) {
		this->sectionStart(onStream, "TicTacToe (1 move)");
	} else {
		this->sectionStart(onStream, "TicTacToe (" + std::to_string(game.nrOfMoves()) + " moves)");
	};
	if (game.getWinner() != ' ') {this->announceWinner(onStream, game.getWinner());}

	this->boardStart(onStream);
	for (row = minRow; row <= maxRow; row++) {
		this->rowStart(onStream, row - minRow + 1);
		for (col = minCol; col <= maxCol; col++) {
			this->cell(onStream, game.getMark(col, row));
		}
		this->rowEnd(onStream);		
	};
	this->boardEnd(onStream);
	this->sectionEnd(onStream);
}


// Following are the hook methods to be overridden in subclasses

void TicTacToeExporter::documentStart (std::ostream& onStream) {_documentStarted = true;}
void TicTacToeExporter::documentEnd (std::ostream& onStream) {_documentStarted = false;}

void TicTacToeExporter::sectionStart (std::ostream& onStream, const string sectionTitle) {
	onStream << sectionTitle << std::endl;}
void TicTacToeExporter::sectionEnd (std::ostream& onStream) {}

void TicTacToeExporter::boardStart (std::ostream& onStream) {
	onStream 	<< "    a   b   c   " << std::endl
				<< "  ------------- " << std::endl;
}
void TicTacToeExporter::boardEnd (std::ostream& onStream) {
	onStream << "  ------------- " << std::endl;
}

void TicTacToeExporter::rowStart (std::ostream& onStream, const int row) {
	onStream << row;
}
void TicTacToeExporter::rowEnd (std::ostream& onStream) {
	onStream << " |" << std::endl;
}

void TicTacToeExporter::cell (std::ostream& onStream, char const cellMarker) {
	onStream << " | " << cellMarker;}

void TicTacToeExporter::announceWinner (std::ostream& onStream, const char winnerMarker) {
	onStream << "   And the winner is '" << winnerMarker << "'" <<std::endl;}
	






void TicTacToeHTMLExporter::documentStart (std::ostream& onStream) {
	TicTacToeExporter::documentStart (onStream);
	onStream << "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">" << std::endl
			<< "<html> <head> <meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" >" << std::endl
			<< "<title>ticTacToe</title></head>" << std::endl
			<< "<body>" << std::endl;
}

void TicTacToeHTMLExporter::documentEnd (std::ostream& onStream) {
	TicTacToeExporter::documentEnd (onStream);
	onStream << "<p><a href=\"http://validator.w3.org/check?uri=referer\">"
		<< "<img src=\"http://www.w3.org/Icons/valid-html40\" "
		<< "alt=\"Valid HTML\"></a></p>" << std::endl
		<< "</body>" << std::endl;}

void TicTacToeHTMLExporter::sectionStart (std::ostream& onStream, const string sectionTitle) {
	onStream << "<h1>" << sectionTitle << "</h1>" << std::endl;}

void TicTacToeHTMLExporter::boardStart (std::ostream& onStream) {
	onStream 	<<  "<pre>" << std::endl << "    a   b   c   " << std::endl
				<< "  ------------- " << std::endl;
}
void TicTacToeHTMLExporter::boardEnd (std::ostream& onStream) {
	onStream << "  ------------- " << std::endl <<  "</pre>" << std::endl;
}

void TicTacToeHTMLExporter::rowStart (std::ostream& onStream, const int row) {
	onStream << row;
}
void TicTacToeHTMLExporter::rowEnd (std::ostream& onStream) {
	onStream << " |" << std::endl;
}

void TicTacToeHTMLExporter::cell (std::ostream& onStream, char const cellMarker) {
	onStream << " | " << cellMarker;}

void TicTacToeHTMLExporter::announceWinner (std::ostream& onStream, const char winnerMarker) {
	onStream << "<p>And the <em>winner</em> is '" << winnerMarker << "'.</p>" <<std::endl;
}








void TicTacToeHTMLTablesIconExporter::boardStart (std::ostream& onStream) {
	onStream 	<<  "<table border=""1"">" << std::endl
				<<  "  <tbody>" << std::endl;
}
void TicTacToeHTMLTablesIconExporter::boardEnd (std::ostream& onStream) {
	onStream 	<<  "  </tbody>" << std::endl
				<<  "</table>" << std::endl;
				
}

void TicTacToeHTMLTablesIconExporter::rowStart (std::ostream& onStream, const int row) {
	onStream 	<<  "    <tr>" << std::endl;
}
	
void TicTacToeHTMLTablesIconExporter::rowEnd (std::ostream& onStream) {
	onStream 	<<  "    </tr>" << std::endl;
}


void exportCellMarkerAsImgRef (std::ostream& onStream, char const cellMarker) {
	if (cellMarker == 'O') {
		onStream << "<img src=""OMarker.png"" alt= ""O"">";
	} else if (cellMarker == 'X') {
		onStream << "<img src=""XMarker.png"" alt= ""X"">";
	} else if (cellMarker == ' ') {
		onStream << "<img src=""WhiteSpaceMarker.png"" alt= ""&nbsp;"">";
	} else {
		onStream << "&nbsp;";		
	};
}

void TicTacToeHTMLTablesIconExporter::cell (std::ostream& onStream, char const cellMarker) {
	onStream 	<<  "      <td>";
	exportCellMarkerAsImgRef(onStream, cellMarker);
	onStream << "</td>" << std::endl;
}


void TicTacToeHTMLTablesIconExporter::announceWinner (std::ostream& onStream, const char winnerMarker) {
	onStream << "<p>And the <em>winner</em> is ";
	exportCellMarkerAsImgRef(onStream, winnerMarker);
	onStream << ".</p>" <<std::endl;
}

