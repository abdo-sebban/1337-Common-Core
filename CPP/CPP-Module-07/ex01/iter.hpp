#ifndef ITER_HPP
#define ITER_HPP

template <typename T, typename T_func>
void iter(T *array, const size_t len, T_func f)
{
    for(size_t i = 0; i < len ; i++)
        f(array[i]);
}

#endif
