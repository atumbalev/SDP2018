#include <iostream>
#include <stack>
#include <string>

bool balanced(const std::string& expr)
{
	std::stack<char> st;
	for(char a : expr)
	{
		switch(a)
		{
			case ')':
				if (!st.empty() && st.top() == '(')
				{
					st.pop();
				}
				else 
				{
					return false;
				}
				break;
			case '(':
				st.push(a);
				break;
			case '[':
				if (!st.empty() && st.top() == '(')
				{
					return false;
				} 
				st.push(a);
				break;
			case ']':
				if (!st.empty() && st.top() == '[')
				{
					st.pop();
				}
				else 
				{
					return false;
				}
				break;
		}
	} 	
	if (st.empty())
	{
		return true;
	}
}
int main(int argc, char const *argv[])
{
	std::string input;
	std::cin>>input;
	std::cout<<std::boolalpha<<balanced(input)<<std::endl;
	return 0;
}