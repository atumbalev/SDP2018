#include <iostream>
#include <forward_list>
#include <stack>

using term = std::pair<double, unsigned>;
using polynomial = std::forward_list<term>;
using const_iterator = polynomial::const_iterator;
using iterator = polynomial::iterator;

// Non-recursive
void print(const polynomial& p)
{
	std::stack<term> st;
	for (term t : p)
	{
		st.push(t);
	}

	while(!st.empty())
	{
		std::cout<<st.top().first<<"x^"<<st.top().second<<" ";
		st.pop();
	}
}

bool valid(const polynomial& p)
{
	if (p.empty())
	{
		return true;
	}
	auto next = p.begin();
	auto curr = next++; 
	while(curr != p.end())
	{
		if (next == p.end())
		{
			return true;
		}
		if ((*curr).second <= (*next).second)
		{
			return false;
		}
		++curr;
		++next;
	}

	return true;
}

bool equal(const polynomial& a, const polynomial& b)
{
	auto it1 = a.begin();
	auto it2 = b.begin();
	while(it1 != a.end() && it2 != b.end())
	{
		if ((*it1).first != (*it2).first || (*it1).first != (*it2).first)
		{
			return false;
		}
		++it1;
		++it2;
	}

	return (it1 == a.end() && it2 == b.end());
}

polynomial differentiate(const polynomial& p)
{
	polynomial result;
	iterator itR = result.before_begin();

	if (p.empty())
	{
		return result;
	}

	const_iterator it = p.begin();
	for(it; it != p.end(); ++it)
	{
		if ((*it).second != 0)
		{
			result.insert_after(itR, std::make_pair((*it).first*(*it).second, (*it).second - 1));
			itR++;
		}
	}

	return result;
}


// Recursive
void printRHelper(const polynomial& p, const_iterator it)
{
	if (it == p.end())
	{
		return;
	}

	term toPrint = *it;
	++it;
	printRHelper(p, it);
	std::cout<<toPrint.first<<"x^"<<toPrint.second<<" ";
}

void printR(const polynomial& p)
{
	printRHelper(p, p.begin());	
}


bool validRHelper(const polynomial& p, const_iterator it)
{
	if (it == p.end())
	{
		return true;
	}

	auto next = it; ++next;
	if (next == p.end())
	{
		return true;
	}

	if ((*it).second >= (*next).second)
	{
		return false;
	}

	return validRHelper(p, next);
}

bool validR(const polynomial& p)
{
	return validRHelper(p, p.begin());
}

bool equalRHelper(const polynomial& a, const polynomial& b, const_iterator it1, const_iterator it2)
{
	if (it1 == a.end() && it2 == b.end())
	{
		return true;
	}

	if (it1 == a.end() || it2 == b.end())
	{
		return false;
	}

	if ((*it1).first != (*it2).first || (*it1).second != (*it2).second)
	{
		return false;
	}

	++it1;
	++it2;

	return equalRHelper(a, b, it1, it2);
}

bool equalR(const polynomial& a, const polynomial& b)
{
	return equalRHelper(a, b, a.begin(), b.begin());
}

polynomial differentiateRHelper(polynomial& p, iterator it, polynomial& result, iterator itR)
{
	if (it == p.end())
	{
		return result;
	}

	if ((*it).second == 0)
	{
		++it;
		return differentiateRHelper(p, it, result, itR);
	}

	result.insert_after(itR, std::make_pair((*it).first*(*it).second, (*it).second - 1));
	++itR;
	++it;
	
	return differentiateRHelper(p, it, result, itR);
}

polynomial differentiateR(polynomial& p)
{
	polynomial result;
	return differentiateRHelper(p, p.begin(), result, result.before_begin());
}

int main(int argc, char const *argv[])
{
	polynomial p = {std::make_pair(3,3), std::make_pair(2,2), std::make_pair(1,1)};
	printR(p);
	std::cout<<std::endl;
    p = differentiateR(p);
    printR(p);
    std::cout<<std::endl;
    p = differentiateR(p);
    printR(p);
    std::cout<<std::endl;
    p = differentiateR(p);
    printR(p);
    std::cout<<std::endl;
	return 0;
}
