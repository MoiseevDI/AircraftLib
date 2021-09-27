#include "waypoint.h"
#include <algorithm>
#include <stdexcept>

Waypoint::Waypoint()
{
}

string Waypoint::getName() {
    return this->name;
}

void Waypoint::setName(string newName) {
    this->name = newName;
}

vector<pair<Waypoint*, pair<int, int>>> Waypoint::getConnectedWaypoints() {
    return this->connectedWaypoints;
}

void Waypoint::setConnectedWaypoints(vector<pair<Waypoint*, pair<int, int>>> newConnectedWaypoints) {
    for_each(newConnectedWaypoints.begin(), newConnectedWaypoints.end(), [this](pair<Waypoint*, pair<int, int>> t) {
        if (t.second.first > t.second.second) throw runtime_error("Connected waypoint travle time is incorrect");
        t.first->connectedWaypoints.push_back(make_pair(this, t.second));
        });
}

bool Waypoint::operator==(const Waypoint& a) const {
    return a.name == this->name;
}

bool Waypoint::operator!=(const Waypoint& a) const {
    return a.name != this->name;
}

