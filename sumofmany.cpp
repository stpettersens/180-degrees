/*
    C++ Primer: Exercise 1.16 "Sum of many cin integers"
    sumofmany.cpp
*/
#include <iostream>

int main() {
    int sum = 0, value = 0;
    std::cout << "Enter integers (then <Enter> + EOF):" << std::endl;
    while(std::cin >> value) {
        sum += value;
    }
    std::cout << "Sum of is: " << sum << std::endl;
    return 0;
}
