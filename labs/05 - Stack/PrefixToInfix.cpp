#include <stack>
#include <iostream>
#include <sstream>
#include <string>

std::string prefixToInfix(std::istream& in)
{
	std::stack<std::string> st;
	std::string token, token1, token2;
	while(!in.eof())
	{
		in >> token;
		if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
		{
			// if (!st.size()) => invalid expression
			token2 = st.top();
			st.pop();
			// if (!st.size()) => invalid expression
			token1 = st.top();
			st.pop();
			st.push("(" + token1 + " " + token + " " + token2 + ")");
		}

		else
		{
			st.push(token);
		}
	}

	// if (st.size() > 1) => invalid expression
	return st.top();
}

int main(int argc, char const *argv[])
{
	std::istringstream in("10 20 + 3 * 4 5 + /");
	std::cout<<prefixToInfix(in);
	return 0;
}
