/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:00:11 by asebban           #+#    #+#             */
/*   Updated: 2025/08/11 08:42:03 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main()
{
    PhoneBook   phonebook;
    std::string command;

    std::cout << "📞 Welcome to Your PhoneBook! Type ADD, SEARCH or EXIT" << std::endl;

    while (true)
    {
        std::cout << "\n> ";
        std::getline(std::cin, command);
        if (std::cin.eof())
        {
            std::cout << "\nEOF detected. Exiting.\n";
            break;
        }
        if (command == "ADD")
        {
            Contact contact;
            std::string firstName, lastName, nickname, phoneNumber, darkestSecret;
            std::cout << "First Name: ";
            std::getline(std::cin, firstName);
            std::cout << "Last Name: ";
            std::getline(std::cin, lastName);
            std::cout << "Nickname: ";
            std::getline(std::cin, nickname);
            std::cout << "Phone Number: ";
            std::getline(std::cin, phoneNumber);
            std::cout << "Darkest Secret: ";
            std::getline(std::cin, darkestSecret);
            if (firstName.empty() || lastName.empty() || nickname.empty() || phoneNumber.empty() || darkestSecret.empty())
            {
                std::cout << "❌ All fields must be filled. Contact not added.\n";
                continue ;
            }
            contact.ft_set(firstName, lastName, nickname, phoneNumber, darkestSecret);
            phonebook.addContact(contact);
            std::cout << "✅ Contact added!";
        }
        else if (command == "SEARCH")
        {
            if (phonebook.getSize() == 0)
            {
                std::cout << "📭 No contacts to display.\n";
                continue;
            }
            phonebook.displayContacts();
            std::string indexStr;
            int index = -1;
            std::cout << "Enter index to view full contact: ";
            std::getline(std::cin, indexStr);

            if (indexStr.length() > 1  || indexStr.empty() || !std::isdigit(indexStr[0]))
            {
                std::cout << "❌ Invalid input." << std::endl;
                continue ;
            }
            index = std::atoi(indexStr.c_str());
            std::cout << "index  : " << index  << std::endl;
            if (index < 0 || index > 7)
            {
                std::cout << "❌ Index out of range (0, 7)." << std::endl;
                continue ;
            }
            phonebook.displayContactByIndex(index);
        }
        else if (command == "EXIT")
        {
            std::cout << "👋 Goodbye!" << std::endl;
            break ;
        }
        else
            std::cout << "❓ Unknown command. Use ADD, SEARCH, or EXIT." << std::endl;
    }
    return (0);
}
