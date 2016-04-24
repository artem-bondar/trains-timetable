#ifndef BUILDER_H
#define BUILDER_H

#include "container.h"
#include "train.h"

using namespace std;

class Builder {
public:

	void
		loadFromFileToContainers(const string* fileName, Container<string> &allStations, Container<Train> &allTrains);

private:

	void
		loadInfoFromRecord(string* buffer),
		sortAndCheckContainers(Container<Train> &allTrains);
};

extern Builder builder;

#endif