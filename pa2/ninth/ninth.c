#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void findBinaryForWholeNum(double fractionChanged, int valInExpField, int exponentNumBits, int binaryArr[]) { 
    int binaryLength = 0;
    int remainder = 0;
    int indexOfBinaryArr = exponentNumBits - 1;

    while ((valInExpField != 0) && (binaryLength < exponentNumBits)) {
        binaryLength++;
        remainder = (valInExpField % 2);
        binaryArr[indexOfBinaryArr] = remainder;
        indexOfBinaryArr--;
        valInExpField = valInExpField / 2;
    }

    if(binaryLength > exponentNumBits || valInExpField != 0) {
        for(int i = 0; i < exponentNumBits; i++) {
            binaryArr[i] = 1;
        }
    }    
}

void findBinaryforFrac(double fractionChanged, int fracNumBits, int decBinaryArr[]) {
    for(int i = 0; i < fracNumBits+3; i++) {
        fractionChanged *= 2;
        if(fractionChanged < 1) {
            decBinaryArr[i] = 0;
        }
        if(fractionChanged > 1) {
            decBinaryArr[i] = 1;
            fractionChanged = fractionChanged - 1;
        }
        if(fractionChanged == 1) {
            decBinaryArr[i] = 1;
            break;
        }
    } 
}

void addOne(int fracNumBits, int decBinaryArr[], int decArrRounded[]) {
    int left = 0;
    for(int i = fracNumBits - 1; i >= 0; i--) {
        if(decBinaryArr[i] == 1 && left == 0) {
            decArrRounded[i] = 0;
        }
        else if(decBinaryArr[i] == 0 && left == 0) {
            decArrRounded[i] = 1;
            left = 1;
        }
        else {
            decArrRounded[i] = decBinaryArr[i];
        }
    }     
}

void addOneForExp(int exponentNumBits, int binaryArr[], int binArrRounded[]) {
    int left = 0;
    for(int i = exponentNumBits - 1; i >= 0; i--) {
        if(binaryArr[i] == 1 && left == 0) {
            binArrRounded[i] = 0;
        }
        else if(binaryArr[i] == 0 && left == 0) {
            binArrRounded[i] = 1;
            left = 1;
        }
        else {
            binArrRounded[i] = binaryArr[i];
        }
    }     
}

void printOutputForPos(int exponentNumBits, int fracNumBits, int binaryArr[], int secondArr[]) {
    printf("0");
    for(int i = 0; i < exponentNumBits; i++) {
        printf("%d", binaryArr[i]);
    }
    for(int i = 0; i < fracNumBits; i++) {
        printf("%d", secondArr[i]);
    }
    printf("\n");
}

void printOutputForNeg(int exponentNumBits, int fracNumBits, int binaryArr[], int secondArr[]) {
    printf("1");
    for(int i = 0; i < exponentNumBits; i++) {
        printf("%d", binaryArr[i]);
    }
    for(int i = 0; i < fracNumBits; i++) {
        printf("%d", secondArr[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[argc + 1]) {
    FILE *fp1 = fopen(argv[1], "r");
    if(!fp1) {
        printf("error\n");
        return EXIT_SUCCESS;
    }

    double fraction;
    int totalNumBits;
    int exponentNumBits;
    int fracNumBits;

    while(fscanf(fp1, "%lf %d %d %d", &fraction, &totalNumBits, &exponentNumBits, &fracNumBits) != EOF) {
        
        int bias = pow(2, exponentNumBits - 1) - 1;
        double fractionChanged = fraction;
        int exponent = 0;
        int valInExpField = 0;
        int binaryArr[exponentNumBits];
        int decBinaryArr[fracNumBits + 3];
        int indexOfDecArr = 0;
        int binaryLength2 = 0;
        int remainder2 = 0;
        int decArrRounded[fracNumBits];
        int binArrRounded[exponentNumBits];


        for(int i = 0; i < exponentNumBits; i++) {
            binaryArr[i] = 0;
        }
        
        for(int i = 0; i < fracNumBits + 3; i++) {
            decBinaryArr[i] = 0;
        }
        for(int i = 0; i < fracNumBits; i++) {
            decArrRounded[i] = 0;
        }
        for(int i = 0; i < exponentNumBits; i++) {
            binArrRounded[i] = 0;
        }
        
        if(fraction >= 1) {
            
            while((fractionChanged / 2) >= 1) {
                fractionChanged = fractionChanged / 2;
                exponent++;
            } 

            fractionChanged = fractionChanged - 1;
            valInExpField = bias + exponent;

            findBinaryForWholeNum(fractionChanged, valInExpField, exponentNumBits, binaryArr);

            findBinaryforFrac(fractionChanged, fracNumBits, decBinaryArr);

            if(decBinaryArr[fracNumBits] == 0) { //if first bit is 0, do nothing
                printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decBinaryArr);
            }
            //if next three are 1 0 0, check digit right before and round up or down
            else if(decBinaryArr[fracNumBits] == 1 && decBinaryArr[fracNumBits+1] == 0 && decBinaryArr[fracNumBits+2] == 0) {
                //if 101 or 011, you can add one and round up
                int count = 0;
                for(int i = 0; i < fracNumBits; i++) {
                    if(decBinaryArr[i] == 1) {
                        count++;
                    }
                }
                if(decBinaryArr[fracNumBits - 1] == 1 && count < fracNumBits) {
                    addOne(fracNumBits, decBinaryArr, decArrRounded);
                    printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decArrRounded); 
                }
                else if(count == fracNumBits) { 
                    //if everything one, add one to exponent field
                    addOne(fracNumBits, decBinaryArr, decArrRounded);
                    addOneForExp(exponentNumBits, binaryArr, binArrRounded);
                    printOutputForPos(exponentNumBits, fracNumBits, binArrRounded, decArrRounded);
                }
                else { //round down
                    printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decBinaryArr);
                }
            }
            else { //round up
                int count = 0;
                for(int i = 0; i < fracNumBits; i++) {
                    if(decBinaryArr[i] == 1) {
                        count++;
                    }
                }
                if(count == fracNumBits) {
                    //check if everything one and round in exp field based on that
                    addOne(fracNumBits, decBinaryArr, decArrRounded);
                    addOneForExp(exponentNumBits, binaryArr, binArrRounded);
                    printOutputForPos(exponentNumBits, fracNumBits, binArrRounded, decArrRounded);
                }
                else {
                    //round dec field and print
                    addOne(fracNumBits, decBinaryArr, decArrRounded);
                    printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decArrRounded);                   
                }
            }

        }

        else if(fraction >= 0 && fraction < 1) { //for numbers between 0 inclusive and 1 exclusive
            while(fractionChanged < 1) {
                fractionChanged = fractionChanged * 2;
                exponent--;
            }

            valInExpField = bias + exponent;

            findBinaryForWholeNum(fractionChanged, valInExpField, exponentNumBits, binaryArr);
            //check for subnormals
            if(binaryArr[0] == 0 && binaryArr[1] == 0 && binaryArr[2] == 0 && binaryArr[3] == 0) {
                while ((fractionChanged != 0) && (binaryLength2 < fracNumBits)) {
                    binaryLength2++;
                    remainder2 = fmod(fractionChanged, 2);
                    decBinaryArr[indexOfDecArr] = remainder2;
                    indexOfDecArr++;
                    fractionChanged = fractionChanged / 2;
                }

                if(binaryLength2 > fracNumBits || fractionChanged != 0) {
                    for(int i = 0; i < fracNumBits; i++) {
                        decBinaryArr[i] = 1;
                    }
                }
                printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decBinaryArr);
            }
            else { //not a subnormal
                fractionChanged = fractionChanged - 1;

                findBinaryforFrac(fractionChanged, fracNumBits, decBinaryArr);

                if(decBinaryArr[fracNumBits] == 0) {
                    printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decBinaryArr);
                }
                else if(decBinaryArr[fracNumBits] == 1 && decBinaryArr[fracNumBits+1] == 0 && decBinaryArr[fracNumBits+2] == 0) {
                    int count = 0;
                    for(int i = 0; i < fracNumBits; i++) {
                        if(decBinaryArr[i] == 1) {
                            count++;
                        }
                    }
                    if(decBinaryArr[fracNumBits-1] == 1 && count < fracNumBits) {
                        addOne(fracNumBits, decBinaryArr, decArrRounded);
                        printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decArrRounded);
                    }
                    else if(count == fracNumBits) { 
                        //if everything one, add one to exponent field
                        addOne(fracNumBits, decBinaryArr, decArrRounded);
                        addOneForExp(exponentNumBits, binaryArr, binArrRounded);
                        printOutputForPos(exponentNumBits, fracNumBits, binArrRounded, decArrRounded);
                    }                    
                    else {
                        printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decBinaryArr);
                    }
                }
                else {
                    int count = 0;
                    for(int i = 0; i < fracNumBits; i++) {
                        if(decBinaryArr[i] == 1) {
                            count++;
                        }
                    }
                    if(count == fracNumBits) { 
                        //if everything one, add one to exponent field
                        addOne(fracNumBits, decBinaryArr, decArrRounded);
                        addOneForExp(exponentNumBits, binaryArr, binArrRounded);
                        printOutputForPos(exponentNumBits, fracNumBits, binArrRounded, decArrRounded);
                    }
                    else {
                        addOne(fracNumBits, decBinaryArr, decArrRounded);
                        printOutputForPos(exponentNumBits, fracNumBits, binaryArr, decArrRounded);
                    }
                }
            }
              
        }
        else { //negative number

            fractionChanged = fractionChanged * (-1);

            if(fractionChanged < 1) {
                while(fractionChanged < 1) {
                    fractionChanged = fractionChanged * 2;
                    exponent--;
                }    
            }
            else {
                while((fractionChanged / 2) >= 1) {
                    fractionChanged = fractionChanged / 2;
                    exponent++;
                } 
            }


            fractionChanged = fractionChanged - 1;
            valInExpField = bias + exponent;

            findBinaryForWholeNum(fractionChanged, valInExpField, exponentNumBits, binaryArr);
            findBinaryforFrac(fractionChanged, fracNumBits, decBinaryArr);

            if(decBinaryArr[fracNumBits] == 0) {
                printOutputForNeg(exponentNumBits, fracNumBits, binaryArr, decBinaryArr);
            }
            else if(decBinaryArr[fracNumBits] == 1 && decBinaryArr[fracNumBits+1] == 0 && decBinaryArr[fracNumBits+2] == 0) {
                int count = 0;
                for(int i = 0; i < fracNumBits; i++) {
                    if(decBinaryArr[i] == 1) {
                        count++;
                    }
                }
                if(decBinaryArr[fracNumBits - 1] == 1 && count < fracNumBits) {
                    addOne(fracNumBits, decBinaryArr, decArrRounded); 
                    printOutputForNeg(exponentNumBits, fracNumBits, binaryArr, decArrRounded);
                }
                else if(count == fracNumBits) { 
                    //if everything one, add one to exponent field
                    addOne(fracNumBits, decBinaryArr, decArrRounded);
                    addOneForExp(exponentNumBits, binaryArr, binArrRounded);
                    printOutputForNeg(exponentNumBits, fracNumBits, binArrRounded, decArrRounded);
                }
                else {
                    printOutputForNeg(exponentNumBits, fracNumBits, binaryArr, decBinaryArr);
                }
            }
            else {
                int count = 0;
                for(int i = 0; i < fracNumBits; i++) {
                    if(decBinaryArr[i] == 1) {
                        count++;
                    }
                }
                if(count == fracNumBits) { 
                    //if everything one, add one to exponent field
                    addOne(fracNumBits, decBinaryArr, decArrRounded);
                    addOneForExp(exponentNumBits, binaryArr, binArrRounded);
                    printOutputForNeg(exponentNumBits, fracNumBits, binArrRounded, decArrRounded);
                }
                else {
                    addOne(fracNumBits, decBinaryArr, decArrRounded);
                    printOutputForNeg(exponentNumBits, fracNumBits, binaryArr, decArrRounded);
                }
            }            
            
        }

    }

    fclose(fp1);

}

