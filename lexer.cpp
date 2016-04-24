#include "lexer.h"
#include "implements.h"
#include "text.h"
#include "interface.h"
#include "train.h"

void Lexer::clearWhiteCharacters(string &line) {
	string output;
	for (char i : line)
		if (!checkElementInArray(i, text.whiteSpaces, WHITE_SPACES_SIZE)) output += i;
	line = output;
}

void Lexer::clearAllExceptDigits(string &line) {
	string output;
	for (char i : line)
		if (isdigit(i) || i == text.separators[0][0]) output += i;
	line = output;
}

const bool Lexer::onlyDigits(const string &line) {
	for (char i : line)
		if (!isdigit(i)) return false;
	return true;
}

const Container<string>& Lexer::parseHeader(string &header) {
	
	// Returns string container with stations names

	Container<string>* output = new Container<string>;
	string subString;
	size_t startSeparator = header.find_first_of(text.separators[0]) + 1;

	if (startSeparator == string::npos)
		throw unsigned int(SEPARATOR_ERROR);

	size_t endSeparator = header.find_first_of(text.separators[2], startSeparator);

	if (endSeparator == string::npos)
		throw unsigned int(SEPARATOR_ERROR);
	do {
		subString = header.substr(startSeparator, endSeparator - startSeparator);
		if (subString.empty())
			throw unsigned int(EMPTY_STATION_NAME_ERROR);
		output->push(subString);
		startSeparator = endSeparator + 1;
		endSeparator = header.find_first_of(text.separators[2], startSeparator);
	} while (endSeparator != string::npos);

	endSeparator = header.find_first_of(text.separators[0], startSeparator);
	if (endSeparator == string::npos)
		throw unsigned int(SEPARATOR_ERROR);
	subString = header.substr(startSeparator, endSeparator - startSeparator);
	if (subString.empty())
		throw unsigned int(EMPTY_STATION_NAME_ERROR);

	output->push(subString);

	startSeparator = endSeparator + 1;
	subString = header.substr(startSeparator);
	if (!subString.empty())
		throw unsigned int(EXTRA_CHARACTERS_ERROR);
	output->freeze(false);
	return *output;
}

const unsigned int* Lexer::parseRecord(string &record) {

	// Returns array parsed from Record
	// It contains:

	// Train     number
	// Station   index from all stations array
	// Arrival   hours
	// Arrival   minutes
	// Departure hours
	// Departure minutes

	unsigned int* output = new unsigned int[6];
	size_t startSeparator = 0;
	size_t endSeparator = record.find_first_of(text.separators[0]);

	if (endSeparator == string::npos)
		throw unsigned int(SEPARATOR_ERROR);

	string subString;
	subString = record.substr(startSeparator, endSeparator - startSeparator);

	if (!onlyDigits(subString))
		throw unsigned int(TRAIN_NUMBER_ERROR);
	if (subString.empty())
		throw unsigned int(EMPTY_TRAIN_NUMBER_ERROR);

	output[0] = stoi(subString);
	for (int i = 1; i < 6; i++)
	{
		startSeparator = endSeparator + 1;
		endSeparator = record.find_first_of(text.separators[!(i % 2)], startSeparator);
		if (endSeparator == string::npos)
			throw unsigned int(SEPARATOR_ERROR);
		subString = record.substr(startSeparator, endSeparator - startSeparator);
		if (i == 1)
		{
			output[i] = allStations.getIndexOf(subString);
			if (!output[i])
				throw unsigned int(UNKNOWN_STATION_ERROR);
			output[i]--;
			continue;
		}
		if (!onlyDigits(subString))
			throw unsigned int(TIME_ERROR);
		if (subString.empty())
			throw unsigned int(EMPTY_TIME_ERROR);
		output[i] = stoi(subString);
		if ((!(i % 2) && output[i] > 23) || ((i % 2) && output[i] > 59))
			throw unsigned int(INCORRECT_TIME_FORMAT_ERROR);
	}

	startSeparator = endSeparator + 1;
	subString = record.substr(startSeparator);
	if (!subString.empty())
		throw unsigned int(EXTRA_CHARACTERS_ERROR);
	return output;
}

void Lexer::parseFooter(string &footer, const unsigned int &totalNumberOfTrains, const unsigned int &totalNumberOfRecords) {

	// Checks footer values and breaks with exception if not correct

	size_t startSeparator = 0;
	size_t endSeparator = footer.find_first_of(text.separators[0]);

	if (endSeparator == string::npos)
		throw unsigned int(SEPARATOR_ERROR);

	startSeparator = endSeparator + 1;
	endSeparator = footer.find_first_of(text.separators[0], startSeparator);
	if (endSeparator == string::npos)
		throw unsigned int(SEPARATOR_ERROR);

	startSeparator = endSeparator + 1;
	string subString = footer.substr(startSeparator);
	if (!subString.empty())
		throw unsigned int(EXTRA_CHARACTERS_ERROR);

	clearAllExceptDigits(footer);
	startSeparator = 0;
	endSeparator = footer.find_first_of(text.separators[0]);
	subString = footer.substr(startSeparator, endSeparator - startSeparator);

	if (subString.empty())
		throw unsigned int(EMPTY_TRAINS_NUMBER_ERROR);
	if (stoi(subString) != totalNumberOfTrains)
		throw unsigned int(INCORRECT_TRAINS_NUMBER_ERROR);

	startSeparator = endSeparator + 1;
	endSeparator = footer.find_first_of(text.separators[0], startSeparator);
	subString = footer.substr(startSeparator, endSeparator - startSeparator);

	if (subString.empty())
		throw unsigned int(EMPTY_RECORDS_NUMBER_ERROR);
	if (stoi(subString) != totalNumberOfRecords)
		throw unsigned int(INCORRECT_RECORDS_NUMBER_ERROR);
}