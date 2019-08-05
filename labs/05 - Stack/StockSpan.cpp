#include <iostream>
#include <stack>
#include <vector>

int main(int argc, char const *argv[])
{
	std::stack<size_t> st;
	st.push(0);
	std::vector<int> inputs = {5, 2, 3, 7, 6, 4};
	std::vector<int> spans(inputs.size());
	spans[0] = 1;

	for (int i = 1; i < inputs.size(); ++i)
	{
		while(!st.empty() && inputs[st.top()] <= inputs[i])
		{
			st.pop();
		}

		spans[i] = (st.empty() ? (i+1) : (i - st.top()));

		st.push(i);
	}

	for(int span : spans)
	{
		std::cout<<span<<" ";
	}
	return 0;
}