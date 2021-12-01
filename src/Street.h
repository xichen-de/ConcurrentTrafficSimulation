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

#ifndef STREET_H
#define STREET_H

#include "TrafficObject.h"

// forward declaration to avoid include cycle
class Intersection;

class Street : public TrafficObject, public std::enable_shared_from_this<Street>
{
public:
    // constructor / desctructor
    Street();

    // getters / setters
    double getLength() { return _length; }
    void setInIntersection(std::shared_ptr<Intersection> in);
    void setOutIntersection(std::shared_ptr<Intersection> out);
    std::shared_ptr<Intersection> getOutIntersection() { return _interOut; }
    std::shared_ptr<Intersection> getInIntersection() { return _interIn; }

    // typical behaviour methods

    // miscellaneous
    std::shared_ptr<Street> get_shared_this() { return shared_from_this(); }

private:
    double _length;                                    // length of this street in m
    std::shared_ptr<Intersection> _interIn, _interOut; // intersections from which a vehicle can enter (one-way streets is always from 'in' to 'out')
};

#endif