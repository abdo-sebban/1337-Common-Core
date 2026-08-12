/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:16:54 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 17:43:39 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
    std::cout << "Dog : Default Constructor Called !" << std::endl;
    brain = new Brain();
    this->type = "Dog";
}

Dog::Dog(const Dog &obj) : Animal(obj)
{
    std::cout << "Dog : Copy Constructor Called !" << std::endl;
    brain = new Brain(*obj.brain);
}

Dog::~Dog()
{
    delete brain;
    std::cout << "Dog : Destructor Called !" << std::endl;
}

Dog& Dog::operator=(const Dog &obj)
{
    std::cout << "Dog : Copy assignment Operator Called !" << std::endl;

    if (this != &obj)
    {
        this->type = obj.type;
        delete brain;
        brain = new Brain(*obj.brain);
    }
    return *this;
}

void Dog::makeSound() const
{
    std::cout << "baaark bark" << std::endl;
}

Brain* Dog::getBrain() const
{
    return brain;
}