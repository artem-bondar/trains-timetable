#include "builder.h"
#include "filehandler.h"
#include "lexer.h"
#include "interface.h"

void Builder::loadFromFileToContainers(const string* fileName, Container<string> &allStations, Container<Train> &allTrains) {
	try {

		fileHandler.tryToOpenFile(fileName);

		unsigned int lineCounter = 1;

		try {

			string* buffer = new string;

			getline(fileHandler.file, *buffer);
			lexer.clearWhiteCharacters(*buffer);
			allStations = lexer.parseHeader(*buffer);

			while (!fileHandler.file.eof())
			{
				lineCounter++;
				getline(fileHandler.file, *buffer);
				lexer.clearWhiteCharacters(*buffer);

				if (!fileHandler.file.eof()) // If eof - footer was readed, else - record
				{
					loadInfoFromRecord(buffer);
				}
				else
				{
					lexer.parseFooter(*buffer, allTrains.getSize(), lineCounter - 2); 
					sortAndCheckContainers(allTrains);
				}
			}
			fileHandler.file.close();
		}
		catch (const unsigned int errorCode) {
			UI.showError(errorCode, lineCounter);
			throw false;
		}
		catch (int trainNumber)
		{
			print(text.errors[13] + to_string(trainNumber) + text.whiteSpaces[5], WHITE, RED);
			throw false;
		}
	}
	catch (bool fileError)
	{
		if (fileError)
			print(text.openError + text.whiteSpaces[0], WHITE, RED);
		cout << text.whiteSpaces[3] << text.whiteSpaces[5] << text.sound;
		throw true;
	}
}

void Builder::loadInfoFromRecord(string* buffer) {

	const unsigned int* pointer; // For receiving array from lexer::parseRecord()
	unsigned int index;			 // To save current train index in dynamic increasing trains numeration in stack of all trains

	pointer = lexer.parseRecord(*buffer);

	Train* train = new Train;
	train->trainNumber = pointer[0];
	Train::Record* record = new Train::Record(pointer[1],
	Train::Record::Time(pointer[2], pointer[3]), Train::Record::Time(pointer[4], pointer[5]));

	index = allTrains.getIndexOf(*train);

	if (index)
		allTrains[index].timetable.push(*record);
	else
	{
		train->timetable.push(*record);
		allTrains.push(*train);
	}
}

void Builder::sortAndCheckContainers(Container<Train> &allTrains) {
	allTrains.freeze(false);
	for (unsigned int i = 0; i < allTrains.getSize(); i++)
	{
		allTrains[i].timetable.freeze();
		allTrains[i].timetable.insertSort();
		allTrains[i].checkRoute();
	}
}