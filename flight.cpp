#include "flight.h"
#include <stdexcept>

Flight::Flight()
{
}

Flight::Flight(int newAirplaneId,
    Waypoint newStartPoint,
    Waypoint newEndPoint,
    int newStartWeekDay,
    int newEndWeekDay,
    long long newStartTime,
    long long newEndTime) : Flight()
{
    if (newEndTime - newStartTime <= 0) throw runtime_error("Некорректное время начал или окончания полета");
    if (newStartPoint == newEndPoint) throw runtime_error("Некорректные пункты отправления и назначения");

    this->airplaneId = newAirplaneId;
    this->startPoint = newStartPoint;
    this->endPoint = newEndPoint;
    this->startWeekDay = newStartWeekDay;
    this->endWeekDay = newEndWeekDay;
    this->startTime = newStartTime;
    this->endTime = newEndTime;
}



const FlightStruct Flight::toStruct() {
    FlightStruct flight = FlightStruct();
    flight.airplaneId = this->airplaneId;
    flight.startPoint = this->startPoint.getName();
    flight.endPoint = this->endPoint.getName();
    flight.startTime = this->startTime;
    flight.endTime = this->endTime;
    flight.startWeekDay = this->startWeekDay;
    flight.endWeekDay = this->endWeekDay;
    return flight;
}

int Flight::getAirplaneId() {
    return this->airplaneId;
}

void Flight::setAirplaneId(int newAirplaneId) {
    this->airplaneId = newAirplaneId;
}

Waypoint Flight::getStartPoint() {
    return this->startPoint;
}

void Flight::setStartPoint(Waypoint newStartPoint) {
    this->startPoint = newStartPoint;
}

Waypoint Flight::getEndPoint() {
    return this->endPoint;
}

void Flight::setEndPoint(Waypoint newEndPoint) {
    this->endPoint = newEndPoint;
}

long long int Flight::getStartTime() {
    return this->startTime;
}

void Flight::setStartTime(long long int newStartTime) {
    this->startTime = newStartTime;
}

long long int Flight::getEndTime() {
    return this->endTime;
}

void Flight::setEndTime(long long int newEndTime) {
    this->endTime = newEndTime;
}

int Flight::getStartWeekDay() {
    return this->startWeekDay;
}

void Flight::setStartWeekDay(int newStartWeekDay) {
    this->startWeekDay = newStartWeekDay;
}

int Flight::getEndWeekday() {
    return this->endWeekDay;
}

void Flight::setEndWeekDay(int newEndWeekDay) {
    this->endWeekDay = newEndWeekDay;
}

bool Flight::operator<(const Flight& a) {
    return this->startTime < a.startTime;
}

bool Flight::operator==(const Flight& a) {
    return this->startTime == a.startTime;
}
