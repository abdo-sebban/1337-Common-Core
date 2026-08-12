#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) : stack(other.stack) {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        stack = other.stack;
    return (*this);
}

RPN::~RPN() {}

const char *RPN::RPNException::what() const throw()
{
    return ("Error");
}

bool RPN::isOperator(const std::string &token) const
{
    return (token.size() == 1 &&
            (token[0] == '+' || token[0] == '-' ||
             token[0] == '*' || token[0] == '/'));
}

bool RPN::isNumber(const std::string &token) const
{
    return (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])));
}

void RPN::applyOperator(const std::string &op)
{
    if (stack.size() < 2)
        throw RPNException();

    long long b = stack.top(); stack.pop();
    long long a = stack.top(); stack.pop();
    long long result = 0;

    if (op == "+")
    {
        if ((b > 0 && a > LLONG_MAX - b) ||
            (b < 0 && a < LLONG_MIN - b))
            throw RPNException();
        result = a + b;
    }
    else if (op == "-")
    {
        if ((b < 0 && a > LLONG_MAX + b) ||
            (b > 0 && a < LLONG_MIN + b))
            throw RPNException();
        result = a - b;
    }
    else if (op == "*")
    {
        if (a != 0 && b != 0)
        {
            if ((a == -1 && b == LLONG_MIN) || (b == -1 && a == LLONG_MIN))
                throw RPNException();
            if (a > LLONG_MAX / b || a < LLONG_MIN / b)
                throw RPNException();
        }
        result = a * b;
    }
    else
    {
        if (b == 0)
            throw RPNException();
        if (a == LLONG_MIN && b == -1)
            throw RPNException();
        result = a / b;
    }

    stack.push(result);
}

long long RPN::evaluate(const std::string &expression)
{
    while (!stack.empty())
        stack.pop();

    std::istringstream  iss(expression);
    std::string         token;

    while (iss >> token)
    {
        if (isOperator(token))
            applyOperator(token);
        else if (isNumber(token))
            stack.push(token[0] - '0');
        else
            throw RPNException();
    }

    if (stack.size() != 1)
        throw RPNException();
    return (stack.top());
}