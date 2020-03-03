//============================================================================
// Name        : TicTacToeImporter.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "DesignByContract.h"
#include "TicTacToeImporter.h"
#include "tinyxml.h"

using namespace std;


//Auxiliary function for internal use only

const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
	if (pElement == NULL) return "";
	
	TiXmlNode *elemNode = pElement->FirstChild();
	if (elemNode == NULL) return "";
	TiXmlText* text = elemNode->ToText();
	if(text == NULL) return "";  
	return text->Value();
}

//Below is a static member function but one cannot repeat the static keyword in the implementation

SuccessEnum TicTacToeImporter::importTicTacToeGame(
	const char * inputfilename, std::ostream& errStream, TicTacToe& game) {
	
	TiXmlDocument doc;
	SuccessEnum endResult = Success;

	REQUIRE(game.properlyInitialized(), "game wasn't initialized when passed to TicTacToeImporterimportTicTacToeGame");
	
	if(!doc.LoadFile(inputfilename)) {
		errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << endl;
		return ImportAborted;
	};
	
	for(TiXmlElement* root = doc.FirstChildElement();
			root != NULL; root = root->NextSiblingElement()) {
		string rootName = root->Value();
		if (rootName != "TicTacToe") {
			errStream << "XML PARTIAL IMPORT: Expected <TicTacToe> ... </TicTactToe> and got <"
				<< rootName <<  "> ... </" << rootName << ">." << endl;
			endResult = PartialImport;
		} else {
			TiXmlNode *elem_moves_o, *elem_moves_x;
			string moves_o, moves_x;
			elem_moves_o = root->FirstChild("MOVES_O");
			elem_moves_x = root->FirstChild("MOVES_X");
			if (elem_moves_o == NULL) {
				errStream << "XML PARTIAL IMPORT: Expected <MOVES_O> ... </MOVES_O>." << endl;
				endResult = PartialImport;
				moves_o = "";
			} else {
				moves_o = fetch_text(elem_moves_o, errStream);
			};
			if (elem_moves_x == NULL) {
				errStream << "XML PARTIAL IMPORT: Expected <MOVES_X> ... </MOVES_X>." << endl;
				endResult = PartialImport;
				moves_x = "";
			} else {
				moves_x = fetch_text(elem_moves_x, errStream);
			};
			bool legal_o = TicTacToePlayer::legalMoves(moves_o);
			bool legal_x = TicTacToePlayer::legalMoves(moves_x);
			if (legal_o & legal_x) {
				game.reset();
				game.setMoves(moves_o, moves_x);
			} else {
				if (!legal_o) errStream << "XML PARTIAL IMPORT: Illegal moves '" << moves_o << "'."<< endl;
				if (!legal_x) errStream << "XML PARTIAL IMPORT: Illegal moves '" << moves_x << "'."<< endl;
				endResult = PartialImport;
			}
		}
	};
    
    doc.Clear();

	return endResult;
}