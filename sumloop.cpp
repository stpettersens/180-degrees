/*
    C++ Primer: Exercise 1.9 "Sum of 50 to 100"
    sumloop.cpp
*/
#include <iostream>

int main() {
    int i = 50;
    int max = 100;
    int sum = 0;
    while(i <= max) { // inclusive <=
        sum += i;
        ++i;
    }
    std::cout << "Sum of 50 to 100 is " << sum << std::endl;
    return 0;
}
