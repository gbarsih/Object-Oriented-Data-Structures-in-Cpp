/**
 * C++ program invoking Cube's destructor several times.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "Cube.h"
#include <iostream>

using uiuc::Cube;

double cube_on_stack() {
    Cube c(3);
    return c.getVolume();
}

void cube_on_heap() {
    Cube * c1 = new Cube(10);
    Cube * c2 = new Cube;
    delete c1;
}

int main() {
    cube_on_stack();
    cube_on_heap();
    cube_on_stack();
    int *a;
    a = new int(50);
    std::cout << *a << std::endl;
    delete a;
    return 0;
}
