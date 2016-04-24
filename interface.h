#ifndef INTERFACE_H
#define INTERFACE_H

#include <Windows.h>
#include <iostream>

#include "text.h"

extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;

class Interface {
public:

	void
		showMenu();
	void
		showInfo() const,
		clearStationsList() const,
		showInputDialog(const string &name) const,
		showError(const unsigned int errorCode, const unsigned int lineCounter) const,
		showStationsList(const unsigned int &currentStation, const unsigned int &previousStation, const unsigned int &inputted) const;

private:
	
	short lastPosition;

	void
		clearConsoleRow(const short rowNumber, const short moveCursor) const;

};

extern Interface UI;

template <class TypeClass> void print(const TypeClass text, const int textColor, const int backgroundColor = BLACK) {
	SetConsoleTextAttribute(hStdOut, (WORD)((backgroundColor << 4) | textColor));
	cout << text;
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | LIGHT_GREY));
}

#endif