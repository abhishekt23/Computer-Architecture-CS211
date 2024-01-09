#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Node {
    int data;
    struct Node *next;
};

void enqueue(struct Node **head, int x);
void push(struct Node **head, int x);
struct Node* pop(struct Node **head);




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
    char second;
    int x;
    while(fscanf(fp, "%s", arr) == 1) {
        if(arr[0] == 'P' || arr[0] == 'E') {
            first = arr[0];  
            second = arr[1];  
        }
        if((first == 'P' && second == 'U') && (atoi(arr))) {
            x = atoi(arr);
            push(&head, x);
            struct Node *printer = head;
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
        
        if(first == 'P' && second == 'O') {
            head = pop(&head);
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

        if(first == 'E' && (atoi(arr))) {
            x = atoi(arr);
            enqueue(&head, x);
            struct Node *printer = head;
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

    struct Node *ptr;
    while(head != NULL) {
        ptr = head;
        head = head -> next;
        free(ptr);
    }
    free(head);
    fclose(fp);
    return EXIT_SUCCESS; 
}

void enqueue(struct Node **head, int x) {
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    struct Node *currNode = *head;
    new -> data = x;
    new -> next = NULL;
    if(*head == NULL) {
        (*head) = new;
    }
    else {
        while(currNode -> next != NULL) {
            currNode = currNode -> next;
        }
        currNode -> next = new;
    }
    return;
}

void push(struct Node **head, int x){
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new -> data = x;
    new -> next = *head;
    *head = new;
}


struct Node* pop(struct Node **head) {
    struct Node *first = *head;
    if(first == NULL) {
        ;
    }
    else {
        struct Node *new = first;
        first = first -> next;
        free(new);
        new = NULL;
    }

    return first;
}




 
