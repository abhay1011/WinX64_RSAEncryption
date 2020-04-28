#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    fstream myfile("a.txt",ios_base::in);
    int a;
    while (myfile >> a)
    {
       cout<<a<<endl;
    }
    return 0;
}
