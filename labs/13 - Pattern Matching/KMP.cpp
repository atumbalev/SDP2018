#include <string>
#include <vector>
#include <iostream>

auto preprocess(const std::string& word)
{
    std::vector<size_t> result(word.size(), 0);
    size_t i = 1, j = 0;
    while(i != word.size())
    {
        if (word[i] == word[j])
        {
            result[i++] = ++j;
        }
        else if (j == 0)
        {
            result[i++] = 0;
        }
        else
        {
            j = result[j-1];
        }
    }
    return result;
}

size_t KMP(const std::string& text, const std::string& pattern)
{
    auto automata = preprocess(pattern);
    for (auto y : automata )
    {
        std::cout<<y<<" ";
    }
    std::cout<<std::endl;

    size_t i = 0, j = 0;
    while(i != text.size())
    {
        if (j == pattern.size())
        {
            return i - j;
        }
        else if (text[i] == pattern[j])
        {
            ++i;
            ++j;
        }
        else if (j == 0)
        {
            ++i;
        }
        else
        {
            j = automata[j-1];
        }
    }

    return j == pattern.size() ? i - j : -1;
}
    

int main()
{
    std::string text = "ABC ABCDAB ABCDABCDABDE";
    std::string pattern = "ABCDABD";
    int pos = KMP(text, pattern);
    std::cout<<pos<<std::endl;
    if (pos == -1)
    {
        std::cout<<"No Match"<<std::endl;
    }
    else
    {
        std::cout<<text.substr(pos, pattern.size());
    }
    
    
    std::cout<<std::endl;
}