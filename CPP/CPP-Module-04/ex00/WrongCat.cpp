/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:04:17 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 12:09:37 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
    std::cout << "WrongCat : Default Constructor Called !" << std::endl;
    this->type = "WrongCat";
}
WrongCat::WrongCat(const WrongCat &obj) : WrongAnimal(obj)
{
    std::cout << "WrongCat : Copy Constructor Called !" << std::endl;
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat : Destructor Called !" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat &obj)
{
    std::cout << "WrongCat : Copy assingment Operator Called !" << std::endl;
    this->type = obj.type;
    return *this;
}

void WrongCat::makeSound() const
{
    std::cout << "Meoooow Meow" << std::endl;
}
