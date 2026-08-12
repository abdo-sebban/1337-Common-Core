/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:17:21 by asebban           #+#    #+#             */
/*   Updated: 2025/11/11 16:22:16 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
    private:
        int                 raw;
        static const int    bites;
    public:
        Fixed();
        Fixed(const int number);
        Fixed(const float number);
        Fixed(const Fixed &obj);
        ~Fixed();
        Fixed&  operator=(const Fixed &obj);
        int     getRawBits(void) const;
        void    setRawBits(int const raw);
        float   toFloat( void ) const;
        int     toInt( void ) const;
        bool    operator>(const Fixed& obj)    const;
        bool    operator<(const Fixed& obj)    const;
        bool    operator>=(const Fixed& obj)   const;
        bool    operator<=(const Fixed& obj)   const;
        bool    operator==(const Fixed& obj)   const;
        bool    operator!=(const Fixed& obj)   const;
        Fixed   operator+(const Fixed& obj)   const;
        Fixed   operator-(const Fixed& obj)   const;
        Fixed   operator*(const Fixed& obj)   const;
        Fixed   operator/(const Fixed& obj)   const;
        Fixed   operator++();
        Fixed   operator++(int);
        Fixed   operator--();
        Fixed   operator--(int);
        static Fixed& min(Fixed& a, Fixed& b);
        static const Fixed& min(const Fixed& a, const Fixed& b);
        static Fixed& max(Fixed& a, Fixed& b);
        static const Fixed& max(const Fixed& a, const Fixed& b);

};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif