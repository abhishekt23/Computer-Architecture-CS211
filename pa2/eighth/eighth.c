#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[argc + 1]) {
    FILE *fp1 = fopen(argv[1], "r");
    if(!fp1) {
        printf("error\n");
        return EXIT_SUCCESS;
    }

    double num; 
    int bitNum;

    while(fscanf(fp1, "%lf %d", &num, &bitNum) != EOF) {

        int binaryArr[bitNum];
        int exponent = 0;
        double ogNum = num;

        for(int i = 0; i < bitNum; i++) {
            binaryArr[i] = 0;
        }

        if(ogNum > 1) {
            while((num / 2) >= 1) {
                num = num / 2;
                exponent++;
            }

            num = num - 1;
            
            for(int i = 0; i < bitNum; i++) {
                num *= 2;
                if(num < 1) {
                    binaryArr[i] = 0;
                }
                if(num > 1) {
                    binaryArr[i] = 1;
                    num = num - 1;
                }
                if(num == 1) {
                    binaryArr[i] = 1;
                    break;
                }
            }            
        }
        
        else if(ogNum < 1) {
            while(num < 1) {
                num = num * 2;
                exponent--;
            }
            num = num - 1;
            for(int i = 0; i < bitNum; i++) {
                num *= 2;
                if(num < 1) {
                    binaryArr[i] = 0;
                }
                if(num > 1) {
                    binaryArr[i] = 1;
                    num = num - 1;
                }
                if(num == 1) {
                    binaryArr[i] = 1;
                    break;
                }            
            }
        }

        else {
            exponent = 0;
        }

        printf("1.");
        for(int i = 0; i < bitNum; i++) {
            printf("%d", binaryArr[i]);
        }
        printf(" %d\n", exponent);

    }

    fclose(fp1);

}

