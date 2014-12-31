/*
    C++ Primer: Exercise 1.11 "Print between x and y"
    range.cpp
*/
#include <iostream>

int main() {
    int x, y = 0;
    std::cout << "Enter two integers (low, high):" << std::endl;
    std::cin >> x >> y;
    std::cout << std::endl;
    while(x <= y) { // inclusive <=
        std::cout <<  x << std::endl;
        ++x;
    }
    return 0;
}
