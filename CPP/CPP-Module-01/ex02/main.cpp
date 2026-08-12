/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:58:56 by asebban           #+#    #+#             */
/*   Updated: 2025/10/04 11:12:14 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
    std::string s = "HI THIS IS BRAIN";
    std::string* stringPTR = &s;
    std::string& stringREF = s;
    std::cout << "The memory Address of string variable: " << &s << std::endl;
    std::cout << "The memory Address held by stringPTR: " << stringPTR << std::endl;
    std::cout << "The memory Address held by stringREF: " << &stringREF << std::endl;

    std::cout << "The Value of string variable: " << s << std::endl;
    std::cout << "The Value pointed to by stringPTR: " << *stringPTR << std::endl;
    std::cout << "The Value pointed to by stringREF: " << stringREF << std::endl;

    return 0;
}
