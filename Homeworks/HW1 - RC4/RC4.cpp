#include "RC4.hpp"

RC4::RC4(__uint128_t *key)
{
    KSA(key);
};

void RC4::KSA(__uint128_t *key)
{
    i = 0;
    j = 0;
    temp = 0;

    for (i = 0; i < 255; ++i)
    {
        S[i] = i;
    }
    for (i = 0; i < 255; ++i)
    {
        j = (j + S[i] + key[i % 16]) % 256;
        temp = S[j];
        S[j] = S[i];
        S[i] = temp;
    }
}

int RC4::PRGA()
{
    i = 0;
    j = 0;

    int k = 0;

    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    temp = S[j];
    S[j] = S[i];
    S[i] = temp;
    return k = S[(S[i] + S[j]) % 256];
}
