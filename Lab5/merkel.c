#include "merkel.h"

Puzzle* genPuzzles()
{
    Puzzle* ps = (Puzzle*)malloc(PUZZLENUM*sizeof(Puzzle));

    for(int i = 0; i < PUZZLENUM; ++i)
    {
        srand(time(NULL));
        uint64_t pi = (uint16_t)gen_random_32();
        uint64_t ki1 = gen_random_64();
        uint64_t ki2 = gen_random_64();
        uint64_t xi1 = gen_random_64();
        uint64_t xi2 = gen_random_64();
        char c[8] = "PID ";

        key_set* keys = (key_set*)malloc(16*sizeof(key_set));

        generate_sub_keys((unsigned char*)pi,keys);
        process_message((unsigned char*)c,(unsigned char*)ps[i].data[0],keys,ENCRYPTION_MODE);
        process_message((unsigned char*)xi1,(unsigned char*)ps[i].data[1],keys,ENCRYPTION_MODE);
        process_message((unsigned char*)xi2,(unsigned char*)ps[i].data[2],keys,ENCRYPTION_MODE);
        process_message((unsigned char*)ki1,(unsigned char*)ps[i].data[3],keys,ENCRYPTION_MODE);
        process_message((unsigned char*)ki2,(unsigned char*)ps[i].data[4],keys,ENCRYPTION_MODE);
    }

    return ps;
}


DecPuzzle* decPuzzle(Puzzle p)
{
    srand(time(NULL));
    uint16_t base;

    printf("%d %d\n",p.data[0],p.data[1]);

    while(base < PUZZLENUM)
    {
        uint64_t pi = base++;
        uint64_t ki1 = gen_random_64();
        uint64_t ki2 = gen_random_64();
        uint64_t xi1 = gen_random_64();
        uint64_t xi2 = gen_random_64();

        key_set* keys = (key_set*)malloc(16*sizeof(key_set));

        generate_sub_keys((unsigned char*)pi,keys);

        char c[8] = "PID ";
        char dec[8] = {0};
        process_message((unsigned char*)p.data[0],(unsigned char*)dec,keys,DECRYPTION_MODE);
        if(strcmp(c,dec) == 0)
        {
            DecPuzzle* decP = (DecPuzzle*)malloc(1*sizeof(DecPuzzle));
            process_message((unsigned char*)p.data[1],(unsigned char*)decP->message1,keys,DECRYPTION_MODE);
            process_message((unsigned char*)p.data[2],(unsigned char*)decP->message2,keys,DECRYPTION_MODE);
            process_message((unsigned char*)p.data[3],(unsigned char*)decP->key1,keys,DECRYPTION_MODE);
            process_message((unsigned char*)p.data[4],(unsigned char*)decP->key2,keys,DECRYPTION_MODE);
            return decP;
        }
    }

    return NULL;
}