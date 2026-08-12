/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:03:50 by asebban           #+#    #+#             */
/*   Updated: 2025/11/14 12:09:40 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap()
{
    std::cout << "FragTrap Default constructor called!" << std::endl;
    this->Name = "";
    this->Hit_points = 100;
    this->Energy_points = 50;
    this->Attack_damage = 20;
}

FragTrap::FragTrap(const FragTrap &obj) : ClapTrap(obj)
{
    std::cout << "FragTrap Copy constructor called!" << std::endl;
    *this = obj;
}

FragTrap::FragTrap(std::string Name) : ClapTrap(Name)
{
    std::cout << "FragTrap Parameterized constructor called!" << std::endl;
    this->Hit_points = 100;
    this->Energy_points = 50;
    this->Attack_damage = 20;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap Destructor called!" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &obj)
{
    std::cout << "FragTrap Copy assignment operator called!" << std::endl;
    this->Name = obj.Name;
    this->Hit_points = obj.Hit_points;
    this->Energy_points = obj.Energy_points;
    this->Attack_damage = obj.Attack_damage;
    return *this;
}

void FragTrap::highFivesGuys(void)
{
    std::cout << "FragTrap request positive high-fives" << std::endl;
}