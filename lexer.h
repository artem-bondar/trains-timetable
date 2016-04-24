#ifndef LEXER_H
#define LEXER_H

#include <string>

#include "container.h"

using namespace std;

class Lexer {
public:

	void
		clearWhiteCharacters(string &line);

private:

	friend class Builder;

	void
		parseFooter(string &footer, const unsigned int &totalNumberOfTrains, const unsigned int &totalNumberOfRecords),
		clearAllExceptDigits(string &line);

	const bool
		onlyDigits(const string &line);

	const unsigned int*
		parseRecord(string &record);

	const Container<string>&
		parseHeader(string &header);

};

extern Lexer lexer;

#endif