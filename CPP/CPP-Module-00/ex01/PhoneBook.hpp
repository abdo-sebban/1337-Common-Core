/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:24:38 by asebban           #+#    #+#             */
/*   Updated: 2025/08/11 06:39:13 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include <iomanip>
#include "Contact.hpp"

class PhoneBook
{
    private:
        Contact contact[8];
        int     index;
        int     size;
    public:
        PhoneBook();
        void    addContact(Contact contact);
        void    displayContacts();
        void    displayContactByIndex(int i);
        int     getSize();
};

#endif