#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template <typename T>
class Array
{
    private:
        T *_arr;
        unsigned int _size;

    public:
        Array();
        Array(unsigned int n);
        Array(const Array &obj);
        Array &operator=(const Array &obj);
        ~Array();

        T &operator[](unsigned int index);
	const T &operator[](unsigned int index) const;

        unsigned int size() const;

        class OutOfBoundsException : public std::exception
        {
            public:
                const char *what() const throw();
        };
};

#include "Array.tpp"

#endif
