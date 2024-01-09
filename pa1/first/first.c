#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



int main(int argc, char* argv[argc + 1]) {
    FILE *fp = fopen(argv[1], "r");
    int num = 0;
    fscanf(fp, "%d", &num);
    int lines = 0; 
    int number;
    while(lines < num) {
        fscanf(fp, "%d", &number);
        bool prime = true;
        for(int i = 2; i <= number/2; i++) {
            if(number <= 1) {
                prime = false;
                printf("no\n");
                break;
            } 
            if(number % i == 0) {
                prime = false;
                printf("no\n");
                break;
            }
            if(i == number/2) {
                number = number / 10;
                i = 1;
            }

        }
        if(prime == true) {
            printf("yes\n");
        }
        lines++;
    }

  


    fclose(fp);
    return EXIT_SUCCESS; 
}
 
