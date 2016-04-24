#include <iomanip>

#include "train.h"
#include "text.h"

Train::Record::Record(const unsigned int Station, const Time Arrival, const Time Departure) {
	station = Station;
	arrival = Arrival;
	departure = Departure;
}

Train::Record::Time::Time(const unsigned int Hours, const unsigned int Minutes) {
	hours = Hours;
	minutes = Minutes;
}

Train::Route::Route(const Train &train, const bool &IsStartStationFirstInTimetable,
					const Record::Time &DepartureFromStart, const Record::Time &ArrivalToTarget, const Record::Time &RouteLength) {
	trainIndex = allTrains.getIndexOf(train) - 1;
	isStartStationFirstInTimetable = IsStartStationFirstInTimetable;
	departureFromStart = DepartureFromStart;
	arrivalToTarget = ArrivalToTarget;
	routeLength = RouteLength;
}

string& Train::Route::getInfoInString() const
{
	string* output = new string;
	*output += text.whiteSpaces[5] + to_string(allTrains[trainIndex].trainNumber) + text.whiteSpaces[5];
	*output << departureFromStart;
	*output += text.separators[2];
	*output << arrivalToTarget;
	*output += text.whiteSpaces[5];
	*output += text.brackets[0];
	*output << routeLength;
	*output += text.brackets[1];
	if (isStartStationFirstInTimetable)
		*output += text.plus;
	return *output;
}

void Train::checkRoute() {
	Train::Record::Time in, out;
	in = timetable[0].arrival;
	out = timetable[0].departure;
	if (out < in)
		throw int(trainNumber);
	for (unsigned int i = 1; i < timetable.getSize(); i++)
	{
		in = timetable[i].arrival;
		if (out >= in)
			throw int(trainNumber);
		out = timetable[i].departure;
		if (out < in)
			throw int(trainNumber);
	}
}

Container<string>& Train::getRoute(const Record::Time departureTime, const Record::Time arrivalTime)
{
	Container<string>* output = new Container<string>;
	bool write = false;
	for (unsigned int i = 0; i < timetable.getSize(); i++)
	{
		if (timetable[i].departure == departureTime) write = true;
		if (write) {
			string buffer;
			buffer += text.whiteSpaces[5] + allStations[timetable[i].station] + text.whiteSpaces[5];
			buffer << timetable[i].arrival;
			buffer += text.separators[2];
			buffer << timetable[i].departure;
			output->push(buffer);
		}
		if (timetable[i].arrival == arrivalTime) break;
	}
	output->freeze(false);
	return *output;
}

Container<Train::Route>& Train::findAllRoutes(const unsigned int* stations)
{
	Container<Train::Route>* output = new Container<Train::Route>;
	unsigned int currentStation = 0;
	Train::Record::Time departure, arrival, length;
	while (currentStation < timetable.getSize())
	{
		if (timetable[currentStation].station == stations[0])
		{
			length = Train::Record::Time(0, 0);
			departure = timetable[currentStation].departure;
			for (unsigned int i = currentStation + 1; i < timetable.getSize(); i++)
			{	
				length = length + timetable[i].arrival - departure;
				if (timetable[i].station == stations[1])
				{
					Train::Route* route = new Train::Route(*this, !currentStation, timetable[currentStation].departure, timetable[i].arrival, length);
					output->push(*route);
				}
				length = length + timetable[i].departure - timetable[i].arrival;
				departure = timetable[i].departure;
			}
		}
		currentStation++;
	}
	return *output;
}

Train::Record::Time Train::Record::Time::operator+(const Time &anotherTime) const {
	return Time((hours + anotherTime.hours) + ((minutes + anotherTime.minutes) >= 60), (minutes + anotherTime.minutes) % 60);
}

Train::Record::Time Train::Record::Time::operator-(const Time &anotherTime) const {
	unsigned int a = minutes + pow(61, minutes < anotherTime.minutes) - 1 - anotherTime.minutes;
	unsigned int b = (hours - anotherTime.hours) - (minutes < anotherTime.minutes);
	return Time((hours - anotherTime.hours) - (minutes < anotherTime.minutes),
				 minutes + pow(61, minutes < anotherTime.minutes) - 1 - anotherTime.minutes);
}

void Train::Record::Time::operator=(const Time &anotherTime) {
	hours = anotherTime.hours;
	minutes = anotherTime.minutes;
}

bool Train::Record::Time::operator==(const Time &anotherTime) const {
	return hours == anotherTime.hours && minutes == anotherTime.minutes;
}

bool Train::Record::Time::operator!=(const Time &anotherTime) const {
	return !(*this == anotherTime);
}

bool Train::Record::Time::operator>(const Time &anotherTime) const {
	return hours > anotherTime.hours || (hours == anotherTime.hours && minutes > anotherTime.minutes);
}

bool Train::Record::Time::operator<(const Time &anotherTime) const {
	return anotherTime > *this;
}

bool Train::Record::Time::operator>=(const Time &anotherTime) const {
	return *this > anotherTime || *this == anotherTime;
}

bool Train::Record::Time::operator<=(const Time &anotherTime) const {
	return anotherTime >= *this;
}

bool Train::Record::operator==(const Record &anotherRecord) const {
	return this->arrival == anotherRecord.arrival;
}

bool Train::Record::operator!=(const Record &anotherRecord) const {
	return !(*this == anotherRecord);
}

bool Train::Record::operator>(const Record &anotherRecord) const {
	return this->arrival > anotherRecord.arrival;
}

bool Train::Record::operator<(const Record &anotherRecord) const {
	return anotherRecord.arrival > this->arrival;
}

bool Train::Record::operator>=(const Record &anotherRecord) const {
	return *this > anotherRecord || *this == anotherRecord;
}

bool Train::Record::operator<=(const Record &anotherRecord) const {
	return anotherRecord >= *this;
}

bool Train::Route::operator==(const Route &anotherRoute) const {
	return departureFromStart == anotherRoute.departureFromStart;
}

bool Train::Route::operator!=(const Route &anotherRoute) const {
	return !(*this == anotherRoute);
}

bool Train::Route::operator>(const Route &anotherRoute) const {
	return departureFromStart > anotherRoute.departureFromStart;
}

bool Train::Route::operator<(const Route &anotherRoute) const {
	return anotherRoute > *this;
}

bool Train::Route::operator>=(const Route &anotherRoute) const {
	return *this > anotherRoute || *this == anotherRoute;
}

bool Train::Route::operator<=(const Route &anotherRoute) const {
	return anotherRoute >= *this;
}

ostream& operator<<(ostream &ostream, const Train::Record::Time time)
{
	return ostream << setw(2) << setfill((char)ZERO) << time.hours << text.separators[1] << setw(2) << setfill((char)ZERO) << time.minutes << setfill((char)SPACE);
}

void operator<<(string &line, const Train::Record::Time time) {
	if (time.hours > 9)
		line += to_string(time.hours);
	else
		line += text.zero + to_string(time.hours);
	line += text.separators[1];
	if (time.minutes > 9)
		line += to_string(time.minutes);
	else
		line += text.zero + to_string(time.minutes);
}

ostream& operator<<(ostream &ostream, const Train::Record record)
{
	return ostream << setw(35) << allStations[record.station] << text.whiteSpaces[5] << right << record.arrival << text.separators[2] << record.departure;
}

ostream& operator<<(ostream &ostream, const Train train)
{
	for (unsigned int i = 0; i < train.timetable.getSize(); i++)
		ostream << train.timetable[i] << text.whiteSpaces[3];
	return ostream;
}

bool Train::operator==(const Train &anotherTrain) const {
	return trainNumber == anotherTrain.trainNumber;
}

bool Train::operator>(const Train &anotherTrain) const {
	return false;
}