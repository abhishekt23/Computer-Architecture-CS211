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

int write = 0;
int read = 0;
int cHit = 0;
int cMiss = 0;
int policy = 0;
int assocNVal = 0;


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

void makeCache(int numSets, int assocNVal) {
    cache = (Cache**)malloc(numSets * sizeof(Cache*));
    for(int i = 0; i < numSets; i++) {
        cache[i] = (Cache*)malloc(assocNVal * sizeof(Cache));
        for(int j = 0; j < assocNVal; j++) {
            cache[i][j].valid = 0;
            cache[i][j].age = 0;
        }
    }
}

void memoryAction(char action, unsigned long tagIndexBits, unsigned long setIndexBits, int assocNVal) {
    if(action == 'W') {
        write++;
    }
    for(int i = 0; i < assocNVal; i++) {
        //if valid bit is 0, no need to evict, just set everything to given inputs
        if(cache[setIndexBits][i].valid == 0) {
            cache[setIndexBits][i].valid = 1;
            cache[setIndexBits][i].tag = tagIndexBits;
            read++;
            cMiss++;
            int old = findOldestAge(assocNVal, setIndexBits);
            cache[setIndexBits][i].age = old + 1;
            return;
        }
        //if tag bits match, check the policy and increment hits and age upon that
        else if(cache[setIndexBits][i].tag == tagIndexBits) {
            if(policy == 1) {
                cHit++;
                return;
            }
            if(policy == 2) {
                cHit++;
                int old = findOldestAge(assocNVal, setIndexBits);
                cache[setIndexBits][i].age = old + 1;
                return;
            }
        }
        //when loop hits the end, meaning there is no spot that matches the query, you need to evict
        else if((i + 1) == assocNVal) {
            read++;
            cMiss++;
            int temp = findOldestAgeIndex(assocNVal, setIndexBits);
            cache[setIndexBits][temp].valid = 1;
            cache[setIndexBits][temp].tag = tagIndexBits;
            int old = findOldestAge(assocNVal, setIndexBits);
            cache[setIndexBits][temp].age = old + 1;
            return;
        }
    }
    return;
}

int main(int argc, char* argv[argc + 1]) {

    int cacheSize = atoi(argv[1]);
    int blockSize = atoi(argv[4]);

    if(strcmp(argv[3], "fifo") == 0) {
        policy = 1;
    }
    else if(strcmp(argv[3], "lru") == 0) {
        policy = 2;
    }

    sscanf(argv[2], "assoc:%d", &assocNVal);
    int numSets = cacheSize/assocNVal/blockSize;

    FILE *fp = fopen(argv[5], "r");
    if(!fp) {
        printf("error\n");
        return EXIT_SUCCESS;
    }

    int blockOffBits = log2(blockSize);
    int setBits = log2(numSets);
    unsigned long setIndexBits;
    unsigned long tagIndexBits;
    char action;
    unsigned long address;

    makeCache(numSets, assocNVal);

    while(fscanf(fp, "%c %lx\n", &action, &address) != EOF) {
        tagIndexBits = address >> (blockOffBits + setBits);
        setIndexBits = (address >> blockOffBits) & ((1<<setBits) - 1);
        memoryAction(action, tagIndexBits, setIndexBits, assocNVal);
    }

    for(int i = 0; i < numSets; i++) {
        free(cache[i]);
    }
    free(cache);
    
    printf("memread: %d\n", read);
    printf("memwrite: %d\n", write);
    printf("cachehit: %d\n", cHit);
    printf("cachemiss: %d\n", cMiss);

    fclose(fp);
    return EXIT_SUCCESS; 
}
 
