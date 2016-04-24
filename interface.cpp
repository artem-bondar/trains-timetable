#include "interface.h"
#include "train.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Getting console output descriptor and saving it in "hStdOut" identifier
CONSOLE_SCREEN_BUFFER_INFO csbi; // (On initialization is empty)
								 // CSBI-typedef variable for saving different info about console in it's fields like:
								 // - dwCursorPosition, that stores coordinates of cursor in COORD-typedef
								 // Isn't a dynamic variable
								 // - dwSize - sizes of console
								 // - etc.

void Interface::clearConsoleRow(const short rowNumber = 0, const short moveCursor = 0) const {
	// Clear exact (rowNumber) console line
	// Type "short" is used because API functions requires COORD-typedef for coordinates, which used short X, Y fields
	GetConsoleScreenBufferInfo(hStdOut, &csbi); // Save current info about console in global "csbi" variable
	DWORD binBuffer; // DWORD-typedef (double word - 64-bits) to save number of printed chars in FillConsoleOutputCharacter-function
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', csbi.dwSize.X, { 0, csbi.dwCursorPosition.Y - rowNumber }, &binBuffer);
	// WinAPI function for printing character that receives next arguments:
	// - HANDLE %identifiername% - identifier of console screen, where the character will be printed
	// - TCHAR-typedef %char% - printed character
	// - DWORD %number% - how many times in a row character will be printed
	// - COORD-typedef %variablename% - coordinates, starting from what the character will be printed
	// Instead of COORD can be used it's equivalent - {short X, short Y}
	// - LPDWORD-typedef (pointer to DWORD) %variablename% - pointer to the variable, that will 
	// receive the number of real printed symbols 
	SetConsoleCursorPosition(hStdOut, { 0, csbi.dwCursorPosition.Y - moveCursor });
	// Restoring cursor position with "moveCursor" incrementing
	// WinAPI function for setting cursor to new position, receives next argumnets:
	// - HANDLE %identifiername%
	// - COORD %variablename%
}

void Interface::showInfo() const {
	SetConsoleTitle((LPCSTR)text.title.c_str());
	print(text.task, WHITE, MAGENTA);
	print(text.bnf, WHITE, CYAN);
	print(text.bnfInput, RED, WHITE);
	for (unsigned int i = 0; i < BNF_INPUT_SIZE; i++)
		print(text.inputBnf[i], text.inputBnfTextColors[i], WHITE);
	print(text.extendedN + text.bnfOutput, RED, WHITE);
	for (unsigned int i = 0; i < BNF_OUTPUT_SIZE; i++)
		print(text.outputBnf[i], text.outputBnfTextColors[i], WHITE);
	print(text.bnfHint, LIGHT_GREY, BLUE);
}

void Interface::clearStationsList() const {
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	DWORD binBuffer;
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', (csbi.dwCursorPosition.Y - lastPosition) * csbi.dwSize.X, { 0, lastPosition }, &binBuffer);
	FillConsoleOutputAttribute(hStdOut, BLACK, (csbi.dwCursorPosition.Y - lastPosition) * csbi.dwSize.X, { 0, lastPosition }, &binBuffer);
	SetConsoleCursorPosition(hStdOut, { 0, lastPosition });
}

void Interface::showMenu() {
	print(text.menu, BLUE, LIGHT_GREY);
	print(text.menuHint, LIGHT_GREY, BLUE);
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	lastPosition = csbi.dwCursorPosition.Y;
}

void Interface::showStationsList(const unsigned int &currentStation, const unsigned int &previousStation, const unsigned int &inputted) const {
	for (unsigned int i = 0; i < allStations.getSize(); i++)
	{
		if (i == currentStation)
		{
			if (inputted == 2)
				print(text.whiteSpaces[5] + allStations[i] + text.whiteSpaces[3], WHITE);
			else
				print(text.whiteSpaces[5] + allStations[i] + text.whiteSpaces[5] + text.whiteSpaces[3], LIGHT_BLUE, LIGHT_GREY);
		}
		else if (i == previousStation && inputted)
		{
			print(text.whiteSpaces[5] + allStations[i] + text.whiteSpaces[3], WHITE);
		}
		else
			print(text.whiteSpaces[5] + allStations[i] + text.whiteSpaces[3], DARK_GREY);
	}
	cout << text.whiteSpaces[5];
}

void Interface::showError(const unsigned int errorCode, const unsigned int lineCounter) const {
	switch (errorCode) {
	case SEPARATOR_ERROR:
	case TRAIN_NUMBER_ERROR:
	case TIME_ERROR:
	{
		print(text.errors[errorCode] + text.errors[1], WHITE, RED);
		break;
	}
	case INCORRECT_TRAINS_NUMBER_ERROR:
	case INCORRECT_RECORDS_NUMBER_ERROR:
	{
		print(text.errors[errorCode] + text.errors[8], WHITE, RED);
		break;
	}
	case UNKNOWN_STATION_ERROR:
	case INCORRECT_TIME_FORMAT_ERROR:
	case EXTRA_CHARACTERS_ERROR:
	{
		print(text.errors[errorCode], WHITE, RED);
		break;
	}
	case EMPTY_STATION_NAME_ERROR:
	{
		print(text.errors[errorCode] + text.errors[10], WHITE, RED);
		break;
	}
	case EMPTY_TRAIN_NUMBER_ERROR:
	case EMPTY_TIME_ERROR:
	case EMPTY_TRAINS_NUMBER_ERROR:
	case EMPTY_RECORDS_NUMBER_ERROR:
	{
		print(text.errors[errorCode % 10] + text.errors[10], WHITE, RED);
		break;
	}
	}
	print(text.errors[0] + to_string(lineCounter) + text.whiteSpaces[5], WHITE, RED);
}

void Interface::showInputDialog(const string &name) const {
	print(name, BLUE, LIGHT_GREY);
	cout << text.whiteSpaces[5] << text.whiteSpaces[3];
	cout << text.terminal;
}