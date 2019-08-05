#include <iostream>
#include <stack>
#include <vector>
​
long int maxArea(const std::vector<int>& histogram)
{
  long int maxArea = 0;
  long int currentArea;
  std::stack<size_t> st; 
  for(size_t i = 0 ; i < histogram.size(); ++i)
  {
    if (st.empty() || histogram[st.top()] <= histogram[i])
    {
      st.push(i);
    }

    // After popping an index from the stack, the index under it is the last element smaller than it and the next element in the array is the first smaller element after it
    else
    {
      while(!st.empty() && histogram[st.top()] > histogram[i])
      {
        size_t top = st.top();
        st.pop();
        currentArea = histogram[top] * (st.empty() ? i : i - st.top() - 1);
        
        maxArea = currentArea > maxArea ? currentArea : maxArea;
      }
      st.push(i);
    }
  }
  
  while(!st.empty())
  {
    size_t top = st.top();
    st.pop();
    currentArea = histogram[top] * (st.empty() ? histogram.size() - 1 : histogram.size() - 1 - st.top());
    maxArea = currentArea > maxArea ? currentArea : maxArea;
  }
  
  return maxArea;
  
}
​
int main()
{
  std::vector<int> histogram = {2, 1, 4, 5, 1, 3, 3,};
  std::cout<<maxArea(histogram)<<std::endl;
}
