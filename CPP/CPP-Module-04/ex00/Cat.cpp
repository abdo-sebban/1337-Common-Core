/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:18:18 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 11:21:08 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
    std::cout << "Cat : Default Constructor Called !" << std::endl;
    this->type = "Cat";
}

Cat::Cat(const Cat &obj) : Animal(obj)
{
    std::cout << "Cat : Copy Constructor Called !" << std::endl;
}

Cat::~Cat()
{
    std::cout << "Cat : Destructor Called !" << std::endl;
}

Cat& Cat::operator=(const Cat &obj)
{
    std::cout << "Cat : Copy assingment Operator Called !" << std::endl;
    this->type = obj.type;
    return *this;
}

void Cat::makeSound() const
{
    std::cout << "Meoooow Meow" << std::endl;
}
