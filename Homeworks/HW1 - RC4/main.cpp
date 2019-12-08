//
//  main.cpp
//  hw1 rc4
//
//  Created by or eitan on 07/12/2019.
//  Copyright © 2019 or eitan. All rights reserved.
//

#include <iostream>
#include <stdint.h>
#include <fstream>
#include "RC4.hpp"
#include <time.h>

using namespace std;

#define ROUNDS 100000

int main(int argc, const char *argv[])
{
    int resarray[256] = {0};
    float percentage[256] = {0};
    ofstream resFile;
    ofstream graphFile;

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
        percentage[p] = resarray[p] / ROUNDS;
        resFile << resarray[p] << "\n";
        graphFile << p << "\n";
    }

    resFile.close();

    return 0;
}
