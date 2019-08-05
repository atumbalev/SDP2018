#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <assert.h>

int getWeight(char c)
{
	switch(c)
	{
		case '*': case '/': 
			return 2;
		case '+': case '-':
			return 1;
		default:
			return 100;		
	}
}

bool isOperation(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

double evaluate(const std::string& input)
{
	double number1, number2;
	char op;
	std::stack<char> st;
	std::istringstream expr(input);

	std::stack<double> rpn;

	while(!expr.eof())
	{
		char next = expr.peek();
		if (isOperation(next))
		{
			expr >> op;
			while(!st.empty() && st.top() != '(' && getWeight(st.top()) >= getWeight(op))
			{
				char op2 = st.top();
				number2 = rpn.top();
				rpn.pop();
				number1 = rpn.top();
				rpn.pop();
				switch(op2)
				{
					case '+': rpn.push(number1 + number2); break;
					case '*': rpn.push(number1 * number2); break;
					case '-': rpn.push(number1 - number2); break;
					case '/': assert(number2); rpn.push(number1 / number2); break;
				}
				st.pop();
			}

			st.push(op);
		}
		else if (isDigit(next))
		{
			expr >> number1;
			rpn.push(number1);
		}
		else if (next == '(')
		{
			expr.ignore();
			st.push('(');
		}
		else if (next == ')')
		{
			expr.ignore();
			while(st.top() != '(')
			{
				op = st.top();
				number2 = rpn.top();
				rpn.pop();
				number1 = rpn.top();
				rpn.pop();
				switch(op)
				{
					case '+': rpn.push(number1 + number2); break;
					case '*': rpn.push(number1 * number2); break;
					case '-': rpn.push(number1 - number2); break;
					case '/': assert(number2); rpn.push(number1 / number2); break;
				}
				st.pop();
			}

			st.pop();
		}
		else
		{
			expr.ignore();
		}
	}
	while(!st.empty()) {
	    op = st.top();
		number2 = rpn.top();
		rpn.pop();
		number1 = rpn.top();
		rpn.pop();
		switch(op)
		{
			case '+': rpn.push(number1 + number2); break;
			case '*': rpn.push(number1 * number2); break;
			case '-': rpn.push(number1 - number2); break;
			case '/': assert(number2); rpn.push(number1 / number2); break;
		}
		st.pop();
	}

	return rpn.top();

}

int main(int argc, char const *argv[])
{
	std::string input;
	getline(std::cin, input);
	std::cout<<evaluate(input);

	return 0;
}
