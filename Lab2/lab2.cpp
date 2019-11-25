#include <iostream>

using namespace std;

unsigned int seed = 0;

void setseed(int s)
{
    seed = s;
}

unsigned int calc()
{
    seed = (seed * 1103515245) + 12345;
    cout << seed << endl;
    return (seed / 65536) % 32768;
}

unsigned int test(unsigned int a,unsigned int b)
{
    a = a << 17;   
    
    unsigned int res = 0;

    while(1)
    {
        res = (a / 65536) % 32768;
        if(res == b)
            return a;
        a += 1;
    }
}

int main(int argc, char* argv[])
{
    unsigned int x = 0;
    cin >> x;

    setseed(x);
    unsigned int a = calc();
    cout << a << endl;
    unsigned int b = calc();
    cout << b << endl;


    cout << test(a,b) << std::endl;

    return 0;
}