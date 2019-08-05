#include<iostream>
#include<fstream>
#include<string>

// Count words in file separated by white spaces
int wordCount(std::string fileName)
{
    std::ifstream fin(fileName);
    std::string word;
    int counter = 0;
    while(!fin.eof())
    {
        fin>>word;
        counter++;
        // std::cout<<counter<<": "<<word<<std::endl;
    }
    fin.close();
    return counter;
}
int main()
{
    std::string fileName;
    std::cin>>fileName;
    std::cout<<wordCount(fileName);
}
