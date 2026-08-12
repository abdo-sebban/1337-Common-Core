/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:00:35 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 12:08:29 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
    std::cout << "WrongAnimal : Default Constructor Called !" << std::endl;
    this->type = "";
}

WrongAnimal::WrongAnimal(const WrongAnimal &obj)
{
    std::cout << "WrongAnimal : Copy Constructor Called !" << std::endl;
    this->type = obj.type;
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "WrongAnimal : Destructor Called !" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal &obj)
{
    std::cout << "WrongAnimal : Copy Assignment Operator Called !" << std::endl;
    this->type = obj.type;
    return *this;
}

void WrongAnimal::makeSound() const
{
    std::cout << "WrongAnimal : WrongAnimal sound" << std::endl;
}

std::string WrongAnimal::getType() const
{
    return this->type;
}

void WrongAnimal::setType(const std::string &type)
{
    this->type = type;
}
