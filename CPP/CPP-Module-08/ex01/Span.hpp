#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>

class Span
{
	private:
		unsigned int		N;
		std::vector<int>	vector;

	public:
		Span();
		Span(unsigned int N);
		Span(const Span &obj);
		Span &operator=(const Span &obj);
		~Span();

		void	addNumber(int number);
		void	addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);

		int		shortestSpan();
		int		longestSpan();

		class ContainerIsFull : public std::exception
		{
			public:
				const char *what() const throw();
		};

		class NoEnoughNumbers : public std::exception
		{
			public:
				const char *what() const throw();
		};
};

#endif
