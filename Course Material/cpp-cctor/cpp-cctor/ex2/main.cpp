/**
 * C++ program copying a Cube class.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "../Cube.h"
#include <iostream>

using uiuc::Cube;

Cube foo() {
    Cube c;
    return c;
}

int main() {
    Cube c2 = foo();
    std::cout << c2.getVolume() << std::endl;
    std::cout << c2.getSurfaceArea() << std::endl;
    return 0;
}
