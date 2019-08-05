// https://en.wikipedia.org/wiki/Josephus_problem

#include <iostream>
#include <queue>

size_t jp(int n, int k)
{
    std::queue<size_t> q;
    for(size_t i = 1; i <= n; ++i)
    {
        q.push(i);
    }
    
    while(q.size() != 1)
    {
        for(size_t j = 1; j  < k ; j++)
        {
            q.push(q.front());
            q.pop();
        }
        
        q.pop();
    }
    
    return q.front();
}

int main()
{
    auto j = jp(5000000, 2);
    std::cout<<j<<std::endl;
}
