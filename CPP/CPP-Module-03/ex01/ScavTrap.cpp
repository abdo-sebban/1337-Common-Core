/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:36:28 by asebban           #+#    #+#             */
/*   Updated: 2025/11/15 09:53:09 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
    std::cout << "ScavTrap Default constructor called!" << std::endl;
    this->Name = "Anonymous";
    this->Hit_points = 100;
    this->Energy_points = 50;
    this->Attack_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &obj) : ClapTrap(obj)
{
    std::cout << "ScavTrap Copy constructor called!" << std::endl;
    *this = obj;
}

ScavTrap::ScavTrap(std::string Name) : ClapTrap(Name)
{
    std::cout << "ScavTrap Parameterized constructor called!" << std::endl;
    this->Hit_points = 100;
    this->Energy_points = 50;
    this->Attack_damage = 20;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap Destructor called!" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap &obj)
{
    std::cout << "ScavTrap Copy assignment operator called!" << std::endl;
    this->Name = obj.Name;
    this->Hit_points = obj.Hit_points;
    this->Energy_points = obj.Energy_points;
    this->Attack_damage = obj.Attack_damage;
    return *this;
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap is now in Gate keeper mode." << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (Energy_points <= 0 || Hit_points <= 0)
    {
        std::cout << "ScavTrap " << Name << " cannot attack!" << std::endl;
        return;
    }

    std::cout << "ScavTrap " << Name
              << " attacks " << target
              << ", causing " << Attack_damage
              << " points of damage!" << std::endl;

    Energy_points--;
}