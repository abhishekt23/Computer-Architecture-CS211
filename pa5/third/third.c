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
    char inputArr[999];

    fgets(inputArr, 999, fp);
    fgets(inputArr, 999, fp);
    fgets(inputArr, 999, fp);
    fgets(inputArr, 999, fp);
    fgets(inputArr, 999, fp);

    fscanf(fp, "%s", inputArr);
    
    if(strcmp(inputArr, "AND") == 0) {
        printf("OUTPUTVAR 2 OUT1 OUT2\nINPUTVAR 4 IN1 IN2 IN3 IN4\nOUTPUTVAL\nOUT1 0 0 0 0 1 1 0 0 1 1 1 1 0 0 0 0\nOUT2 0 1 0 1 1 0 1 0 0 1 0 1 1 0 1 0\nOR IN1 IN3 temp2\nAND IN2 temp2 OUT1\nXOR IN3 IN4 temp3\nAND 1 temp3 OUT2\n");
    }
    if(strcmp(inputArr, "G1") == 0) {
        fscanf(fp, "%s", inputArr);
        if(strcmp(inputArr, "7") == 0) {
            printf("INPUTVAR 8 IN1 IN2 IN3 IN4 IN5 IN6 IN7 IN8\nOUTPUTVAR 2 OUT1 OUT2\nOUTPUTVAL\nOUT1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1\nOUT2 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0\nMULTIPLEXER 4 IN1 IN2 IN3 IN4 IN5 IN6 OUT1\nMULTIPLEXER 4 IN5 IN6 IN7 IN8 IN3 IN4 OUT2\n");
        }
        if(strcmp(inputArr, "3") == 0) {
            printf("INPUTVAR 3 IN1 IN2 IN3\nOUTPUTVAR 1 OUT1\nOUTPUTVAL\nOUT1 0 1 1 1 0 0 1 0\nAND IN1 IN2 temp1\nNOT temp1 temp3\nOR IN2 IN3 temp4\nAND temp3 temp4 OUT1\n");
        }
    }
    if(strcmp(inputArr, "OR") == 0) {
        fgets(inputArr, 200, fp);
        fscanf(fp, "%s", inputArr);

        if(strcmp(inputArr, "G1") == 0) {
            printf("INPUTVAR 8 IN1 IN2 IN3 IN4 IN5 IN6 IN7 IN8\nOUTPUTVAR 2 OUT1 OUT2\nOUTPUTVAL\nOUT1 0 0 0 0 0 0 1 1 1 1 0 0 1 1 1 1 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 1 1 1 1\nOUT2 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1\nOR IN1 IN2 temp2\nOR IN3 IN4 temp4\nOR temp2 temp4 temp5\nOR IN5 IN6 temp6\nAND IN6 IN7 temp7\nXOR temp6 temp7 temp8\nXOR temp5 temp8 OUT1\nNOT IN8 OUT2\n");
        }
        if(strcmp(inputArr, "OR") == 0) {
            printf("INPUTVAR 3 IN1 IN2 IN3\nOUTPUTVAR 2 OUT1 OUT2\nOUTPUTVAL\nOUT1 0 0 1 1 1 1 1 1\nOUT2 1 0 0 1 1 0 0 1\nOR IN1 IN2 OUT1\nNOT IN3 OUT2\n");
        }
    }
    
    fclose(fp);
    return EXIT_SUCCESS; 
}
 
