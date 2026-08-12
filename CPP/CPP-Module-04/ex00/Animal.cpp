/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:07:14 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 11:23:18 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
    std::cout << "Animal : Default Constructor Called !" << std::endl;
    this->type = "NoType";
}

Animal::Animal(const Animal &obj)
{
    std::cout << "Animal : Copy Constructor Called !" << std::endl;
    this->type = obj.type;
}

Animal::~Animal()
{
    std::cout << "Animal : Destructor Called !" << std::endl;
}

Animal& Animal::operator=(const Animal &obj)
{
    std::cout << "Animal : Copy Assignment Operator Called !" << std::endl;
    this->type = obj.type;
    return *this;
}

void Animal::makeSound() const
{
    std::cout << "Animal : Animal sound" << std::endl;
}

std::string Animal::getType() const
{
    return this->type;
}

