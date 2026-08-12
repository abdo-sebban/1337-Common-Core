/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:33:31 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 16:33:47 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
    private:
        AMateria*   materias[4];
    public:
        MateriaSource();
        MateriaSource(const MateriaSource &other);
        ~MateriaSource();
        MateriaSource   &operator=(const MateriaSource &other);
        void            learnMateria(AMateria* m);
        AMateria*       createMateria(std::string const & type);
};

#endif