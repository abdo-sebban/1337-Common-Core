/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:40:55 by asebban           #+#    #+#             */
/*   Updated: 2025/11/21 13:15:34 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"
#include <iostream>

Character::Character(std::string const & name)
{
    trash_count = 0;
    this->name = name;
    for (int i = 0; i < 4; i++)
        inventory[i] = NULL;
    for (int i = 0; i < 3; i++)
        trash[i] = NULL;
}

Character::Character(const Character& other)
{
    name = other.name;
    trash_count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (other.inventory[i])
            inventory[i] = other.inventory[i]->clone();
        else
            inventory[i] = NULL;
    }
    for (int i = 0; i < 3; i++)
        trash[i] = NULL;
}


Character::~Character()
{
    for (int i = 0; i < 4; i++)
        delete inventory[i];
    for (int i = 0; i < trash_count; i++)
        delete trash[i];
}

Character & Character::operator=(const Character& other)
{
    if (this != &other)
    {
        name = other.name;
        for (int i = 0; i < 4; i++)
        {
            delete inventory[i];
            if (other.inventory[i])
                inventory[i] = other.inventory[i]->clone();
            else
                inventory[i] = NULL;
        }
        for (int i = 0; i < trash_count; i++)
            delete trash[i];
        trash_count = 0;
    }
    return *this;
}

std::string const & Character::getName() const
{
    return name;
}

void Character::equip(AMateria* m)
{
    if (!m)
        return;

    for (int i = 0; i < 4; i++)
    {
        if (!inventory[i])
        {
            inventory[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4 && inventory[idx])
    {
        if (trash_count == 3)
        {
            delete trash[0];
            trash[0] = trash[1];
            trash[1] = trash[2];
            trash_count--;
        }

        trash[trash_count++] = inventory[idx];
        inventory[idx] = NULL;
    }
}

void Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4 && inventory[idx])
        inventory[idx]->use(target);
}
