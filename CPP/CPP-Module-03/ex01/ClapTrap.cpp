/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:07:05 by asebban           #+#    #+#             */
/*   Updated: 2025/11/14 11:55:30 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
    std::cout << "ClapTrap Default constructor called!" << std::endl;
    this->Name = "";
    this->Hit_points = 10;
    this->Energy_points = 10;
    this->Attack_damage = 0;
}

ClapTrap::ClapTrap(const ClapTrap &obj)
{
    std::cout << "ClapTrap Copy constructor called!" << std::endl;
    *this = obj;
}

ClapTrap::ClapTrap(std::string Name)
{
    std::cout << "ClapTrap Parameterized constructor called!" << std::endl;
    this->Name = Name;
    this->Hit_points = 10;
    this->Energy_points = 10;
    this->Attack_damage = 0;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap Destructor called!" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &obj)
{
    std::cout << "ClapTrap Copy assignment operator called!" << std::endl;
    this->Name = obj.Name;
    this->Hit_points = obj.Hit_points;
    this->Energy_points = obj.Energy_points;
    this->Attack_damage = obj.Attack_damage;
    return *this;
}

void ClapTrap::attack(const std::string& target)
{
    if (Energy_points <= 0 || Hit_points <= 0)
    {
        std::cout << "ClapTrap " << Name << " cannot attack!" << std::endl;
        return;
    }

    std::cout << "ClapTrap " << Name
              << " attacks " << target
              << ", causing " << Attack_damage
              << " points of damage!" << std::endl;

    Energy_points--;
}

void ClapTrap::takeDamage(unsigned int amount)
{    
    if (amount == 0)
    {
        std::cout << "ClapTrap is already dead!" << std::endl;
        return;
    }   

    if (Hit_points <= amount)
        Hit_points = 0;
    else
        Hit_points -= amount;
    std::cout << "ClapTrap " << Name
            << " takes " << amount << " damage!" << std::endl;
}


void ClapTrap::beRepaired(unsigned int amount)
{
    if (Energy_points <= 0 || Hit_points <= 0)
    {
        std::cout << "ClapTrap " << Name << " cannot repair itself!" << std::endl;
        return;
    }

    if (amount == 0)
    {
        std::cout << "ClapTrap " << Name
                << " cannot repair using zero amount!" << std::endl;
        return;
    }
    std::cout << "ClapTrap " << Name
              << " repairs " << amount << " HP!" << std::endl;

    Hit_points += amount;
    Energy_points--;
}

