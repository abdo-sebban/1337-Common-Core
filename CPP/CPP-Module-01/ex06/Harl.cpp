/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:46:01 by asebban           #+#    #+#             */
/*   Updated: 2025/10/07 11:05:31 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void Harl::complain(std::string level)
{
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    int index = -1;

    for (int i = 0; i < 4; i++)
    {
        if (levels[i] == level)
        {
            index = i;
            break;
        }
    }

    switch (index)
    {
        case 0:
            std::cout << "[ DEBUG ]" << std::endl;
            std::cout << "I love having extra bacon for my burger!" << std::endl;
        case 1:
            std::cout << "[ INFO ]" << std::endl;
            std::cout << "Adding extra bacon costs more money." << std::endl;
        case 2:
            std::cout << "[ WARNING ]" << std::endl;
            std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
            std::cout << "I've been coming for years, whereas you started working here last month." << std::endl;
        case 3:
            std::cout << "[ ERROR ]" << std::endl;
            std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }
}
