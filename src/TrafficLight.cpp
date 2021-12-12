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

#include <iostream>
#include <random>
#include "TrafficLight.h"


template<class T>
void MessageQueue<T>::send(T &&traffic_light_phase) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.clear(); // https://knowledge.udacity.com/questions/586056
    _queue.emplace_back(std::move(traffic_light_phase));
    _condition.notify_one();
}


template<class T>
T MessageQueue<T>::receive() {
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this] { return !_queue.empty(); });
    T message = std::move(_queue.front());
    _queue.pop_front();
    return message;
}

void TrafficLight::cycleThroughPhases() {
    // https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
    std::random_device _rd;
    std::mt19937 rng(_rd());
    std::uniform_int_distribution<int> uni(4000, 6000);
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(uni(rng)));
        _currentPhase = (_currentPhase == TrafficLightPhase::red) ? TrafficLightPhase::green : TrafficLightPhase::red;
        _messageQueue.send(std::move(_currentPhase));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void TrafficLight::simulate() {
    std::thread t(&TrafficLight::cycleThroughPhases, this);
    threads.emplace_back(std::move(t));
}

void TrafficLight::waitForGreen() {
    while (true) {
        if (_messageQueue.receive() == TrafficLightPhase::green) {
            return;
        }
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase() {
    return _currentPhase;
}

TrafficLight::TrafficLight() {
    _currentPhase = TrafficLightPhase::red;
}


