/*
    C++ Primer: Exercise 1.13 "Sum of 50 to 100 with for-loop"
    sumfor.cpp
*/
#include <iostream>

int main() {
    int max = 100;
    int sum = 0;
    for(int i = 50; i <= max; ++i) { // inclusive <=
        sum += i;
    }
    std::cout << "Sum of 50 to 100 is " << sum << std::endl;
    return 0;
}
