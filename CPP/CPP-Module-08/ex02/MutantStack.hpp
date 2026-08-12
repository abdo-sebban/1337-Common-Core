#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
	public:
		typedef typename std::stack<T, Container>::container_type::iterator				iterator;
		typedef typename std::stack<T, Container>::container_type::const_iterator		const_iterator;

		MutantStack() : std::stack<T, Container>() {}
		MutantStack(const MutantStack &obj) : std::stack<T, Container>(obj) {}
		MutantStack &operator=(const MutantStack &obj)
		{
			if (this != &obj)
				std::stack<T, Container>::operator=(obj);
			return (*this);
		}
		~MutantStack() {}

		iterator begin()
		{
			return (this->c.begin());
		}

		iterator end()
		{
			return (this->c.end());
		}

		const_iterator begin() const
		{
			return (this->c.begin());
		}

		const_iterator end() const
		{
			return (this->c.end());
		}
};

#endif
