/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:58:42 by asebban           #+#    #+#             */
/*   Updated: 2025/11/15 09:53:36 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main()
{
    ScavTrap obj("beta");
    obj.attack("meta");
    obj.takeDamage(8);
    obj.beRepaired(8);
    obj.guardGate();

    return (0);
}