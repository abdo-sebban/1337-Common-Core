/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:16:54 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 11:21:01 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
    std::cout << "Dog : Default Constructor Called !" << std::endl;
    this->type = "Dog";
}

Dog::Dog(const Dog &obj) : Animal(obj)
{
    std::cout << "Dog : Copy Constructor Called !" << std::endl;
}

Dog::~Dog()
{
    std::cout << "Dog : Destructor Called !" << std::endl;
}

Dog& Dog::operator=(const Dog &obj)
{
    std::cout << "Dog : Copy assingment Operator Called !" << std::endl;
    this->type = obj.type;
    return *this;
}

void Dog::makeSound() const
{
    std::cout << "baaark bark" << std::endl;
}