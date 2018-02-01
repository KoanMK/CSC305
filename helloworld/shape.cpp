#include <iostream>
#include "Shape.h"

using namespace std;

Shape::Shape(int size){
    /// @attention memory allocated here!!!
    data = new float[size];
}

/// @todo Define the destructor here
/// 1) print "~Shape()" to terminal (which destructor is called?)
/// 2) deallocate the memory pointed to by the member "data"
Shape::~Shape(){
    std::cout << "~Shape()" << std::endl;
    delete[] data;
}

/// @todo Define "member_function()" here
void Shape::member_function(){
    std::cout << "Shape::member_function()" << std::endl;
}

/// @todo Define "virtual_member_function()" here
/// The function prints "Shape::virtual_member_function()"
