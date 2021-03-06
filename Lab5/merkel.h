#pragma once

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "crypt.h"

#define PUZZLENUM 1

typedef struct{
    uint64_t data[5];
} Puzzle;

typedef struct{
    uint64_t message1;
    uint64_t message2;
    uint64_t key1;
    uint64_t key2;
} DecPuzzle;

Puzzle* genPuzzles();

DecPuzzle* decPuzzle(Puzzle);