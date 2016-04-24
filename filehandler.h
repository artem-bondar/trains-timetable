#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>

using namespace std;

class FileHandler {
public:

	void
		doOutput(const string &target, char* argv[]) const;

private:

	friend class Builder;

	void
		tryToOpenFile(const string* filename);

	ifstream file;

};

extern FileHandler fileHandler;

#endif