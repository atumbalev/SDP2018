#include <iostream>
#include <stack>
#include <sstream>
#include <string>

std::string decode(const std::string& input)
{
    std::istringstream str(input);
    std::ostringstream output("");

    std::stack<int> stN;
    std::stack<std::string> stW;

    int number;
    char letter;

    std::ostringstream currentWord("", std::ios::app | std::ios::out);
    std::string toAdd;

    while(!str.eof()) {
        int peek = str.peek();  
        if (peek >= '0' && peek <= '9')
        {
            stW.push(currentWord.str());
            currentWord.str("");
            str >> number;
            stN.push(number);
        }
        else if (peek == '(')
        {
            str.ignore();
        }
        else if (peek == ')')
        {
            str.ignore();
            number = stN.top();
            stN.pop();
            
            toAdd = currentWord.str();
            for (int i = 1; i < number; ++i)
            {
                currentWord << toAdd;
            }
            toAdd = currentWord.str();
            currentWord.str(stW.top());
            stW.pop();
            currentWord << toAdd;
        }
        else if (peek >= 'a' && peek <= 'z' || peek >= 'A' && peek <= 'Z')
        {
            str >> letter;
            currentWord << letter;
        }
    }
    while(!stN.empty()) {
        number = stN.top();
        stN.pop();
        toAdd = currentWord.str();
        for (int i = 1; i < number; ++i)
        {
            currentWord << toAdd;
        }
        toAdd = currentWord.str();
        currentWord.str(stW.top());
        stW.pop();
        currentWord << toAdd;
    }

    return currentWord.str();
}

int main(int argc, char const *argv[])
{
    std::string input = "3(a4(b))";
    std::cout<<decode(input)<<std::endl;
    while (std::cin>>input)
    {
        std::cout<<decode(input)<<std::endl;
    }
    return 0;
}
