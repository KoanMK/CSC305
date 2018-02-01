#ifndef SHAPE_H
#define SHAPE_H

#pragma once
#include <iostream>

class Shape
{
public:
protected:
    float* data;
public:
    Shape(int size);
    /// @todo Declare the destructor here
    virtual ~Shape();
    /// @todo Declare "member_function()" here
    void member_function();
};

#endif // SHAPE_H
