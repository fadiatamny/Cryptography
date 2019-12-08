#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ofstream out;

unsigned int calc(unsigned int &seed)
{
    seed = (seed * 1103515245) + 12345;
    return (seed / 65536) % 32768;
}

void test1(unsigned int a, unsigned int b)
{
    out << "starting A is :" << a << " b is :" << b << endl
        << endl
        << endl;
    a = a << 17;
    int count = 0;
    unsigned int res = 0;

    out << "starting A after shift is :" << a << endl
        << endl
        << endl;

    while (1)
    {
        res = (a / 65536) % 32768;
        if (res == b)
        {
            out << "answer is" << a << "res is something " << res << endl;
            ++count;
        }
        if (count >= 1)
            if (res != b)
                break;
        a += 1;
    }
}

void test2(unsigned int a, unsigned int b)
{
    unsigned int res = a * 65536;

    for (int i = 0; 32768; ++i, res++)
    {
        unsigned int tmp = res;
        if (calc(tmp) == b)
        {
            out << res << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return -1;

    stringstream s(argv[1]);
    out.open("log.txt");

    unsigned int seed = 0;
    s >> seed;

    unsigned int a = calc(seed);
    out << "seed divided to 15 bits is " << a << endl;
    unsigned int b = calc(seed);
    out << "seed divided to 15 bits is " << b << endl;

    test1(a, b);
    test2(a, b);
    out.close();
    return 0;
}