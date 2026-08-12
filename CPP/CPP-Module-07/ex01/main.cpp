#include <iostream>
#include "iter.hpp"

template <typename T>
void print(const T &x)
{
    std::cout << x << " ";
}

void increment(int &x)
{
    x++;
}

int main()
{
    int numbers[] = {1, 2, 3, 4, 5};

    std::cout << "Before increment: ";
    iter(numbers, 5, print<int>);
    std::cout << std::endl;

    iter(numbers, 5, increment);

    std::cout << "After increment: ";
    iter(numbers, 5, print<int>);
    std::cout << std::endl;

    std::string words[] = {"Hello", "World"};

    std::cout << "Strings: ";
    iter(words, 2, print<std::string>);
    std::cout << std::endl;

    return 0;
}
