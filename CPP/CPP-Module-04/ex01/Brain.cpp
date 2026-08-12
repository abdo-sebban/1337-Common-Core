/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:30:54 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 14:57:35 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain : Default Constructor Called !" << std::endl;
    for (int i = 0; i < 100; i++)
        ideas[i] = "Default";
}

Brain::Brain(const Brain& obj)
{
    std::cout << "Brain : Copy Constructor Called !" << std::endl;
    for (int i = 0; i < 100; i++)
        ideas[i] = obj.ideas[i];
}

Brain::~Brain()
{
    std::cout << "Brain : Destructor Called !" << std::endl;
}

Brain& Brain::operator=(const Brain &obj)
{
    std::cout << "Brain : Copy Assignment Operator Called !" << std::endl;
    for (int i = 0; i < 100; i++)
        ideas[i] = obj.ideas[i];
    return *this;
}

std::string Brain::getIdea(int i) const
{
    return ideas[i];
}

void Brain::setIdea(int i, const std::string &s)
{
    ideas[i] = s;
}
