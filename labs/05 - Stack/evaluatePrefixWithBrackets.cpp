// https://learn.fmi.uni-sofia.bg/mod/resource/view.php?id=65406

#include <stack>
#include <iostream>
#include <string>
#include <sstream>

double calculate(const std::string& input)
{
    std::istringstream str(input);

    std::stack<double> numbers;
    std::stack<char> op;
    std::stack<char> brackets;

    char symbol;
    double number;

    while(!str.eof()) {
        int peek = str.peek();
        if (peek == '*' || peek == '+')
        {
            str >> symbol;
            op.push(symbol);
        }
        else if (peek == '(')
        {
            str.ignore();
            brackets.push('(');
        }
        else if (peek >= '0' && peek <= '9')
        {
            str >> number;
            numbers.push(number);
            brackets.push('\0');
        }
        else if (peek == ')')
        {
            str.ignore();
            double result = op.top() == '+' ? 0 : 1;
            while(!brackets.empty() && brackets.top() != '(')
            {
                brackets.pop();
                result = op.top() == '+' ? result + numbers.top() : result * numbers.top(); 
                numbers.pop();
            }
            op.pop();
            numbers.push(result);
            brackets.pop();
            brackets.push('\0');
        }
        else
        {
            str.ignore();
        }
    }

    return numbers.top();
}

int main(int argc, char const *argv[])
{
    std::string input = "+(*(2,3), 4 , +(4,5,6))";
    std::cout<<calculate(input)<<std::endl;
    
    return 0;
}
