#include <iostream>
#include <string>
#include <stack>

int main()
{
  std::string str = "1+2)*3-4)*5-6)))";
  std::stack<char> st;
  std::stack<char> result;
  
  for(auto it = str.rbegin(); it != str.rend(); it++) // iterate though the string backwards, we will talk about this after 1-2 weeks (you could also do for(int i = str.siz()-1 ; i >=0; i--) and then work with str[i] instead of *it
  {
      result.push(*it); // add all letters from original string to result;
      
      if (*it == ')') // if it is a bracket, push it
      {
          st.push(')');
      }
      
      else if (*it >= '0' && *it <= '9')
      {
          while(!st.empty() && st.top() != ')') // if empty or top is ) -> break
          {
              // if top is number -> you can pop a number and a bracket then add a ( to the result
              st.pop(); // pop number
              st.pop(); // pop bracket
              result.push('(');
          }
          
          st.push(*it); // after we do enough pops, push the number
      }
  }

  // reverse the result
  while(!result.empty())
  {
      std::cout<<result.top();
      result.pop();
  }
}
