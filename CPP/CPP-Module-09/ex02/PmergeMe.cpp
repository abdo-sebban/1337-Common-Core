#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : original(other.original) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
        original = other.original;
    return *this;
}

PmergeMe::~PmergeMe() {}

const char *PmergeMe::ParseException::what() const throw()
{
    return "Error";
}

std::vector<size_t> PmergeMe::jacobsthalOrder(size_t pairCount) const
{
    std::vector<size_t> order;
    if (pairCount <= 1)
        return order;

    std::vector<size_t> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal.back() < pairCount)
        jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2]);

    size_t inserted = 1;
    for (size_t g = 2; g < jacobsthal.size(); ++g)
    {
        size_t lo = jacobsthal[g - 1];
        size_t hi = jacobsthal[g];
        if (hi > pairCount)
            hi = pairCount;
        for (size_t bIdx = hi; bIdx > lo; --bIdx)
        {
            order.push_back(bIdx - 1);
            ++inserted;
        }
        if (inserted >= pairCount)
            break;
    }
    return order;
}

size_t PmergeMe::lowerBoundVector(const std::vector<size_t> &chain, const std::vector<int> &data, size_t begin, size_t end, int value) const
{
    size_t lo = begin;
    size_t hi = end;
    while (lo < hi)
    {
        size_t mid = lo + (hi - lo) / 2;
        if (data[chain[mid]] < value)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

std::vector<size_t> PmergeMe::fordJohnsonVector(const std::vector<int> &data, std::vector<size_t> indices) const
{
    if (indices.size() <= 1)
        return indices;

    bool    hasStraggler = (indices.size() % 2 != 0);
    size_t  stragglerIdx = 0;
    if (hasStraggler)
    {
        stragglerIdx = indices.back();
        indices.pop_back();
    }
    std::vector<std::pair<size_t, size_t> > pairs;
    pairs.reserve(indices.size() / 2);
    for (size_t i = 0; i < indices.size(); i += 2)
    {
        size_t i1 = indices[i];
        size_t i2 = indices[i + 1];
        if (data[i1] > data[i2])
            pairs.push_back(std::make_pair(i1, i2));
        else
            pairs.push_back(std::make_pair(i2, i1));
    }

    std::vector<size_t> largeIdxs;
    largeIdxs.reserve(pairs.size());
    for (size_t i = 0; i < pairs.size(); ++i)
        largeIdxs.push_back(pairs[i].first);
    std::vector<size_t> pureChain = fordJohnsonVector(data, largeIdxs);

    std::vector<size_t> companion(data.size());
    for (size_t i = 0; i < pairs.size(); ++i)
        companion[pairs[i].first] = pairs[i].second;

    std::vector<size_t> mainChain = pureChain;
    mainChain.insert(mainChain.begin(), companion[pureChain[0]]);

    std::vector<size_t> order = jacobsthalOrder(pureChain.size());
    for (size_t k = 0; k < order.size(); ++k)
    {
        size_t largeIdx = pureChain[order[k]];
        size_t smallIdx = companion[largeIdx];
        size_t posOfA   = lowerBoundVector(mainChain, data, 0, mainChain.size(), data[largeIdx]);
        size_t insertAt = lowerBoundVector(mainChain, data, 0, posOfA, data[smallIdx]);
        mainChain.insert(mainChain.begin() + insertAt, smallIdx);
    }
    if (hasStraggler)
    {
        size_t insertAt = lowerBoundVector(mainChain, data, 0, mainChain.size(), data[stragglerIdx]);
        mainChain.insert(mainChain.begin() + insertAt, stragglerIdx);
    }

    return mainChain;
}

std::vector<int> PmergeMe::sortVector(const std::vector<int> &input) const
{
    std::vector<size_t> indices;
    indices.reserve(input.size());
    for (size_t i = 0; i < input.size(); ++i)
        indices.push_back(i);

    std::vector<size_t> sortedIdx = fordJohnsonVector(input, indices);

    std::vector<int> result;
    result.reserve(input.size());
    for (size_t i = 0; i < sortedIdx.size(); ++i)
        result.push_back(input[sortedIdx[i]]);
    return result;
}

size_t PmergeMe::lowerBoundDeque(const std::deque<size_t> &chain, const std::deque<int> &data, size_t begin, size_t end, int value) const
{
    size_t lo = begin;
    size_t hi = end;
    while (lo < hi)
    {
        size_t mid = lo + (hi - lo) / 2;
        if (data[chain[mid]] < value)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

std::deque<size_t> PmergeMe::fordJohnsonDeque(const std::deque<int> &data,
                                               std::deque<size_t> indices) const
{
    if (indices.size() <= 1)
        return indices;

    bool    hasStraggler = (indices.size() % 2 != 0);
    size_t  stragglerIdx = 0;
    if (hasStraggler)
    {
        stragglerIdx = indices.back();
        indices.pop_back();
    }

    std::deque<std::pair<size_t, size_t> > pairs;
    for (size_t i = 0; i < indices.size(); i += 2)
    {
        size_t i1 = indices[i];
        size_t i2 = indices[i + 1];
        if (data[i1] > data[i2])
            pairs.push_back(std::make_pair(i1, i2));
        else
            pairs.push_back(std::make_pair(i2, i1));
    }

    std::deque<size_t> largeIdxs;
    for (size_t i = 0; i < pairs.size(); ++i)
        largeIdxs.push_back(pairs[i].first);
    std::deque<size_t> pureChain = fordJohnsonDeque(data, largeIdxs);

    std::deque<size_t> companion(data.size());
    for (size_t i = 0; i < pairs.size(); ++i)
        companion[pairs[i].first] = pairs[i].second;

    std::deque<size_t> mainChain = pureChain;
    mainChain.insert(mainChain.begin(), companion[pureChain[0]]);

    std::vector<size_t> order = jacobsthalOrder(pureChain.size());
    for (size_t k = 0; k < order.size(); ++k)
    {
        size_t largeIdx = pureChain[order[k]];
        size_t smallIdx = companion[largeIdx];
        size_t posOfA   = lowerBoundDeque(mainChain, data, 0, mainChain.size(), data[largeIdx]);
        size_t insertAt = lowerBoundDeque(mainChain, data, 0, posOfA, data[smallIdx]);
        mainChain.insert(mainChain.begin() + insertAt, smallIdx);
    }

    if (hasStraggler)
    {
        size_t insertAt = lowerBoundDeque(mainChain, data, 0, mainChain.size(), data[stragglerIdx]);
        mainChain.insert(mainChain.begin() + insertAt, stragglerIdx);
    }

    return mainChain;
}

std::deque<int> PmergeMe::sortDeque(const std::deque<int> &input) const
{
    std::deque<size_t> indices;
    for (size_t i = 0; i < input.size(); ++i)
        indices.push_back(i);

    std::deque<size_t> sortedIdx = fordJohnsonDeque(input, indices);

    std::deque<int> result;
    for (size_t i = 0; i < sortedIdx.size(); ++i)
        result.push_back(input[sortedIdx[i]]);
    return result;
}

void PmergeMe::parseArguments(int argc, char **argv)
{
    std::vector<int>    values;

    for (int i = 1; i < argc; ++i)
    {
        std::istringstream iss(argv[i]);
        std::string token;
        while (iss >> token)
        {
            if (token.empty())
                throw ParseException();
            for (size_t j = 0; j < token.size(); ++j)
            {
                if (!std::isdigit(static_cast<unsigned char>(token[j])))
                    throw ParseException();
            }

            errno = 0;
            char *endptr = NULL;
            long value = std::strtol(token.c_str(), &endptr, 10);
            if (*endptr != '\0' || errno == ERANGE || value < 0 || value > INT_MAX)
                throw ParseException();

            values.push_back(static_cast<int>(value));
        }
    }

    if (values.empty())
        throw ParseException();

    original = values;
}

void PmergeMe::printSequence(const std::string &label, const std::vector<int> &seq) const
{
    std::cout << label;
    size_t limit = seq.size() < 6 ? seq.size() : 5;
    for (size_t i = 0; i < limit; ++i)
        std::cout << " " << seq[i];
    if (seq.size() > limit)
        std::cout << " [...]";
    std::cout << std::endl;
}

void PmergeMe::run(int argc, char **argv)
{
    parseArguments(argc, argv);
    printSequence("Before:", original);

    struct timeval startVector, endVector;
    gettimeofday(&startVector, NULL);
    std::vector<int> vecInput(original.begin(), original.end());
    std::vector<int> sortedVector = sortVector(vecInput);
    gettimeofday(&endVector, NULL);

    struct timeval startDeque, endDeque;
    gettimeofday(&startDeque, NULL);
    std::deque<int> dequeInput(original.begin(), original.end());
    std::deque<int> sortedDeque = sortDeque(dequeInput);
    gettimeofday(&endDeque, NULL);

    printSequence("After:", sortedVector);

    double vectorUs = (endVector.tv_sec - startVector.tv_sec) * 1000000.0 +
                       (endVector.tv_usec - startVector.tv_usec);
    double dequeUs  = (endDeque.tv_sec - startDeque.tv_sec) * 1000000.0 +
                       (endDeque.tv_usec - startDeque.tv_usec);

    std::cout << "Time to process a range of " << original.size()
              << " elements with std::vector<int> : " << vectorUs << " us" << std::endl;
    std::cout << "Time to process a range of " << original.size()
              << " elements with std::deque<int> : " << dequeUs << " us" << std::endl;
}