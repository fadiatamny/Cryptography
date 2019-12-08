//
//  RC4.hpp
//  hw1 rc4
//
//  Created by or eitan on 07/12/2019.
//  Copyright © 2019 or eitan. All rights reserved.
//

#ifndef RC4_hpp
#define RC4_hpp

#include <stdio.h>
#include <stdint.h>
#include <iostream>

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

#endif /* RC4_hpp */
