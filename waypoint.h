#ifndef WAYPOINT_H
#define WAYPOINT_H


#include <string>
#include <vector>


using namespace std;

class Waypoint
{
private:
    string name = "";
    vector<pair<Waypoint*, pair<int, int>>> connectedWaypoints = vector<pair<Waypoint*, pair<int, int>>>();

public:
    Waypoint();
    string getName();
    void setName(string newName);
    vector<pair<Waypoint*, pair<int, int>>> getConnectedWaypoints();
    void setConnectedWaypoints(vector<pair<Waypoint*, pair<int, int>>> newConnectedWaypoints);
    bool operator!=(const Waypoint& a) const;
    bool operator==(const Waypoint& a) const;
};

#endif // WAYPOINT_H