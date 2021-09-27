#pragma once
#ifndef AIRCRAFTLIB_H
#define AIRCRAFTLIB_H

#include "waypoint.h"
#include "flight.h"
#include "timetable.h"
#include <iostream>

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

class AircraftLib
{
private:
    vector<Waypoint> waypoints;
    Timetable timetable;
    Waypoint findWaypointByName(string name);


public:
    AircraftLib();

    vector<FlightStruct> getTimetable(); // Возвращает все расписание

    vector<FlightStruct> getTimeTableForPlane(int planeId); // Возращает расписание для конкретного самолета

    long long int getPlaneAirTime(int planeId); // Возвращает суммарное время в воздухе для самолета

    vector<FlightStruct> getFastestRoute(string startPoint,
        string endPoint,
        long long int startTime); // Возвращает самы быстрый марушрут между двумя пунктами для заданного времени отлета

    void addFlight(int airplaneId,
        string startPoint,
        string endPoint,
        int startWeekDay,
        int endWeekDay,
        long long int startTime,
        long long int endTime); // Добавляет рейс в расписние

    void addWaypoint(string name, vector<pair<string, pair<int, int>>> connectedWaypoints); //Добавляет пункт назначения

    // Тесты
    static void testAddWayopoint() {
        AircraftLib lib = AircraftLib();
        Waypoint a = Waypoint();
        a.setName("a");
        Waypoint b = Waypoint();
        b.setName("b");
        a.setConnectedWaypoints({ make_pair(&b, make_pair(1,2)) });
        b.setConnectedWaypoints({ make_pair(&a, make_pair(1,2)) });
        lib.addWaypoint("a", {});
        lib.addWaypoint("b", { make_pair("a", make_pair(1,2)) });
        vector<Waypoint> tmp = { a,b };
        IS_TRUE(tmp.at(0) == a && tmp.at(1) == b);
    }

    static void testTimtableForPLane() {
        AircraftLib lib = AircraftLib();
        lib.addWaypoint("a", {});
        lib.addWaypoint("b", { make_pair("a", make_pair(1,2)) });
        lib.addFlight(1, "a", "b", 1, 1, 100, 103);
        lib.addFlight(2, "a", "b", 1, 1, 100, 103);
        Flight a = Flight(1, lib.waypoints.at(0), lib.waypoints.at(1), 1, 1, 100, 103);
        vector<FlightStruct> aStruct = { a.toStruct() };
        IS_TRUE(lib.getTimeTableForPlane(1) == aStruct);
    }

    static void testGetPlaneAirTime() {
        AircraftLib lib = AircraftLib();
        lib.addWaypoint("a", {});
        lib.addWaypoint("b", { make_pair("a", make_pair(1,2)) });
        lib.addFlight(1, "a", "b", 1, 1, 100, 103);
        lib.addFlight(2, "a", "b", 1, 1, 100, 103);
        IS_TRUE(lib.getPlaneAirTime(1) == 103 - 100);
    }
};

#endif // AIRCRAFTLIB_H

