/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:49:32 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 16:54:14 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
{
    this->type = "";
}

AMateria::~AMateria()
{

}

AMateria::AMateria(const AMateria& obj)
{
    this->type = obj.type;
}

AMateria::AMateria(std::string const & type)
{
    this->type = type;
}

AMateria& AMateria::operator=(const AMateria& obj)
{
    this->type = obj.type;
    return(*this);
}

std::string const & AMateria::getType() const
{
    return (type);
}

void AMateria::use(ICharacter& target)
{
    (void)target;
}