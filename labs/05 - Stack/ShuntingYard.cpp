#include <sstream>
#include <iostream>
#include <stack>
#include <string>

size_t getPrecedence(char op)
{
    switch(op)
    {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '(': return 100;
    }
}

std::string shuntingYardAlgorithm(const std::string& rpnExpression)
{
    std::istringstream expr(rpnExpression);
    std::stack<char> st;
    std::ostringstream result;
    double number;
    char symbol;
    while(!expr.eof())
    {
        char next = expr.peek();
        if (next == '+' || next == '-' || next == '*' || next == '/')
        {
            expr >> symbol;
            size_t precedence = getPrecedence(symbol);
            while (!st.empty() &&
                getPrecedence(st.top()) >= precedence &&
                st.top() != '(')
            {
                result << st.top() << " ";
                st.pop();
            }
            st.push(symbol);
        }
        else if (next >= '0' && next <= '9')
        {
            expr >> number;
            result << number << " ";
        }
        else if (next == '(')
        {
            expr >> symbol;
            st.push(symbol);
        }
        else if (next == ')')
        {
            expr >> symbol;
            while(st.top() != '(')
            {
                result << st.top() << " ";
                st.pop();
            }
            st.pop();
        }
        else
        {
            expr.get();
        }
    }

    while(!st.empty()) {
        result << st.top();
        st.pop();
    }

    return result.str();
}

int main(int argc, char const *argv[])
{
    std::cout<<shuntingYardAlgorithm("(1+2)-1+1");
    return 0;
}
