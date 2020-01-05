#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha1.h"

void hmac(int k1, int k2, char* m, int length, char* dgst)
{
    unsigned int buffsize = length+sizeof(int);
    unsigned char* buff = (unsigned char*) malloc(buffsize * sizeof(char));
    unsigned char hash[20] = {0};

    memcpy(buff,&k2,sizeof(int));
    memcpy(buff+sizeof(int),m,length);

    SHA1_CTX c;

    SHA1Init(&c);
    SHA1Update(&c,buff,buffsize);
    SHA1Final(hash,&c);

    memset(buff, 0, buffsize);

    memcpy(buff,&k1,sizeof(int));
    memcpy(buff+sizeof(int),hash,20);

    SHA1Init(&c);
    SHA1Update(&c,buff,buffsize);
    SHA1Final(dgst,&c);

    free(buff);
}

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        printf("missing message!\nFormat:\nhmac MESSAGE\n\n");
        return -1;
    }
    
    int length = sizeof(argv[1])/sizeof(char);
    int k1 = 123;
    int k2 = 456;
    char key[20] = {0};

    hmac(k1,k2, argv[1], length ,key);

    printf("\n%s\n",key);

    return 0;
}