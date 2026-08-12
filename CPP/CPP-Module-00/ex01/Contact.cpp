/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:24:29 by asebban           #+#    #+#             */
/*   Updated: 2025/08/11 06:42:55 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void    Contact::ft_set(std::string first_Name, std::string last_Name, std::string nick_name, std::string phone_Number, std::string darkest_Secret)
{
    firstName     = first_Name;
    lastName      = last_Name;
    nickname      = nick_name;
    phoneNumber   = phone_Number;
    darkestSecret = darkest_Secret;
}

std::string Contact::getFirstName()
{
    return(firstName);
}
std::string Contact::getLastName()
{
    return(lastName);
}
std::string Contact::getNickname()
{
    return(nickname);
}
std::string Contact::getPhoneNumber()
{
    return(phoneNumber);
}
std::string Contact::getDarkestSecret()
{
    return(darkestSecret);
}
void    Contact::displayContactFull()
{
    std::cout << "First Name: "     << firstName     << std::endl;
    std::cout << "Last Name: "      << lastName      << std::endl;
    std::cout << "Nickname: "       << nickname      << std::endl;
    std::cout << "Phone Number: "   << phoneNumber   << std::endl;
    std::cout << "Darkest Secret: " << darkestSecret << std::endl;
}