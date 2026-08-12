#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array() : _arr(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _arr(new T[n]), _size(n)
{
}

template <typename T>
Array<T>::Array(const Array &obj)
{
    _size = obj._size;
    _arr = new T[_size];

    for (unsigned int i = 0; i < _size; i++)
        _arr[i] = obj._arr[i];
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &obj)
{
    if (this != &obj)
    {
        delete[] _arr;

        _size = obj._size;
        _arr = new T[_size];

        for (unsigned int i = 0; i < _size; i++)
            _arr[i] = obj._arr[i];
    }
    return (*this);
}

template <typename T>
Array<T>::~Array()
{
    delete[] _arr;
}

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
    if (index >= _size)
        throw OutOfBoundsException();

    return (_arr[index]);
}

template <typename T>
const T &Array<T>::operator[](unsigned int index) const
{
    if (index >= _size)
        throw OutOfBoundsException();

    return (_arr[index]);
}

template <typename T>
unsigned int Array<T>::size() const
{
    return (_size);
}

template <typename T>
const char *Array<T>::OutOfBoundsException::what() const throw()
{
	return ("Index out of bounds");
}

#endif
