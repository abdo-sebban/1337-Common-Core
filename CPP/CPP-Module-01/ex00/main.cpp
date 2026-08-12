/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:26:40 by asebban           #+#    #+#             */
/*   Updated: 2025/10/07 10:52:01 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    Zombie *new_Zombie = newZombie("ZOMBIE1");
    new_Zombie->announce();
    delete new_Zombie;

    randomChump("ZOMBIE2");
    return 0;
}