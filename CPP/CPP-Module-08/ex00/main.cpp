#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main()
{
    std::vector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    try
    {
        std::vector<int>::iterator it = easyfind(vec, 30);

        std::cout << "Found in vector: " << *it << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Vector error: " << e.what() << std::endl;
    }

    try
    {
        std::vector<int>::iterator it = easyfind(vec, 99);

        std::cout << "Found in vector: " << *it << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Vector error: " << e.what() << std::endl;
    }

    std::list<int> lst;

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);

    try
    {
        std::list<int>::iterator it = easyfind(lst, 2);

        std::cout << "Found in list: " << *it << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "List error: " << e.what() << std::endl;
    }

    return (0);
}
