/**
 * C++ class for a "stack" of cubes in a Tower of Hanoi puzzle.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#pragma once

#include <vector>
#include "uiuc/Cube.h"
using uiuc::Cube;

class Stack {
  public:
    void push_back(const Cube & cube);  //puts addressed cube at the top of the stack
    Cube removeTop();   //removes top cube from a stack and returns the cube object
    Cube & peekTop();   //returns address of the cube at the top of the stack
    unsigned size() const;

    // An overloaded operator<<, allowing us to print the stack via `cout<<`:
    friend std::ostream& operator<<(std::ostream & os, const Stack & stack);

  private:
    std::vector<Cube> cubes_;
};
