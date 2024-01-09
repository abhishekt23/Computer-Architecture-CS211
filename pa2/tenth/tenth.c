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

    int totalNumBits;
    int exponentNumBits;
    int fracNumBits;
    char hex[100];
    int precisionBits;

    while(fscanf(fp1, "%d %d %d %s %d", &totalNumBits, &exponentNumBits, &fracNumBits, hex, &precisionBits) != EOF) {
        
        int binaryArr[totalNumBits];
        int mantissaArr[fracNumBits];
        int exponentArr[exponentNumBits];


        int bias = pow(2, exponentNumBits - 1) - 1;
        int expFieldVal = 0;
        double manFieldVal = 0;

        double finalAns = 0.0;

        for(int i = 0; i < totalNumBits; i++) {
            binaryArr[i] = 2;
        }
        for(int i = 0; i < fracNumBits; i++) {
            mantissaArr[i] = 0;
        }
        for(int i = 0; i < exponentNumBits; i++) {
            exponentArr[i] = 0;
        }

        if(hex[2] == '0' && hex[3] == '0') {
            printf("%.*f\n", precisionBits, finalAns);
        }
        else {
            int i = 2;
            while(hex[i]) {
                if(hex[i] == '0') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == '1') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }
                }
                if(hex[i] == '2') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == '3') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }
                }
                if(hex[i] == '4') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == '5') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }
                }
                if(hex[i] == '6') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == '7') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 0;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }
                }
                if(hex[i] == '8') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == '9') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }
                }
                if(hex[i] == 'a' || hex[i] == 'A') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == 'b'|| hex[i] == 'B') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 0;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }
                }
                if(hex[i] == 'c'|| hex[i] == 'C') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == 'd'|| hex[i] == 'D') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 0;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }
                }
                if(hex[i] == 'e'|| hex[i] == 'E') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 0;
                            break;
                        }
                    }
                }
                if(hex[i] == 'f'|| hex[i] == 'F') {
                    for(int x = 0; x < totalNumBits; x++) {
                        if(binaryArr[x] == 2) {
                            binaryArr[x] = 1;
                            binaryArr[x+1] = 1;
                            binaryArr[x+2] = 1;
                            binaryArr[x+3] = 1;
                            break;
                        }
                    }

                }

                i++;
            }

            int expCounter = 0;
            for(int i = totalNumBits - fracNumBits - exponentNumBits; i <= exponentNumBits; i++) {
                exponentArr[expCounter] = binaryArr[i];
                expCounter++;
            }

            int manCounter = 0;
            for(int i = totalNumBits - fracNumBits; i < totalNumBits; i++) {
                mantissaArr[manCounter] = binaryArr[i];
                manCounter++;
            }

            for(int i = 0; i < exponentNumBits; ++i) {
                expFieldVal = expFieldVal << 1;
                expFieldVal = expFieldVal + exponentArr[i];
            }

            int counter = 0;
            for(int i = 0; i < fracNumBits; i++) {
                counter--;
                if(mantissaArr[i] == 1) {
                    manFieldVal += pow(2, counter);
                }
            }

            
            if(binaryArr[0] == 0) {
                finalAns = pow(-1, 0) * (1 + manFieldVal) * pow(2, expFieldVal - bias);
            }
            else {
                finalAns = pow(-1, 1) * (1 + manFieldVal) * pow(2, expFieldVal - bias);
            }

            printf("%.*f\n", precisionBits, finalAns);
            
    
        }


    }

    fclose(fp1);

}

