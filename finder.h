#ifndef FINDER_H
#define FINDER_H

#include <ostream>

#include "container.h"

using namespace std;

class Finder {
public:

	void
		getAllTrainsCoursingBetween(const unsigned int* stations);
	friend ostream&
		operator<<(ostream &ostream, const Container<string> container);

private:
	
	friend class FileHandler;

	Container<string> result;

};

extern Finder finder;

#endif