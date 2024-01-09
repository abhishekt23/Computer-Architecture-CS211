#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
    char name[80];
    struct Node *next;
    int weight;
};

struct Node** arr;
int numVert;

void edgeAdd(char* one, char* two, int* w) {

    struct Node* newNode;
    int weigh = *w;

    for(int i = 0; i < numVert; i++) {
        char* temp = arr[i]->name;

        if(strcmp(one, temp) == 0) {
            newNode = malloc(sizeof(struct Node));
            newNode->weight = weigh;
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
    int nodeWeight;

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

    while(fscanf(fp1, "%s %s %d", beg, end, &nodeWeight) != EOF) {
        edgeAdd(beg, end, &nodeWeight);
    }


    while(fscanf(fp2, "%s", query) != EOF) {
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

        if(query[0] == 'i') {
            int count = 0;
            fscanf(fp2, "%s", qVertex);
            for(int i = 0; i < numVert; i++) {
                struct Node* ptr = arr[i]->next;
                while(ptr != NULL) {
                    if(strcmp(ptr->name, qVertex) == 0) {
                        count++;
                    }
                    ptr = ptr->next;
                }
                
            }
            printf("%d\n", count);
        }

        if(query[0] == 'o') {
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
 
