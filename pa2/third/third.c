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

char* visited;
char** queue;
int front = -1;
int back = -1;


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

bool isEmpty() {
    if(front == -1 && back == -1) {
        return true;
    }
    else {
        return false;
    }
}

void enqueue(char* name) {
    if(back == numVert-1) {
        return;
    }
    else if(isEmpty()) {
        front = 0;
        back = 0;
        queue[back] = name;
    }
    else {
        back++;
        queue[back] = name;
    }
}

char* dequeue() {
    if(isEmpty()) {
        return NULL;
    }
    else if(front == back) {
        char* var = queue[front];
        front = -1;
        back = -1;
        return var;
    }
    else {
        char* var = queue[front];
        front++;
        return var;
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


void BFS(char* start) {
    setVisitIndex(start);
    enqueue(start);
    while(!isEmpty()) {
        char* vert = malloc(80);
        strcpy(vert, dequeue());
        printf("%s ", vert);
        setVisitIndex(vert);
        struct Node* ptr = arr[getVisitIndex(vert)];
        while(ptr != NULL) {
            if(visited[getVisitIndex(ptr->name)] != 1) {
                setVisitIndex(ptr->name);
                enqueue(ptr->name);
            }
            ptr = ptr->next;
        }
        free(vert);
    }
    printf("\n");
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


    char beg[80];
    char end[80];
    arr = malloc(numVert * sizeof(struct Node));
    queue = malloc(numVert * sizeof(char*));
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

    while(fscanf(fp1, "%s %s", beg, end) != EOF) {
        edgeAdd(beg, end);
    }


    while(fscanf(fp2, "%s", query) != EOF) {
        BFS(query);
        for(int i = 0; i < numVert; i++) {
            visited[i] = 0;
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
    free(queue);
    free(visited);

    fclose(fp1);
    fclose(fp2);
    return EXIT_SUCCESS; 
}
 
