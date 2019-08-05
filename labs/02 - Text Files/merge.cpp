#include<fstream>

using namespace std;

void writeFileToOther(ifstream &src, ofstream &dst)
{
    int num;
    while (!src.eof())
    {
        src >> num;
        dst << num << " ";
    }
}

void mergeFiles(ifstream &m1, ifstream& m2, ofstream &mRes)
{
    if (m1.eof())
    {
        return writeFileToOther(m2, mRes);
    }
    if (m2.eof())
    {
        return writeFileToOther(m1, mRes);
    }
    int num1, num2;

    m1 >> num1;
    m2 >> num2;

    while(!m1.eof() && !m2.eof())
    {
        if (num1 <= num2)
        {
            mRes << num1 << " ";
            m1 >> num1;
            if (m1.eof())
            {
                num1 <= num2 ? mRes << num1 << " " << num2 << " " : mRes << num2 << " " << num1 << " ";
                return writeFileToOther(m2, mRes);
            }

        }
        else
        {
            mRes << num2 << " ";
            m2 >> num2;
            if (m2.eof())
            {
                num1 <= num2 ? mRes << num1 << " " << num2 << " " : mRes << num2 << " " << num1 << " ";
                return writeFileToOther(m1, mRes);
            }
        }
    }
}

int main()
{

    ifstream m1("merge 1.txt"), m2("merge 2.txt");
    ofstream mRes("merge result.txt");

    mergeFiles(m1, m2, mRes);
    m1.close();
    m2.close();
    mRes.close();

    return 0;
}
