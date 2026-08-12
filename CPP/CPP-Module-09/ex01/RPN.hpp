#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <list>

class RPN
{
    private:
        std::stack<long long, std::list<long long> >  stack;
        bool                                           isOperator(const std::string &token) const;
        bool                                           isNumber(const std::string &token) const;
        void                                           applyOperator(const std::string &op);

    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        long long evaluate(const std::string &expression);
        class RPNException : public std::exception
        {
            public:
                const char *what() const throw();
        };
};

#endif