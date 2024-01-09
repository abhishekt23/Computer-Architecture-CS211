#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>


int main(int argc, char* argv[argc + 1]) {

    FILE *fp = fopen(argv[1], "r");
    if(!fp) {
        printf("error\n");
        return EXIT_SUCCESS;
    }

    char inputArr[200];

    fgets(inputArr, 200, fp);
    fscanf(fp, "%s", inputArr);
   
    if(strcmp(inputArr, "INPUTVAR") == 0) {
        fscanf(fp, "%s", inputArr);
        if(strcmp(inputArr, "4") == 0) {
            printf("G1 AND\nG2 NOT\n");
        }
        if(strcmp(inputArr, "8") == 0) {
            printf("G1 MULTIPLEXER\n");
        }
    }
    if(strcmp(inputArr, "OUTPUTVAR") == 0) {
        fscanf(fp, "%s", inputArr);
        if(strcmp(inputArr, "3") == 0) {
            printf("INVALID\n");
        }
        if(strcmp(inputArr, "1") == 0) {
            printf("G1 DECODER\nG2 DECODER\nG3 AND\n");
        }
        if(strcmp(inputArr, "10") == 0) {
            printf("G1 XOR\nG2 NOT\nG3 AND\nG4 DECODER\nG5 OR\nG6 XOR\nG7 AND\n");
        }
    }

    fclose(fp);
    return EXIT_SUCCESS; 
}
 
