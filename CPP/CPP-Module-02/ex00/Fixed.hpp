/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:27:13 by asebban           #+#    #+#             */
/*   Updated: 2025/11/11 16:14:32 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
    private:
        int                 raw;
        static const int    bites;
    public:
        Fixed();
        Fixed(const Fixed &obj);
        ~Fixed();
        Fixed&  operator=(const Fixed &obj);
        int     getRawBits(void) const;
        void    setRawBits(int const raw);
};

#endif