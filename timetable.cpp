#include "timetable.h"

Timetable::Timetable()
{
}

void Timetable::addFlight(Flight newFlight)
{
    bool notFound = true;
    if (this->flights.size() == 0) this->flights.push_back(newFlight);
    else
        for (auto iter = this->flights.begin(); iter != this->flights.end() && notFound; iter++) {
            if (newFlight.getStartTime() < (*iter).getStartTime()) {
                this->flights.insert(iter, newFlight);
                notFound = false;
            }
        }
}
