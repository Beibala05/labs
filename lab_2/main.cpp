#include "double_numbers.h"

#include <iostream>

int main()
{
    DoubleNumbers d({6, 3, 2});

    std::cout << d << std::endl;

    std::cout << "derivative: " << d.derivative().integral() << std::endl;


    return 0;
}