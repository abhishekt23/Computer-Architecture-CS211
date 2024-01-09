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

char* visited;

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

void setVisitIndex(char* start) {
    for(int i = 0; i < numVert; i++) {
        if(strcmp(arr[i]->name, start) == 0) {
            visited[i] = 1;
        }
    }
}

int getVisitIndex(char* start) {
    int index;
    for(int i = 0; i < numVert; i++) {
        if(strcmp(arr[i]->name, start) == 0) {
            index = i;
        }
    }
    return index;
}

void DFS(char* start, char* visited) {
    setVisitIndex(start);
    printf("%s ", start);

    struct Node* ptr = arr[getVisitIndex(start)];
    while(ptr != NULL) {
        if(visited[getVisitIndex(ptr->name)] != 1) {
            DFS(ptr->name, visited);
        }
        ptr = ptr->next;
    }
}

void dfsHelper() {
    for(int i = 0; i < numVert; i++) {
        visited[i] = 0;
    }

    for(int i = 0; i < numVert; i++) {
        if(visited[i] != 1) {
            DFS(arr[i]->name, visited);
        }
    }
}



int main(int argc, char* argv[argc + 1]) {
    FILE *fp1 = fopen(argv[1], "r");
    if(!fp1) {
        printf("error\n");
        return EXIT_SUCCESS;
    }

    fscanf(fp1, "%d", &numVert);
    char vertex[200];

    char beg[80];
    char end[80];
    int nodeWeight;

    arr = malloc(numVert * sizeof(struct Node));
    visited = malloc(numVert * sizeof(int));

    for(int i = 0; i < numVert; i++) { 
        fscanf(fp1, "%s", vertex);
        arr[i] = malloc(sizeof(struct Node));
        strcpy(arr[i]->name, vertex);
        arr[i]->next = NULL;
        visited[i] = 0;

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
    
    /*
    for(int i = 0; i < numVert; i++) {
        struct Node* ptr = arr[i];
        while(ptr != NULL)  {
            printf("%s ", ptr->name);
            ptr = ptr->next;
        }
        printf("\n");
 
    }
    */
    
    //printf("\n");
    dfsHelper();

    for(int i = 0; i < numVert; i++) {
        struct Node* temp;
        while(arr[i] != NULL) {
            temp = arr[i];
            arr[i] = arr[i]->next;
            free(temp);
        }
    }

    free(arr);
    free(visited);

    fclose(fp1);
    return EXIT_SUCCESS; 
}
 
