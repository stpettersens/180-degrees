/*
    C++ Primer: Exercise 1.4 "Product of numbers"
    product.cpp
*/
#include <iostream>

int main() {
    int v1, v2 = 0;
    std::cout << "Enter two integers:" << std::endl;
    std::cin >> v1 >> v2;
    std::cout << "Product of " << v1 << " and " << v2
              << " is " << (v1 * v2) << std::endl;
    return 0;
}
