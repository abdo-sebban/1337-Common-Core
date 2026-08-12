/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:48:00 by asebban           #+#    #+#             */
/*   Updated: 2025/11/20 15:02:20 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    const int size = 10;
    Animal* animals[size];

    for (int i = 0; i < size; i++)
    {
        if (i < size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }
    
    for (int i = 0; i < size; i++)
        delete animals[i];
    Dog dog1;
    dog1.getBrain()->setIdea(0, "Dog1 idea!");
    Dog dog2 = dog1;
    dog1.getBrain()->setIdea(0, "Changed idea!");
    std::cout << "dog1: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog2: " << dog2.getBrain()->getIdea(0) << std::endl;

    return 0;
}
