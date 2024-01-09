#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int findDet(int size, int **matrix) {
    int det = 0;
    int **mat = matrix;
    if(size == 1) {
        det = mat[0][0];
    }
    if(size == 2) {
        det = (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]);
    }
    if(size == 3) {
            det = mat[0][0] * ((mat[1][1]*mat[2][2]) - (mat[2][1]*mat[1][2])) - mat[0][1]*(mat[1][0]*mat[2][2] - mat[2][0]*mat[1][2]) + mat[0][2]*(mat[1][0]*mat[2][1] - mat[2][0]*mat[1][1]);
    }

    return det;
}


int main(int argc, char* argv[argc + 1]) {
    int **matrix;
    FILE *fp = fopen(argv[1], "r");
    if(!fp) {
        printf("error\n");
        return EXIT_SUCCESS;
    }
    int num;
    int size = 0;
    int counter = 0;

    while(fscanf(fp, "%d", &num) == 1) {
        counter++;
        if(counter == 1) {
            size = num;
        }
        else {
            matrix = malloc(size * sizeof(int*));
            for(int i = 0; i < size; i++) {
                matrix[i] = malloc(size * sizeof(int));
            }
            for(int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    matrix[i][j] = num;
                    fscanf(fp, "%d", &num);
                }
            } 
        }
    }
    
    printf("%d\n", findDet(size, matrix));

    for(int i =0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);


    return EXIT_SUCCESS; 

}










 
