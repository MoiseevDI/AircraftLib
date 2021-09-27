#include "aircraftlib.h"
#include <algorithm>
#include "pybind11/pybind11.h"
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <memory>
#include <complex>
#include <array>

namespace py = pybind11;

AircraftLib::AircraftLib()
{
}

vector<FlightStruct> AircraftLib::getTimetable()
{
    list<FlightStruct> timetableExp = list<FlightStruct>();
    for_each(this->timetable.begin(), this->timetable.end(), [&timetableExp](Flight t) {
        timetableExp.push_back(t.toStruct());
        });
    vector<FlightStruct> tmp(timetableExp.size());
    copy(timetableExp.begin(), timetableExp.end(), tmp.begin());
    return tmp;
}

vector<FlightStruct> AircraftLib::getTimeTableForPlane(int planeId)
{
    list<FlightStruct> timetableExp = list<FlightStruct>();
    for_each(this->timetable.begin(), this->timetable.end(), [&timetableExp, planeId](Flight t) {
        if (t.getAirplaneId() == planeId)
            timetableExp.push_back(t.toStruct());
        });
    vector<FlightStruct> tmp(timetableExp.size());
    copy(timetableExp.begin(), timetableExp.end(), tmp.begin());
    return tmp;
}

long long int AircraftLib::getPlaneAirTime(int planeId)
{
    long long int airTime = 0;
    for_each(this->timetable.begin(), this->timetable.end(), [&airTime, planeId](Flight t) {
        if (t.getAirplaneId() == planeId)
            airTime += (t.getEndTime() - t.getStartTime());
        });
    return airTime;
}

vector<FlightStruct> AircraftLib::getFastestRoute(string startPoint,
    string endPoint,
    long long int startTime)
{
    if (startPoint == endPoint) throw runtime_error("Пункты назначения и отбытия заданы неправильно");
    Waypoint startWaypoint = findWaypointByName(startPoint),
        endWaypoint = findWaypointByName(endPoint);
    if (startWaypoint == endWaypoint) throw runtime_error("Пункты назначения и отбытия найдены неправильно");

    bool shortestRouteFound = false;
    vector<FlightStruct> shortestRoute = {};
    list<Flight>::iterator iter = this->timetable.begin();
    while (!shortestRouteFound) {
        Waypoint currentPoint = Waypoint();
        while (iter->getEndPoint() != endWaypoint && startTime <= iter->getStartTime()) {
            if (iter == this->timetable.end()) {
                if (shortestRoute.size() == 0)
                    throw runtime_error("Не существует рейсов в пункт назначения");
                else shortestRoute.pop_back();
            }
            ++iter;
        }

        if (shortestRoute.size() != 0 && shortestRoute.end()->startTime >= iter->getEndTime())
            shortestRoute.push_back((*iter).toStruct());
        if (shortestRoute.size() == 0) shortestRoute.push_back((*iter).toStruct());
        if (iter->getStartPoint() == startWaypoint)
            shortestRouteFound = true;
        else {
            endWaypoint = iter->getStartPoint();
        }
        iter = this->timetable.begin();
        if (shortestRoute.end()->startPoint == shortestRoute.end()->endPoint)
            throw runtime_error("Найденный рейс некорректен. Совпадают пункты отправления и прибытия");
    }
    return shortestRoute;
}

void AircraftLib::addFlight(int airplaneId,
    string startPoint,
    string endPoint,
    int startWeekDay,
    int endWeekDay,
    long long startTime,
    long long endTime)
{
    Waypoint startWaypoint = findWaypointByName(startPoint),
        endWaypoint = findWaypointByName(endPoint);

    this->timetable.addFlight(Flight(airplaneId,
        startWaypoint,
        endWaypoint,
        startWeekDay,
        endWeekDay,
        startTime,
        endTime));

}

void AircraftLib::addWaypoint(string name, vector<pair<string, pair<int, int> > > connectedWaypoints)
{
    Waypoint waypoint = Waypoint();
    waypoint.setName(name);
    vector<pair<Waypoint, pair<int, int> > > tmp = vector<pair<Waypoint, pair<int, int> > >();
    if (this->waypoints.size() != 0 && connectedWaypoints.size() == 0)
        throw runtime_error("Необходимо указать связанные пункты");
    for_each(connectedWaypoints.begin(), connectedWaypoints.end(), [&tmp, this](pair<string, pair<int, int> > t) {
        tmp.push_back(make_pair(findWaypointByName(t.first), t.second));
        });
    waypoints.push_back(waypoint);
}


Waypoint AircraftLib::findWaypointByName(string name) {
    Waypoint waypoint = Waypoint();
    bool waypointFound = false;
    for_each(this->waypoints.begin(),
        this->waypoints.end(),
        [name, &waypoint, &waypointFound](Waypoint t) {
            if (t.getName() == name) {
                waypoint = t;
                waypointFound = true;
            }
        });
    if (!waypointFound) throw runtime_error("Waypoint with such name was not created");
    return waypoint;
}


PYBIND11_MODULE(Aircraft, m) {
    m.doc() = "airplaneLibls"; // optional module docstring
    py::class_<AircraftLib>(m, "AircraftLibInitClass")
        .def(py::init())
        .def("getTimetable", &AircraftLib::getTimetable)
        .def("getTimeTableForPlane", &AircraftLib::getTimeTableForPlane)
        .def("getPlaneAirTime", &AircraftLib::getPlaneAirTime)
        .def("addFlight", &AircraftLib::addFlight)
        .def("getFastestRoute", &AircraftLib::getFastestRoute)
        .def("addDestination", &AircraftLib::addWaypoint);
    py::class_<FlightStruct>(m, "FlightStruct")
        .def(py::init())
        .def_readwrite("startPoint", &FlightStruct::startPoint)
        .def_readwrite("endPoint", &FlightStruct::endPoint)
        .def_readwrite("startWeekDay", &FlightStruct::startWeekDay)
        .def_readwrite("endWeekDay", &FlightStruct::endWeekDay)
        .def_readwrite("airplaneId", &FlightStruct::airplaneId)
        .def_readwrite("startTime", &FlightStruct::startTime)
        .def_readwrite("endTime", &FlightStruct::endTime);
    py::class_<Flight>(m, "Flight")
        .def(py::init())
        .def("getStartPoint", &Flight::getStartPoint)
        .def("getEndPoint", &Flight::getStartPoint)
        .def("getStartTime", &Flight::getStartTime);
    py::class_<Waypoint>(m, "Waypoint")
        .def(py::init())
        .def("getName", &Waypoint::getName);

}
