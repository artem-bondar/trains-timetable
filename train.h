#ifndef TRAIN_H
#define TRAIN_H

#include <string>

#include "container.h"

using namespace std;

class Train {
public:

	class Record {
	public:

		class Time {
		public:
			
			Time() {}
			Time(const unsigned int Hours, const unsigned int Minutes);

			Time
				operator+(const Time &anotherTime) const,
				operator-(const Time &anotherTime) const;
			bool
				operator>(const Time &anotherTime) const,
				operator<(const Time &anotherTime) const,
				operator>=(const Time &anotherTime) const,
				operator<=(const Time &anotherTime) const,
				operator==(const Time &anotherTime) const,
				operator!=(const Time &anotherTime) const;
			void
				operator=(const Time &anotherTime);
			friend ostream&
				operator<<(ostream& ostream, const Time time);
			friend void
				operator<<(string& line, const Time time);

		private:

			unsigned int hours, minutes;
		
		};

		Record() {}
		Record(const unsigned int Station, const Time Arrival, const Time Departure);
		
		bool
			operator>(const Record &anotherRecord) const,
			operator<(const Record &anotherRecord) const,
			operator>=(const Record &anotherRecord) const,
			operator<=(const Record &anotherRecord) const,
			operator==(const Record &anotherRecord) const,
			operator!=(const Record &anotherRecord) const;
		friend ostream&
			operator<<(ostream& ostream, const Record record);

	private:

		friend class Train;

		unsigned int station;

		Time arrival, departure;

	};

	class Route {
	public:

		Route() {}
		Route(const Train &train, const bool &IsStartStationFirstInTimetable,
			  const Record::Time &DepartureFromStart, const Record::Time &ArrivalToTarget, const Record::Time &RouteLength);

		string&
			getInfoInString() const;

		bool
			operator>(const Route &anotherRoute) const,
			operator<(const Route &anotherRoute) const,
			operator>=(const Route &anotherRoute) const,
			operator<=(const Route &anotherRoute) const,
			operator==(const Route &anotherRoute) const,
			operator!=(const Route &anotherRoute) const;

	private:

		friend class Train;
		friend class Finder;

		bool isStartStationFirstInTimetable;

		unsigned int trainIndex;
		
		Record::Time departureFromStart, arrivalToTarget, routeLength;

	};

	bool
		operator==(const Train &anotherTrain) const,
		operator>(const Train &anotherTrain) const;

	friend ostream&
		operator<<(ostream& ostream, const Train train);

private:

	friend class Builder;
	friend class Finder;

	void
		checkRoute();

	Container<string>&
		getRoute(const Record::Time departureTime, const Record::Time arrivalTime);

	Container<Route>&
		findAllRoutes(const unsigned int* stations);

	unsigned int trainNumber;

	Container<Record> timetable;

};

extern Container<Train> allTrains;
extern Container<string> allStations;

#endif