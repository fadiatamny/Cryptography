#pragma once
#include "./includes.hpp"

class RC4
{
public:
    RC4(__uint128_t *key);
    void KSA(__uint128_t *key);
    int PRGA();

private:
    int S[256] = {0};
    int j;
    int i;
    int temp;
};