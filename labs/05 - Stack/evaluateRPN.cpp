#include <sstream>
#include <string>
#include <iostream>
#include <stack>
#include <assert.h>

double evalRPN(const std::string& expression)
{
    std::istringstream expr(expression);
    std::stack<double> st;
    char operation;
    double operand1, operand2;
    while(!expr.eof())
    {
        char next = expr.peek();
        if (next == '+' || next == '-' || next == '*' || next == '/') // operation
        {
            expr >> operation;
            switch (operation)
            {
                case '+':
                    operand2 = st.top();
                    st.pop();
                    operand1 = st.top();
                    st.pop();
                    st.push(operand1 + operand2);
                    break;
                case '-':
                    operand2 = st.top();
                    st.pop();
                    operand1 = st.top();
                    st.pop();
                    st.push(operand1 - operand2);
                    break;  
                case '*':
                    operand2 = st.top();
                    st.pop();
                    operand1 = st.top();
                    st.pop();
                    st.push(operand1 * operand2);
                    break;  
                case '/':
                    operand2 = st.top();
                    assert(operand2);
                    st.pop();
                    operand1 = st.top();
                    st.pop();
                    assert(operand2);
                    st.push(operand1 / operand2);
                    break;
            }
        }
        else if (next >= '0' && next <= '9') // operand
        {
            expr >> operand1;
            st.push(operand1);
        }
        else // trash
        {
            expr.get();
        }
    }
    return st.top();
}

int main(int argc, char const *argv[])
{
    std::cout<<evalRPN("1.5 2.6 + 1.4 2.5 ++ 4/");
}
