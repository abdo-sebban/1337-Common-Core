/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:58:42 by asebban           #+#    #+#             */
/*   Updated: 2025/11/14 12:10:10 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main()
{
    FragTrap obj("beta");
    obj.attack("meta");
    obj.takeDamage(8);
    obj.beRepaired(8);
    obj.highFivesGuys();

    
    return (0);
}