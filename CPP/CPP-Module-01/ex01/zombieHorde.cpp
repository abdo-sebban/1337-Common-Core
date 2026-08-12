/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:47:48 by asebban           #+#    #+#             */
/*   Updated: 2025/10/07 12:15:53 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie* zombieHorde( int N, std::string name )
{
    if (N <= 0)
        return (NULL);
    Zombie* horde = new (std::nothrow) Zombie[N];
    if (!horde)
        return (NULL);
    for (int i = 0; i < N; ++i)
    {
        horde[i].setName(name);
    }
    return (horde);
}
