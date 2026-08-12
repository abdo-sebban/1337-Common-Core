#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    try
    {
        PmergeMe pmerge;
        pmerge.run(argc, argv);
    }
    catch (const std::exception &e)
    {
        (void)e;
        std::cerr << "Error" << std::endl;
        return (1);
    }
    return (0);
}