#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cctype>

std::unordered_map<char, unsigned> WEIGHTS = {
	{'H', 1},
	{'C', 12},
	{'O', 16},
};

#define openingBracket 0

int main(int argc, char const *argv[])
{
	std::string formula;
	std::cin >> formula;
	// 0 means opening bracket
	std::stack<unsigned> st;

	for (char c : formula)
	{
		if (c == '(')
		{
			st.push(openingBracket);
		}

		else if (c == ')')
		{
			int total = 0;
			while(st.top() != openingBracket)
			{
				total += st.top();
				st.pop();
			}

			st.pop();
			st.push(total);
		}

		else if (std::isdigit(c))
		{
			int total = st.top();
			st.pop();
			st.push(total * (c - '0'));
		}

		else
		{
			st.push(WEIGHTS[c]);
		}
	}

	int total = 0;
	while (!st.empty())
	{
		total += st.top();
		st.pop();
	}

	std::cout<<total;

	return 0;
}