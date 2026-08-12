/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:24:33 by asebban           #+#    #+#             */
/*   Updated: 2025/08/11 06:42:26 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
    index = 0;
    size = 0;
}

void PhoneBook::addContact(Contact obj)
{
    contact[index] = obj;
    index = (index + 1) % 8;
    if (size < 8)
        size++;
}

void PhoneBook::displayContactByIndex(int i)
{
    if (i >= 0 && i < size)
        contact[i].displayContactFull();
    else
        std::cout << "Invalid index." << std::endl;
}

int PhoneBook::getSize()
{
    return (size);
}

static std::string truncate(std::string str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return (str);
}

void    PhoneBook::displayContacts()
{
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << std::setw(10) << i << "|"
                  << std::setw(10) << truncate(contact[i].getFirstName()) << "|"
                  << std::setw(10) << truncate(contact[i].getLastName()) << "|"
                  << std::setw(10) << truncate(contact[i].getNickname()) << std::endl;
    }
}
