/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:07:18 by asebban           #+#    #+#             */
/*   Updated: 2025/11/15 09:48:03 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap
{
    private:
        std::string          Name;
        unsigned int         Hit_points;
        unsigned int         Energy_points;
        unsigned int         Attack_damage;

    public:
        ClapTrap();
        ClapTrap(const ClapTrap &obj);
        ClapTrap(std::string Name);
        ~ClapTrap();
        ClapTrap& operator=(const ClapTrap &obj);
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif
