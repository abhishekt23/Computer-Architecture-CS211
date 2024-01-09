#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int main(int argc, char* argv[argc + 1]) {
    int num = atoi(argv[1]);
    if(num % 2 == 0) {
        printf("error");
        return EXIT_SUCCESS;
    }
    else {            
        int** mat = malloc(num * sizeof(int*));
        for(int i = 0; i < num; i++) {
                mat[i] = malloc(num * sizeof(int*));
            }
            for(int i = 0; i < num; i++) {
                for(int j = 0; j < num; j++) {
                    mat[i][j] = 0;
                }
            }

        int r = 0;
        int c = num / 2;
        int tempR;
        int tempC;
        for(int i = 1; i <= num * num; i++) {
            mat[r][c] = i;
            tempR = r--;
            tempC = c++;

            if(r < 0) {
                r = num - 1;
            }
            if(r >= num) {
                r = 0;
            }
            if(c >= num) {
                c = 0;
            }
            if ((mat[r][c] != 0)) {
                c = tempC;
                r = tempR + 1;
            }
        }

        for(int x = 0; x < num; x++) {
            for(int y = 0; y < num ; y++) {
                printf("%d\t", mat[x][y]);
            }
            printf("\n");
        }

        for(int z = 0; z < num; z++) {
            free(mat[z]);
        }
        free(mat);
            
        }
    return EXIT_SUCCESS; 
}










 
