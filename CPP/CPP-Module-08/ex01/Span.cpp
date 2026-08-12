#include "Span.hpp"

#include <algorithm>
#include <iterator>

Span::Span() : N(0)
{
}

Span::Span(unsigned int N) : N(N)
{
}

Span::Span(const Span &obj)
{
	*this = obj;
}

Span &Span::operator=(const Span &obj)
{
	if (this != &obj)
	{
		N = obj.N;
		vector = obj.vector;
	}
	return (*this);
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
	if (vector.size() >= N)
		throw ContainerIsFull();

	vector.push_back(number);
}

void Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	if (vector.size() + std::distance(begin, end) > N)
		throw ContainerIsFull();

	vector.insert(vector.end(), begin, end);
}

int Span::shortestSpan()
{
	if (vector.size() <= 1)
		throw NoEnoughNumbers();

	std::vector<int> tmp(vector);

	std::sort(tmp.begin(), tmp.end());

	int minSpan = tmp[1] - tmp[0];

	for (size_t i = 2; i < tmp.size(); i++)
	{
		int currentSpan = tmp[i] - tmp[i - 1];

		if (currentSpan < minSpan)
			minSpan = currentSpan;
	}

	return (minSpan);
}

int Span::longestSpan()
{
	if (vector.size() <= 1)
		throw NoEnoughNumbers();

	int min = *std::min_element(vector.begin(), vector.end());
	int max = *std::max_element(vector.begin(), vector.end());

	return (max - min);
}

const char *Span::ContainerIsFull::what() const throw()
{
	return ("Container is full");
}

const char *Span::NoEnoughNumbers::what() const throw()
{
	return ("Not enough numbers to compute span");
}
