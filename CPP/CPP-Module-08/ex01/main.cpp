#include "Span.hpp"
#include <iostream>
#include <vector>

int main()
{
	try
	{
		Span sp(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span : " << sp.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Span sp(2);

		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Span sp(5);

		sp.addNumber(42);

		std::cout << sp.shortestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Span sp(10);

		std::vector<int> v;

		v.push_back(100);
		v.push_back(101);
		v.push_back(102);
		v.push_back(103);

		sp.addNumber(v.begin(), v.end());

		std::cout << "Shortest span: "
          			<< sp.shortestSpan()
          			<< std::endl;

		std::cout << "Longest span: "
          			<< sp.longestSpan()
          			<< std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Span sp(10000);

		for (int i = 0; i < 10000; i++)
			sp.addNumber(i);

		std::cout << "Shortest span: "
          		<< sp.shortestSpan()
          		<< std::endl;

		std::cout << "Longest span: "
          		<< sp.longestSpan()
          		<< std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return (0);
}

