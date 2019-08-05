/*Даден e HTML документ, съдържащ отварящи и затварящи тагове. За да може документът да се визуализира коректно, отварящите и затварящите тагове в него трябва да са правилно вложени.
Да се напише програма, която проверява дали в таговете в даден HTML документ са правилно вложени.
Да се напише програма, която в даден HTML документ намира тагът с най-голямо вложение (най-вътрения). Ако има няколко тага на едно и също ниво на вложение, се извежда първия.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <stack>

// assuming no empty or self-closing tags
// assuming tags are case sensitive

std::string getNextTag(std::istream& in) // assume we are ar a correct position
{
    std::ostringstream out("");
    while(in.peek() != '<' && !in.eof())
    {
        in.ignore();
    }
    
    if (in.eof())
    {
        return "";
    }
    char next;
    do
    {
        next = in.get();
        out << next;
    } while(next != '>');
    
    return out.str();
}

bool openTag(const std::string& tag) // assume valid tag
{
    return tag[1] != '/';
}

bool closes(const std::string& open, const std::string& close) // assume both are correct tags
{
    // not sure if html attributes should be considered
    return open.substr(1, close.length() - 3) == close.substr(2, close.length() - 3);
}

bool validHTML(std::istream& html)
{
    std::stack<std::string> st;
    std::string nextTag;
    
    while((nextTag = getNextTag(html)) != "")
    {
        if (openTag(nextTag))
        {
            st.push(nextTag);
        }
        
        else if (closes(st.top(), nextTag))
        {
            st.pop();
        }
        
        else // missmatched tags
        {
            return false;
        }
    }
    
    return true;
}

size_t maxIdentation(std::istream& html)
{
    int maxIdentation = 0, currentIdentation = -1;
    std::string nextTag;
    while((nextTag = getNextTag(html)) != "")
    {
        if (openTag(nextTag))
        {
            currentIdentation++;
            maxIdentation = std::max(maxIdentation, currentIdentation);
        }
        
        else // if (closes(st.top(), nextTag)) // assume it's correct
        {
            currentIdentation--;
        }
    }
    
    return maxIdentation;
}

int main()
{
  std::istringstream html("<html><head>glava</head><body><button onClick=\"doSomething()\">ne6to</button><h2>ne6todr</h2></body></html>");
  std::cout<<std::boolalpha<<validHTML(html)<<std::endl;
  // std::cout<<maxIdentation(html)<<std::endl;
}