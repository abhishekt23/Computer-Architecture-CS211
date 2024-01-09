#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    char name[80];
    struct Node *next;
};

struct Node** arr;
int numVert;

void edgeAdd(char* one, char* two) {

    struct Node* newNode;
    struct Node* newNode2;

    for(int i = 0; i < numVert; i++) {
        char* temp = arr[i]->name;

        if(strcmp(one, temp) == 0) {
            newNode = malloc(sizeof(struct Node));
            strcpy(newNode->name, two);
            if(arr[i]->next == NULL) {
                newNode->next = NULL;
                arr[i]->next = newNode;
            }
            else if(strcmp(newNode->name, arr[i]->next->name) < 0) {
                newNode->next = arr[i]->next;
                arr[i]->next = newNode;
            }
            else {
                struct Node* ptr = arr[i]->next;
                while(ptr->next != NULL && (strcmp(newNode->name, ptr->next->name) > 0)) {
                    ptr = ptr->next;
                }
                newNode->next = ptr->next;
                ptr->next = newNode;
            }
            
        }
        if(strcmp(two, temp) == 0) {
            newNode2 = malloc(sizeof(struct Node));
            strcpy(newNode2->name, one);
            if(arr[i]->next == NULL) {
                newNode2->next = NULL;
                arr[i]->next = newNode2;
            }
            else if(strcmp(newNode2->name, arr[i]->next->name) < 0) {
                newNode2->next = arr[i]->next;
                arr[i]->next = newNode2;
            }
            else {
                struct Node* ptr2 = arr[i]->next;
                while(ptr2->next != NULL && (strcmp(newNode2->name, ptr2->next->name) > 0)) {
                    ptr2 = ptr2->next;
                }
                newNode2->next = ptr2->next;
                ptr2->next = newNode2;
            }

        }
    }
}


int main(int argc, char* argv[argc + 1]) {
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    if(!fp1) {
        printf("error\n");
        return EXIT_SUCCESS;
    }
    if(!fp2) {
        printf("error\n");
        return EXIT_SUCCESS;
    }

    fscanf(fp1, "%d", &numVert);
    char vertex[200];
    char query[200];
    char qVertex[200];

    char beg[80];
    char end[80];
    arr = malloc(numVert * sizeof(struct Node));
    for(int i = 0; i < numVert; i++) { 
        fscanf(fp1, "%s", vertex);
        arr[i] = malloc(sizeof(struct Node));
        strcpy(arr[i]->name, vertex);
        arr[i]->next = NULL;
    }

    //Bubble Sort on Head Nodes of array
    struct Node* temp;
    for(int i = 0; i < numVert - 1; i++) {
        for(int j = 0; j < numVert - i - 1; j++) {
            if(strcmp(arr[j]->name, arr[j+1]->name) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    while(fscanf(fp1, "%s %s", beg, end) != EOF) {
        edgeAdd(beg, end);
    }


    while(fscanf(fp2, "%s", query) != EOF) {
        if(query[0] == 'd') {
            int count = 0;
            fscanf(fp2, "%s", qVertex);
            for(int i = 0; i < numVert; i++) {
                if(strcmp(arr[i]->name, qVertex) == 0) {
                    struct Node* ptr = arr[i]->next;
                    while(ptr != NULL) {
                        count++;
                        ptr = ptr->next;
                    }
                }
            }
            printf("%d\n", count);
        }
        if(query[0] == 'a') {
            fscanf(fp2, "%s", qVertex);
            for(int i = 0; i < numVert; i++) {
                if(strcmp(arr[i]->name, qVertex) == 0) {
                    struct Node* ptr2 = arr[i];
                    while(ptr2->next != NULL) {
                        ptr2 = ptr2->next;
                        printf("%s ", ptr2->name);
                    }
                }
            }
            printf("\n");
        }
    }

    for(int i = 0; i < numVert; i++) {
        struct Node* temp;
        while(arr[i] != NULL) {
            temp = arr[i];
            arr[i] = arr[i]->next;
            free(temp);
        }
    }

    free(arr);

    fclose(fp1);
    fclose(fp2);
    return EXIT_SUCCESS; 
}
 
