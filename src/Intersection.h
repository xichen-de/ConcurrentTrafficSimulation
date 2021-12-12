// MIT License
//
// Copyright (c) 2021 Xi Chen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <future>
#include <mutex>
#include <memory>
#include "TrafficObject.h"
#include "TrafficLight.h"

// forward declarations to avoid include cycle
class Street;

class Vehicle;

// auxiliary class to queue and dequeue waiting vehicles in a thread-safe manner
class WaitingVehicles {
public:
    // getters / setters
    int getSize();

    // typical behaviour methods
    void pushBack(std::shared_ptr<Vehicle> vehicle, std::promise<void> &&promise);

    void permitEntryToFirstInQueue();

private:
    std::vector<std::shared_ptr<Vehicle>> _vehicles;          // list of all vehicles waiting to enter this intersection
    std::vector<std::promise<void>> _promises; // list of associated promises
    std::mutex _mutex;
};

class Intersection : public TrafficObject {
public:
    // constructor / desctructor
    Intersection();

    // getters / setters
    void setIsBlocked(bool isBlocked);

    // typical behaviour methods
    void addVehicleToQueue(std::shared_ptr<Vehicle> vehicle);

    void addStreet(std::shared_ptr<Street> street);

    std::vector<std::shared_ptr<Street>>
    queryStreets(std::shared_ptr<Street> incoming); // return pointer to current list of all outgoing streets
    void simulate();

    void vehicleHasLeft(std::shared_ptr<Vehicle> vehicle);

    bool trafficLightIsGreen();

private:

    // typical behaviour methods
    void processVehicleQueue();

    // private members
    std::vector<std::shared_ptr<Street>> _streets;   // list of all streets connected to this intersection
    WaitingVehicles _waitingVehicles; // list of all vehicles and their associated promises waiting to enter the intersection
    bool _isBlocked;                  // flag indicating wether the intersection is blocked by a vehicle
    TrafficLight _trafficLight;       // traffic light controlling the intersection
};

#endif
