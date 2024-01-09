#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Node {
    int data;
    struct Node *next;
};

void insert(struct Node **head, int data);
bool delete(struct Node **head, int data);
void freeMemory(struct Node *head);



int main(int argc, char* argv[argc + 1]) {
    struct Node *head = NULL;
    FILE *fp = fopen(argv[1], "r");
    if(!fp) {
        printf("error\n");
        return EXIT_SUCCESS;
    }
    char arr[200];
    int count = 0;
    char first;
    int x;
    while(fscanf(fp, "%s", arr) == 1) {
        if(arr[0] == 'I' || arr[0] == 'D') {
            first = arr[0];    
        }
        if((first == 'I') && (count % 2 == 1)) {
            x = atoi(arr);
            insert(&head, x);
            struct Node *printer = head;
            if(printer == NULL) {
                printf("EMPTY");
            }
            while(printer != NULL) {
                if(printer -> next != NULL) {
                    printf("%d ", printer -> data);
                }
                else {
                    printf("%d", printer -> data);
                }
                printer = printer -> next;
            }
            printf("\n");
        }
        if((first == 'D') && (count % 2 == 1)) {
            x = atoi(arr);
            delete(&head, x);
            struct Node *printer = head;
            if(printer == NULL) {
                printf("EMPTY");
            }
            while(printer != NULL) {
                if(printer -> next != NULL) {
                    printf("%d ", printer -> data);
                }
                else {
                    printf("%d", printer -> data);
                }
                printer = printer -> next;
            }
            printf("\n");
        }
        count++;
    }

    if(head != NULL) {
        while(head -> next != NULL) {
            struct Node *ptr = head;
            ptr = head;
            head = head -> next;
            free(ptr);
        }
    }
    free(head);
    fclose(fp);
    return EXIT_SUCCESS; 
}

void insert(struct Node **head, int data) {
    struct Node *currNode;
    struct Node *new = malloc(sizeof(struct Node));
    new -> data = data;
    new -> next = NULL;
    int num = data;
    struct Node *ptr = *head;
    if(ptr == NULL || num < ptr -> data) {
        new -> next = *head;
        *head = new;
        ptr = *head;
    }
    else {
        currNode = *head;
        while(currNode -> next != NULL && currNode -> next -> data <= data) {
            currNode = currNode -> next;
        }
        if(currNode -> data == data) {
            free(new);
            return;
        }
        else {
            new -> next = currNode -> next;
            currNode -> next = new;       
        }
    }
}

bool delete(struct Node **head, int data) {
    struct Node* prev = *head;                                
    struct Node* current = *head;

    if(current -> data == data) {
        *head = current -> next;
        free(current);
        return true;
    }

    current = current -> next;

    while(current) {
        if(current -> data == data) {
            prev -> next = current -> next;
            free(current);
            return true;
        }
        prev = current;
        current = current -> next;
    }
    return false;
}

void freeMemory(struct Node *head) {
    struct Node *ptr;
    while(head) {
        ptr = head;
        head = head -> next;
        free(ptr);
    }
}




 
