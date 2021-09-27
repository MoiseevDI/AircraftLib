#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include "waypoint.h"

using namespace std;

struct FlightStruct {
    string startPoint = "", endPoint = "";
    int startWeekDay = 0, endWeekDay = 0;
    int airplaneId = 0;
    long long int startTime = 0, endTime = 0;

    bool operator==(const FlightStruct& a) const
    {
        return (startPoint == a.startPoint
            && endPoint == a.endPoint
            && startWeekDay == a.startWeekDay
            && endWeekDay == a.endWeekDay
            && airplaneId == a.airplaneId
            && startTime == a.startTime
            && endTime == a.endTime);
    }
};

class Flight
{
private:
    Waypoint startPoint, endPoint;
    int startWeekDay, endWeekDay;
    int airplaneId;
    long long int startTime, endTime;

public:
    Flight();
    Flight(int airplaneId,
        Waypoint startPoint,
        Waypoint endPoint,
        int startWeekDay,
        int endWeekDay,
        long long int startTime,
        long long int endTime);

    Waypoint getStartPoint();
    void setStartPoint(Waypoint newStartPoint);

    Waypoint getEndPoint();
    void setEndPoint(Waypoint newEndPoint);

    int getStartWeekDay();
    void setStartWeekDay(int newStartWeekDay);

    int getEndWeekday();
    void setEndWeekDay(int newEndWeekDay);

    int getAirplaneId();
    void setAirplaneId(int newAirplaneId);

    long long int getStartTime();
    void setStartTime(long long int newStartTime);

    long long int getEndTime();
    void setEndTime(long long int newEndTime);

    const FlightStruct toStruct();

    bool operator < (const Flight& a);

    bool operator == (const Flight& a);
};

#endif // FLIGHT_H
