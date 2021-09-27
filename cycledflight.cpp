#include "cycledflight.h"
#include <stdexcept>

CycledFlight::CycledFlight()
{
}

vector<Flight>* CycledFlight::getFlights() {
    return &this->flights;
}

void CycledFlight::addFlight(Flight newFlight, int place) {
    if (place < static_cast<int>(this->flights.size()))
        checkNewFlight(newFlight, this->flights.at(place), this->flights.at(place + 1));
    else if (place == static_cast<int>(this->flights.size()))
        checkNewFlight(newFlight, this->flights.at(place - 1), this->flights.at(0));
    else throw runtime_error("Flight index is incorrect");

    this->flights.insert(this->flights.begin() + place, newFlight);
}

void CycledFlight::checkNewFlight(Flight newFlight, Flight previousFlight, Flight nextFlight) {
    if (newFlight.getStartPoint() != previousFlight.getEndPoint())
        throw runtime_error("New flight start point is incorrect");
    if (newFlight.getEndPoint() != nextFlight.getStartPoint())
        throw runtime_error("New flight endpoint is incorrect");
    if (newFlight.getAirplaneId() != previousFlight.getAirplaneId())
        throw runtime_error("New flight airplane id is incorrect");
    if (newFlight.getStartTime() < previousFlight.getEndTime())
        throw runtime_error("New flight start time is incorrect");
    if (newFlight.getEndTime() > previousFlight.getStartTime())
        throw runtime_error("New flight end time is incorrect");
}
