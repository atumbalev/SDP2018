#include <iostream>
#include <string>
#include <stack>

int getPrecedence(char a)
{
    switch(a)
    {
        case 'n': return 2;
        case 'a': return 1;
        case 'o': return 0;
        default: throw "Invalid expression";
    }
}

std::string toRPN(const std::string& expr)
{
    std::stack<char> st;
    std::string result = "";
    
    for (const char& c : expr)
    {
        if (c == 't' || c == 'f')
        {
            result+=c;
        }
        
        else if (c == '(')
        {
            st.push(c);
        }
        
        else if (c == ')')
        {
            while(st.top() != '(')
            {
                result+=st.top();
                st.pop();
            }
            st.pop();
        }
        
        else
        
        {
            while(!st.empty() && st.top() != '(' && getPrecedence(st.top()) >= getPrecedence(c))
            {
                result+=st.top();
                st.pop();
            }
            st.push(c);
        }
    }
        
    while(!st.empty())
    {
        result+=st.top();
        st.pop();
    }

    return result;
}

int main()
{
  std::string expr = "tofafo(faf)";
  std::cout<<toRPN(expr)<<std::endl;
}
