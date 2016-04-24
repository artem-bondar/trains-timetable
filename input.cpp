#include "input.h"
#include "interface.h"
#include "lexer.h"
#include "implements.h"
#include "train.h"

const string* Input::getFileName(int argc, char* argv[]) {
	string* output = new string[2];
	output[0] = argv[0];
	output[0] = output[0].substr(0, output[0].find_last_of(text.backslash) + 1); // Gets path of .exe file
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++) {
			output[1] += argv[i];
		}
	}
	else
	{ 
		UI.showInputDialog(text.inputFileName);
		inputName(&output[1]);
	}
	lexer.clearWhiteCharacters(output[1]);
	return output;
}

const bool Input::checkChar(char character) {
	return checkElementInArray((int)character, text.allowedKeys, sizeof(text.allowedKeys));
}

const unsigned int* Input::getTwoStations() {
	unsigned int* output = new unsigned int[2];
	unsigned int currentStation = 0, inputted = 0, lastStationIndex = allStations.getSize() - 1;
	char keyValue;
	UI.showStationsList(currentStation, output[0], inputted);
	while (inputted != 2)
	{
		keyValue = _getch();
		if (checkChar(keyValue))
		{
			switch (keyValue) {
			case W:
			{
				if (currentStation)
					currentStation--;
				else
					currentStation = lastStationIndex;
				if (inputted && currentStation == output[0])
				// Provides additional shift if current highlighted station is already inputted
				{
					if (currentStation)
						currentStation--;
					else
						currentStation = lastStationIndex;
				}
				break;
			}
			case S:
			{
				if (currentStation == lastStationIndex)
					currentStation = 0;
				else
					currentStation++;
				if (inputted && currentStation == output[0])
				{
					if (currentStation == lastStationIndex)
						currentStation = 0;
					else
						currentStation++;
				}
				break;
			}
			case ENTER:
			{
				output[inputted] = currentStation;
				inputted++;
				if (inputted == 1)
				{
					currentStation = 0;
					if (currentStation == output[0])
						currentStation++;
				}
			}
			}
			UI.clearStationsList();
			UI.showStationsList(currentStation, output[0], inputted);
		}
	}
	return output;
}

const string& Input::getSaveTarget() {
	string* output = new string;
	UI.showInputDialog(text.saveDialog);
	inputName(output);
	output->pop_back();
	return *output;
}

void Input::inputName(string* line) const {

	// Provides extended input with workable Backspace

	char input;
	do {
		input = _getch();
		if (input == BACKSPACE)
		{
			if (line->size())
			{
				cout << text.whiteSpaces[1] << text.whiteSpaces[5] << text.whiteSpaces[1];
				line->pop_back();
			}
		}
		else
		{
			cout << input;
			*line += input;
		}
	} while (input != ENTER);
}