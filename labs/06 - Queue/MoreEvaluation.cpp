/*
В опашка е записан без грешка израз от вида:
<израз> ::= <цифра>   |  s(<израз>) | p(<израз>)
където s(x) и p(x) намират x+1 и x-1, съответно (s(9) се приема за 0, а p(0) – за 9). Като се използва стек да се намери стойността на израза.
*/

#include <queue>
#include <iostream>

size_t s(size_t x)
{
	return (x+1)%10;
}

size_t p(size_t x)
{
	return (x+9)%10;
}

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

size_t evaluate(std::queue<char> q)
{
	char c;
	size_t extra = 0;
	while(!q.empty())
	{
		c = q.front();
		if (isDigit(c))
		{
			return (extra + (c - '0')) % 10;		
		}

		if (c == 'p')
		{
			extra = p(extra);
		}

		if (c == 's')
		{
			extra = s(extra);
		}

		q.pop();
	}
}

int main(int argc, char const *argv[])
{
	std::string expr = "s(s(s(s(s(s(s(s(s(p(2))))))))))";
	std::queue<char> q;
	for(char c : expr)
	{
		q.push(c);
	}

	std::cout<<evaluate(q);
	return 0;
}
