#include "Serializer.hpp"
#include <iostream>

int main()
{
    Data data;

    data.id = 42;
    data.name = "asebban";

    Data* original = &data;

    uintptr_t raw = Serializer::serialize(original);

    Data* recovered = Serializer::deserialize(raw);

    std::cout << "Original : " << original << std::endl;
    std::cout << "Recovered: " << recovered << std::endl;

    if (original == recovered)
        std::cout << "Success!" << std::endl;
    else
        std::cout << "Failure!" << std::endl;
}
