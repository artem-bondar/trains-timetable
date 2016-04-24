#ifndef INPUT_H
#define INPUT_H

#include <conio.h>
#include <string>

using namespace std;

class Input {
public:

	const bool
		checkChar(char keyValue);

	const unsigned int*
		getTwoStations();

	const string&
		getSaveTarget();

	const string*
		getFileName(int argc, char* argv[]);

private:
	
	void inputName(string* line) const;

};

extern Input input;

#endif