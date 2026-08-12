#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <sys/time.h>

class PmergeMe
{
    private:
        std::vector<int>        original;
        std::vector<size_t>     fordJohnsonVector(const std::vector<int> &data, std::vector<size_t> indices) const;
        size_t                  lowerBoundVector(const std::vector<size_t> &chain, const std::vector<int> &data, size_t begin, size_t end, int value) const;
        std::deque<size_t>      fordJohnsonDeque(const std::deque<int> &data, std::deque<size_t> indices) const;
        size_t                  lowerBoundDeque(const std::deque<size_t> &chain, const std::deque<int> &data, size_t begin, size_t end, int value) const;
        std::vector<size_t>     jacobsthalOrder(size_t pairCount) const;
        void                    parseArguments(int argc, char **argv);
        void                    printSequence(const std::string &label, const std::vector<int> &seq) const;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe            &operator=(const PmergeMe &other);
        ~PmergeMe();
        void                run(int argc, char **argv);
        std::vector<int>    sortVector(const std::vector<int> &input) const;
        std::deque<int>     sortDeque(const std::deque<int> &input) const;

        class ParseException : public std::exception
        {
            public:
                const char *what() const throw();
        };
};

#endif