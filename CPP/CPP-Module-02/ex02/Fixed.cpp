/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:17:19 by asebban           #+#    #+#             */
/*   Updated: 2025/11/11 16:26:05 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int   Fixed::bites = 8;

Fixed::Fixed()
{
    std::cout << "Default constructor called" << std::endl;
    this->raw = 0;
}

Fixed::Fixed(const Fixed &obj)
{
    std::cout << "Copy constructor called" << std::endl;
    this->raw = obj.getRawBits();
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed&  Fixed::operator=(const Fixed &obj)
{
    std::cout << "Copy assignment operator called" << std::endl;
    this->raw = obj.getRawBits();
    return *this;
}

int Fixed::getRawBits() const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->raw;
}

void Fixed::setRawBits(int const raw)
{
    this->raw = raw;
    std::cout << "setRawBits member function called" << std::endl;
}

Fixed::Fixed(const int number)
{
    std::cout << "Int constructor called" << std::endl;
    raw = number << bites;
}

Fixed::Fixed(const float number)
{
    std::cout << "Float constructor called" << std::endl;
    this->raw = roundf(number * (1 << bites));
}

std::ostream& operator<<(std::ostream& os, const Fixed& obj)
{
    os << obj.toFloat();
    return os;
}

float Fixed::toFloat( void ) const
{
    return ((float)this->raw / (1 << bites));
}

int Fixed::toInt( void ) const
{
    return (this->raw >> bites);
}

bool Fixed::operator>(const Fixed& obj) const
{
    return this->raw > obj.raw;
}

bool Fixed::operator<(const Fixed& obj) const
{
    return this->raw < obj.raw;
}

bool Fixed::operator>=(const Fixed& obj) const
{
    return this->raw >= obj.raw;
}

bool Fixed::operator<=(const Fixed& obj) const
{
    return this->raw <= obj.raw;
}

bool Fixed::operator==(const Fixed& obj) const
{
    return this->raw == obj.raw;
}

bool Fixed::operator!=(const Fixed& obj) const
{
    return this->raw != obj.raw;
}

Fixed Fixed::operator+(const Fixed& obj) const
{
    Fixed result;
    result.setRawBits(this->raw + obj.raw);
    return result;
}

Fixed Fixed::operator-(const Fixed& obj) const
{
    Fixed result;
    result.setRawBits(this->raw - obj.raw);
    return result;
}

Fixed Fixed::operator*(const Fixed& obj) const
{
    float product = this->toFloat() * obj.toFloat();
    return Fixed(product);
}

 
Fixed Fixed::operator/(const Fixed& obj) const
{
    float quotient = this->toFloat() / obj.toFloat();
    return Fixed(quotient);
}


Fixed Fixed::operator++()
{
    this->raw++;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed temp = *this;
    this->raw++;
    return temp;
}

Fixed Fixed::operator--()
{
    this->raw--;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed temp = *this;
    this->raw--;
    return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    return (a > b) ? a : b;
}
