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
        int isNeg = 0;
        int inputNum = num;
        int binaryLength = 0;
        int remainder = 0;
        int indexBA = bitNum - 1;

        int binaryArr[bitNum];
        int onesArr[bitNum];
        int twosArr[bitNum];

        int left = 0;

        //Check if number is positive or negative
        if(num > 0) {
            isNeg = 0;
        }
        if(num < 0) {
            isNeg = 1;
            num = num * -1;
        }

        //Fill all arrays with 0s
        for(int i = 0; i < bitNum; i++) {
            binaryArr[i] = 0;
            onesArr[i] = 0;
            twosArr[i] = 0;
        }

        double lNum = pow(2, bitNum - 1) - 1; //exclusive 
        double sNum = pow(2, bitNum - 1) * -1;

        //Checking edge cases
        if((lNum <= num) && (isNeg == 0)) {
            for(int i = 1; i < bitNum; i++) {
                binaryArr[i] = 1;
            }
            for(int i = 0; i < bitNum; i++) {
                printf("%d", binaryArr[i]);
            }
            printf("\n");
        }
        else if((sNum >= (num * -1)) && (isNeg == 1)) {
            binaryArr[0] = 1;
            for(int i = 0; i < bitNum; i++) {
                printf("%d", binaryArr[i]);
            }
            printf("\n");
        }
        else {
            while ((inputNum != 0) && (binaryLength < bitNum)) {
                binaryLength++;
                remainder = (inputNum % 2);
                binaryArr[indexBA] = remainder;
                indexBA--;
                inputNum = inputNum / 2;
            }

            if(binaryLength > bitNum || inputNum != 0) {
                for(int i = 0; i < bitNum; i++) {
                    binaryArr[i] = 1;
                }
            }

            if(isNeg == 0) {
                for(int i = 0; i < bitNum; i++) {
                    printf("%d", binaryArr[i]);
                }
                printf("\n");
            }
            else {
                //Fill One's Complement Array with One's Complement
                for(int i = 0; i < bitNum; i++) {
                    if(binaryArr[i] == 0) {
                        onesArr[i] = 1;
                    }
                    else if(binaryArr[i] == 1) {
                        onesArr[i] = 0;
                    }
                }

                //Find Two's Complement
                for(int i = bitNum - 1; i >= 0; i--) {
                    if(onesArr[i] == 1 && left == 0) {
                        twosArr[i] = 0;
                    }
                    else if(onesArr[i] == 0 && left == 0) {
                        twosArr[i] = 1;
                        left = 1;
                    }
                    else {
                        twosArr[i] = onesArr[i];
                    }
                }    

                for(int i = 0; i < bitNum; i++) {
                    printf("%d", twosArr[i]);
                }   
                printf("\n");
            }
        }

    }

    fclose(fp1);

}

