/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:18:18 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 15:00:38 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
    std::cout << "Cat : Default Constructor Called !" << std::endl;
    this->type = "Cat";
    this->brain = new Brain();
}

Cat::Cat(const Cat &obj) : Animal(obj)
{
    std::cout << "Cat : Copy Constructor Called !" << std::endl;
    this->brain = new Brain(*obj.brain);
}

Cat::~Cat()
{
    std::cout << "Cat : Destructor Called !" << std::endl;
    delete brain;
}

Cat& Cat::operator=(const Cat &obj)
{
    std::cout << "Cat : Copy Assignment Operator Called !" << std::endl;
    if (this != &obj)
    {
        this->type = obj.type;
        delete brain;
        brain = new Brain(*obj.brain);
    }
    return *this;
}

void Cat::makeSound() const
{
    std::cout << "Meoooow Meow" << std::endl;
}

Brain* Cat::getBrain() const
{
    return brain;
}