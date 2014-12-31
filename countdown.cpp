/*
    C++ Primer: Exercise 1.10 "Count down 10 to 0"
    countdown.cpp
*/
#include <iostream>

int main() {
    int max = 0;
    int i = 10;
    while(i >= max) { // inclusive >=
        std::cout <<  i << std::endl;
        --i;
    }
    return 0;
}
