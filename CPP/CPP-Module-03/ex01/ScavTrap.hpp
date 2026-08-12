/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:36:24 by asebban           #+#    #+#             */
/*   Updated: 2025/11/14 12:46:45 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap 
{
    public:
        ScavTrap();
        ScavTrap(const ScavTrap& obj);
        ScavTrap(std::string Name);
        ~ScavTrap();
        ScavTrap& operator=(const ScavTrap& obj);
        void attack(const std::string& target);
        void guardGate();
};

#endif