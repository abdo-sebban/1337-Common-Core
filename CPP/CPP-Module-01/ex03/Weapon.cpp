/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:14:14 by asebban           #+#    #+#             */
/*   Updated: 2025/10/07 10:34:49 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
#include <iostream>

Weapon::Weapon()
{
    type = "";
}

Weapon::Weapon(const std::string &type)
{
    this->type = type;
}

const std::string& Weapon::getType() const
{
    return type;
}

void Weapon::setType(const std::string &newType)
{
    type = newType;
}
