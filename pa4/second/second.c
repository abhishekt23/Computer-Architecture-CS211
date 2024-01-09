#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>

typedef struct Cache {
    unsigned long tag;
    int valid;
    int age;
}Cache;

Cache** cache;
Cache** cache2;

int write = 0;
int read = 0;
int L1cHit = 0;
int L1cMiss = 0;
int L1policy = 0;
int L1assocNVal = 0;
int L2cHit = 0;
int L2cMiss = 0;
int L2policy = 0;
int L2assocNVal = 0;
int l1HitIndex = 0;
int l2HitIndex = 0;

bool checkL1Hit(unsigned long L1tagIndexBits, unsigned long L1setIndexBits, int L1assocNVal) {
    for(int i = 0; i < L1assocNVal; i++) {
        if(cache[L1setIndexBits][i].tag == L1tagIndexBits) {
            l1HitIndex = i;
            return true;
        }
        else if(i + 1 == L1assocNVal) {
            return false;
        }
    }
    return false;
}

bool checkL2Hit(unsigned long L2tagIndexBits, unsigned long L2setIndexBits, int L2assocNVal) {
    for(int i = 0; i < L2assocNVal; i++) {
        if(cache2[L2setIndexBits][i].tag == L2tagIndexBits) {
            l2HitIndex = i;
            return true;
        }
        else if(i + 1 == L2assocNVal){
            return false;
        }
    }
    return false;
}


int findOldestAgeIndex(int assocNVal, unsigned long setIndexBits) {
    int temp = 0;
    for(int x = 0; x < assocNVal; x++) {
        if(cache[setIndexBits][x].age <= cache[setIndexBits][temp].age) {
            temp = x;
        }
    }
    return temp;
}
int findOldestAge(int assocNVal, unsigned long setIndexBits) {
    int temp = cache[setIndexBits][0].age;
    for(int x = 1; x < assocNVal; x++) {
        if(cache[setIndexBits][x].age >= temp) {
            temp = cache[setIndexBits][x].age;
        }
    }
    return temp;
}
int findOldestAgeIndexTwo(int L2assocNVal, unsigned long L2setIndexBits) {
    int temp = 0;
    for(int x = 0; x < L2assocNVal; x++) {
        if(cache2[L2setIndexBits][x].age <= cache2[L2setIndexBits][temp].age) {
            temp = x;
        }
    }
    return temp;
}
int findOldestAgeTwo(int L2assocNVal, unsigned long L2setIndexBits) {
    int temp = cache2[L2setIndexBits][0].age;
    for(int x = 1; x < L2assocNVal; x++) {
        if(cache2[L2setIndexBits][x].age >= temp) {
            temp = cache2[L2setIndexBits][x].age;
        }
    }
    return temp;
}


void makeCache(int L1numSets, int L1assocNVal) {
    cache = (Cache**)malloc(L1numSets * sizeof(Cache*));
    for(int i = 0; i < L1numSets; i++) {
        cache[i] = (Cache*)malloc(L1assocNVal * sizeof(Cache));
        for(int j = 0; j < L1assocNVal; j++) {
            cache[i][j].valid = 0;
            cache[i][j].age = 0;
        }
    }
}

void makeCache2(int L2numSets, int L2assocNVal) {
    cache2 = (Cache**)malloc(L2numSets * sizeof(Cache*));
    for(int i = 0; i < L2numSets; i++) {
        cache2[i] = (Cache*)malloc(L2assocNVal * sizeof(Cache));
        for(int j = 0; j < L2assocNVal; j++) {
            cache2[i][j].valid = 0;
            cache2[i][j].age = 0;
        }
    }
}

void L2MissAction(unsigned long L2tagIndexBits, unsigned long L2setIndexBits, int L2assocNVal, int L2setBits, int L1setBits, int blockOffBits) {
    for(int i = 0; i < L2assocNVal; i++) {
        if(cache2[L2setIndexBits][i].valid == 0) {
            cache2[L2setIndexBits][i].valid = 1;
            cache2[L2setIndexBits][i].tag = L2tagIndexBits;
            int old = findOldestAgeTwo(L2assocNVal, L2setIndexBits);
            cache2[L2setIndexBits][i].age = old + 1;   
            return;
        }
        else if(i + 1 == L2assocNVal) {            
            int temp = findOldestAgeIndexTwo(L2assocNVal, L2setIndexBits);
            cache2[L2setIndexBits][temp].valid = 1;
            cache2[L2setIndexBits][temp].tag = L2tagIndexBits;
            int old = findOldestAgeTwo(L2assocNVal, L2setIndexBits);
            cache2[L2setIndexBits][temp].age = old + 1;
            return;
        }
    }
}

void L1MissAction(unsigned long L1tagIndexBits, unsigned long L1setIndexBits, int L1assocNVal, int L1setBits, int L2setBits, int blockOffBits, bool L2Hit) {
    for(int i = 0; i < L1assocNVal; i++) {
        if(cache[L1setIndexBits][i].valid == 0) {
            cache[L1setIndexBits][i].valid = 1;
            cache[L1setIndexBits][i].tag = L1tagIndexBits;
            int old = findOldestAge(L1assocNVal, L1setIndexBits);
            cache[L1setIndexBits][i].age = old + 1;  
            return; 
        }
        else if(i + 1 == L1assocNVal) {
            if(L2Hit) {
                int temp = findOldestAgeIndex(L1assocNVal, L1setIndexBits);
                cache[L1setIndexBits][temp].valid = 1;
                cache[L1setIndexBits][temp].tag = L1tagIndexBits;
                int old = findOldestAge(L1assocNVal, L1setIndexBits);
                cache[L1setIndexBits][temp].age = old + 1;
                return;
            }
            if(!L2Hit) {
                int temp = findOldestAgeIndex(L1assocNVal, L1setIndexBits);
                unsigned long tempAddress = cache[L1setIndexBits][temp].tag << (blockOffBits + L1setBits);
                unsigned long evictTagBits = tempAddress >> (blockOffBits + L2setBits);
                unsigned long evictSetBits = (tempAddress >> blockOffBits) & ((1<<L2setBits) - 1);

                cache[L1setIndexBits][temp].valid = 1;
                cache[L1setIndexBits][temp].tag = L1tagIndexBits;
                int old = findOldestAge(L1assocNVal, L1setIndexBits);
                cache[L1setIndexBits][temp].age = old + 1;

                L2MissAction(evictTagBits, evictSetBits, L2assocNVal, L2setBits, L1setBits, blockOffBits);
                return;
            }

        }
    }
}

void memoryAction(char action, unsigned long address, unsigned long L1tagIndexBits, unsigned long L1setIndexBits, int L1assocNVal, int L1setBits, unsigned long L2tagIndexBits, unsigned long L2setIndexBits, int L2assocNVal, int L2setBits, int blockOffBits) {
    if(action == 'W') {
        write++;
    }

    bool L1Hit = checkL1Hit(L1tagIndexBits, L1setIndexBits, L1assocNVal);
    bool L2Hit = checkL2Hit(L2tagIndexBits, L2setIndexBits, L2assocNVal);
    

    if(L1Hit) {
        if(L1policy == 1) {
            L1cHit++;
            return;
        }
        if(L1policy == 2) {
            L1cHit++;
            int old = findOldestAge(L1assocNVal, L1setIndexBits);
            cache[L1setIndexBits][l1HitIndex].age = old + 1;
            return;
        }  
        return;
    }

    if(!L1Hit && L2Hit) {
        read++;
        L1cMiss++;
        L2cHit++;
        unsigned long tempAddress = cache2[L2setIndexBits][l2HitIndex].tag << (blockOffBits + L2setBits);
        unsigned long evictTagBits = tempAddress >> (blockOffBits + L1setBits);
        unsigned long evictSetBits = (tempAddress >> blockOffBits) & ((1<<L1setBits) - 1);
        L1MissAction(evictTagBits, evictSetBits, L1assocNVal, L1setBits, L2setBits, blockOffBits, L2Hit);
        return;
    }

    if(!L1Hit && !L2Hit) {
        read++;
        L1cMiss++;
        L2cMiss++;
        L1MissAction(L1tagIndexBits, L1setIndexBits, L1assocNVal, L1setBits, L2setBits, blockOffBits, L2Hit);
        return;
    }
}

int main(int argc, char* argv[argc + 1]) {

    int L1cacheSize = atoi(argv[1]);
    int blockSize = atoi(argv[4]);

    if(strcmp(argv[3], "fifo") == 0) {
        L1policy = 1;
    }
    else if(strcmp(argv[3], "lru") == 0) {
        L1policy = 2;
    }

    sscanf(argv[2], "assoc:%d", &L1assocNVal);
    int L1numSets = L1cacheSize/L1assocNVal/blockSize;

    int L2cacheSize = atoi(argv[5]);
    sscanf(argv[6], "assoc:%d", &L2assocNVal);
    int L2numSets = L2cacheSize/L2assocNVal/blockSize;

    if(strcmp(argv[7], "fifo") == 0) {
        L2policy = 1;
    }
    else if(strcmp(argv[7], "lru") == 0) {
        L2policy = 2;
    }

    FILE *fp = fopen(argv[8], "r");
    if(!fp) {
        printf("error\n");
        return EXIT_SUCCESS;
    }

    int blockOffBits = log2(blockSize);
    int L1setBits = log2(L1numSets);
    int L2setBits = log2(L2numSets);
    unsigned long L1setIndexBits;
    unsigned long L1tagIndexBits;
    unsigned long L2setIndexBits;
    unsigned long L2tagIndexBits;
    char action;
    unsigned long address;

    makeCache(L1numSets, L1assocNVal);
    makeCache2(L2numSets, L2assocNVal);

    while(fscanf(fp, "%c %lx\n", &action, &address) != EOF) {
        L1tagIndexBits = address >> (blockOffBits + L1setBits);
        L1setIndexBits = (address >> blockOffBits) & ((1<<L1setBits) - 1);
        L2tagIndexBits = address >> (blockOffBits + L2setBits);
        L2setIndexBits = (address >> blockOffBits) & ((1<<L2setBits) - 1);

        memoryAction(action, address, L1tagIndexBits, L1setIndexBits, L1assocNVal, L1setBits, L2tagIndexBits, L2setIndexBits, L2assocNVal, L2setBits, blockOffBits);
    }

    for(int i = 0; i < L1numSets; i++) {
        free(cache[i]);
    }
    free(cache);

    for(int i = 0; i < L2numSets; i++) {
        free(cache2[i]);
    }
    free(cache2);
    
    printf("memread: %d\n", read);
    printf("memwrite: %d\n", write);
    printf("l1cachehit: %d\n", L1cHit);
    printf("l1cachemiss: %d\n", L1cMiss);
    printf("l2cachehit: %d\n", L2cHit);
    printf("l2cachemiss: %d\n", L2cMiss);

    fclose(fp);
    return EXIT_SUCCESS; 
}
 
