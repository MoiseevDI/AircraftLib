#ifndef TIMETABLE_H
#define TIMETABLE_H


#include <list>
#include "flight.h"
#include "waypoint.h"
#include <iterator>

using namespace std;

class Timetable
{
private:
    list<Flight> flights;

public:
    Timetable();

    list<Flight>::iterator begin() { return flights.begin(); }
    list<Flight>::iterator end() { return flights.end(); }

    void addFlight(Flight newFlight);
};

#endif // TIMETABLE_H
