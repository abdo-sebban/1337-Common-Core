#include <iostream>
#include <string>
#include "Array.hpp"

int main()
{

    Array<int> a(5);

    for (unsigned int i = 0; i < a.size(); i++)
        a[i] = i * 10;

    for (unsigned int i = 0; i < a.size(); i++)
        std::cout << a[i] << " ";

    std::cout << std::endl;

    Array<int> b(a);

    b[0] = 999;

    std::cout << "a[0] = " << a[0] << std::endl;
    std::cout << "b[0] = " << b[0] << std::endl;

    Array<int> c;
    c = a;

    c[1] = 555;

    std::cout << "a[1] = " << a[1] << std::endl;
    std::cout << "c[1] = " << c[1] << std::endl;

    Array<std::string> words(2);

    words[0] = "Hello";
    words[1] = "World";

    for (unsigned int i = 0; i < words.size(); i++)
        std::cout << words[i] << std::endl;

    try
    {
        std::cout << a[100] << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    const Array<int> const_arr(a);
    std::cout << "const_arr[0] = " << const_arr[0] << std::endl;

    return (0);
}
