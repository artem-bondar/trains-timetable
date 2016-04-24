#include "text.h"
#include "interface.h"
#include "lexer.h"
#include "input.h"
#include "builder.h"
#include "train.h"
#include "filehandler.h"
#include "finder.h"

Text text;
Lexer lexer;
Input input;
Interface UI;
Finder finder;
Builder builder;
FileHandler fileHandler;
Container<Train> allTrains;
Container<string> allStations;

void main(int argc, char* argv[]) {
	UI.showInfo();
	try {
		builder.loadFromFileToContainers(input.getFileName(argc, argv), allStations, allTrains);
		UI.showMenu();
		finder.getAllTrainsCoursingBetween(input.getTwoStations());
		fileHandler.doOutput(input.getSaveTarget(), argv);
	}
	catch (...) { } // For stopping function execution, catches nothing because interruption is raised from deeper catch-structure
	_getch();
}