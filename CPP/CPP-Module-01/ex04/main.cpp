/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:43:46 by asebban           #+#    #+#             */
/*   Updated: 2025/10/07 11:57:40 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: ./Replace filename s1 s2" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    
    if (s1.empty())
    {
        std::cerr << "s1 must not be empty" << std::endl;
        return 1;
    }

    std::ifstream infile(filename.c_str());
    if (!infile)
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    std::ostringstream ss;
    ss << infile.rdbuf();
    std::string content = ss.str();
    std::string out;
    size_t pos = 0;
    size_t found;
    while ((found = content.find(s1, pos)) != std::string::npos)
    {
        out += content.substr(pos, found - pos);
        out += s2;
        pos = found + s1.size();
    }

    std::ofstream outfile((filename + ".replace").c_str());
    if (!outfile)
    {
        std::cerr << "Error creating output file" << std::endl;
        return 1;
    }
    outfile << out;
    return 0;
}
