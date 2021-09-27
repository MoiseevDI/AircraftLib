#pragma once
#ifndef CYCLEDFLIGHT_H
#define CYCLEDFLIGHT_H

#include <vector>
#include "flight.h"

using namespace std;

class CycledFlight
{
private:
    vector<Flight> flights;
    void checkNewFlight(Flight newFlight, Flight previousFlight, Flight nextFlight);

public:
    CycledFlight();

    vector<Flight>* getFlights();

    void addFlight(Flight newFlight, int place); // ��������� ���� � ���������� �����

    void addFlight(Flight newFlight); // ��������� ���� � �����
};

#endif // CYCLEDFLIGHT_H
