#include "./includes.hpp"
#include "./RC4.hpp"

#define ROUNDS 100000

int main(int argc, const char *argv[])
{
    int resarray[256] = {0};
    std::ofstream resFile;
    std::ofstream graphFile;

    resFile.open("result.txt");
    graphFile.open("graph.txt");

    srand(time(NULL));
    __uint128_t key = rand();

    for (int c = 0; c < ROUNDS; ++c)
    {
        RC4 res(&key);
        res.PRGA();
        int x = res.PRGA();
        resarray[x] += 1;
        key = rand();
    }

    for (int p = 0; p < 256; ++p)
    {
        resFile << resarray[p] << "\n";
        graphFile << p << "\n";
    }

    resFile.close();
    graphFile.close();
    
    return 0;
}
