/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:58:42 by asebban           #+#    #+#             */
/*   Updated: 2025/11/14 11:06:16 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap obj("beta");
    obj.attack("meta");
    obj.takeDamage(8);
    obj.beRepaired(8);
    return (0);
}