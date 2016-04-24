#include "finder.h"
#include "train.h"
#include "text.h"

void Finder::getAllTrainsCoursingBetween(const unsigned int* stations) {
	result.push(text.finder[0] + allStations[stations[0]] + text.finder[1] + allStations[stations[1]] + text.separators[1] + text.whiteSpaces[3]);

	Container<Train::Route>* allRoutes = new Container<Train::Route>;
	Container<Train::Route>* route = new Container<Train::Route>;

	try {
		for (unsigned int i = 0; i < allTrains.getSize(); i++)
		{
			*route = allTrains[i].findAllRoutes(stations);
			while (route->getSize())
				allRoutes->push(route->pop());
		}

		if (!allRoutes->getSize())
			throw true;
		allRoutes->freeze();
		allRoutes->insertSort();

		Train::Record::Time minTime(24, 0), departureTime, arrivalTime;
		unsigned int minTrainNumberIndex;

		for (unsigned int i = 0; i < allRoutes->getSize(); i++)
		{
			result.push(allRoutes->operator[](i).getInfoInString());
			if (allRoutes->operator[](i).routeLength < minTime)
			{
				minTime = allRoutes->operator[](i).routeLength;
				minTrainNumberIndex = allRoutes->operator[](i).trainIndex;
				departureTime = allRoutes->operator[](i).departureFromStart;
				arrivalTime = allRoutes->operator[](i).arrivalToTarget;
			}
		}

		string minTimeBuffer;
		minTimeBuffer << minTime;
		result.push(text.finder[2] + text.brackets[0] + minTimeBuffer + text.brackets[1] + text.finder[3] + 
					to_string(allTrains[minTrainNumberIndex].trainNumber) + text.separators[1] + text.whiteSpaces[3]);

		Container<string>* minRoute = new Container<string>;
		*minRoute = allTrains[minTrainNumberIndex].getRoute(departureTime, arrivalTime);

		for (unsigned int i = 0; i < minRoute->getSize(); i++)
			result.push(minRoute->operator[](i));
	}
	catch (bool) {
		result.push(text.errors[14]);
	}
	result.freeze(false);
}

ostream& operator<<(ostream &ostream, const Container<string> container)
{
	for (unsigned int i = 0; i < container.getSize(); i++)
		ostream << container[i] + text.whiteSpaces[3];
	return ostream;
}