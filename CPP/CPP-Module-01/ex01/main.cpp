/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:47:35 by asebban           #+#    #+#             */
/*   Updated: 2025/10/07 12:16:17 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    int N = 111;
    Zombie* h = zombieHorde(N, "ZOMBIE");
    if (!h)
        return (0);
    for (int i = 0; i < N; ++i)
        h[i].announce();
    delete [] h;
    return 0;
}
