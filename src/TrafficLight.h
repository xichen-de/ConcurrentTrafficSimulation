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

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;


template<class T>
class MessageQueue {
public:
    void send(T &&traffic_light_phase);

    T receive();

private:
    std::deque<T> _queue;
    std::condition_variable _condition_variable;
    std::mutex _mutex;
};



class TrafficLight : public TrafficObject {
public:
    // constructor / destructor
    TrafficLight();

    ~TrafficLight();

    // getter and setter
    int getID() { return _id; }

    void setPosition(double x, double y);

    void getPosition(double &x, double &y);

    ObjectType getType() { return _type; }

    // typical behaviour methods
    void waitForGreen();

    void simulate();

    enum TrafficLightPhase {
        red, green
    };

    TrafficLightPhase getCurrentPhase();

private:
    // typical behaviour methods

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.

    void cycleThroughPhases();

    TrafficLightPhase _currentPhase;
    std::condition_variable _condition;
    std::mutex _mutex;
    std::random_device _rd;     // only used once to initialise (seed) engine
    MessageQueue<TrafficLightPhase> _messageQueue;
};

#endif