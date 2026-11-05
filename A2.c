#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXURL 50

typedef struct StackNode{
    char url[MAXURL];
    struct StackNode* next;
} StackNode;

typedef struct QueueNode{
    char url[MAXURL];
    struct QueueNode* front;
    struct QueueNode* rear;
} QueueNode;


void push(StackNode** stack, char* newUrl);
char* pop(StackNode** stack);
char* peekStack(StackNode** stack);
bool isEmptyStack(StackNode** stack);

void enqueue(QueueNode** queue, char* newUrl);
char* dequeue(QueueNode** queue);
char* peekQueue(QueueNode** queue);
bool isEmptyQueue(QueueNode** queue);


int main() {
    
    QueueNode* queue = NULL;
    StackNode* backStack = NULL;
    StackNode* forwardStack = NULL;
    QueueNode* current = NULL;

    int choice = 0;


        while (1) {
            printf("Menu:\n");
            printf("1. Visit New Web Page\n");
            printf("2. Navigate Backward\n");
            printf("3. Navigate Forward\n");
            printf("4. Display Current Page\n");
            printf("5. Browsing History Log\n");
            printf("6. Exit\n");
            choice = getchar();
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {       //clear input buffer
                continue;
            }

            switch (choice) {
                case '1':
                    printf("Enter the URL of the new web page: ");
                    char newUrl[MAXURL];
                    if (fgets(newUrl, sizeof(newUrl), stdin) != NULL) {
                        if (!strchr(newUrl, '\n')) {
                            // consume rest of chars up to '\n'
                            int ch;
                            while (((ch = getchar()) != '\n') && ch != EOF)
                                continue;
                        }
                    }
                    enqueue(&queue, newUrl);
                    push(&backStack, newUrl);
                    break;
                case '2': 
                    if (isEmptyStack(&backStack)) {
                        break;
                    }
                    dequeue(&queue);
                    push(&forwardStack, peekStack(&backStack));
                    printf("Forward page: %s", peekStack(&backStack));
                    pop(&backStack);
                    printf("Current Page: %s\n", peekStack(&backStack));
                    break;
                case '3':
                    if (isEmptyStack(&forwardStack)) {
                        break;
                    }
                    printf("Forward page: %s", peekStack(&forwardStack));
                    push(&backStack, peekStack(&forwardStack));
                    dequeue(&queue);
                    printf("Current Page: %s\n", peekStack(&backStack));
                    break;
                case '4':
                    if (isEmptyQueue(&queue)) {
                        printf("Queue is empty.\n");
                        break;
                    }
                    printf("Current Page: %s\n", peekQueue(&queue)); 
                    break;
                case '5':
                   current = queue;
                   while (current != NULL) {
                       printf("%s\n", current->url);
                       current = current->front;
                   }
                   break;
                case '6':
                    while (!isEmptyStack(&backStack)) {
                        pop(&backStack);
                    }
                    while (!isEmptyStack(&forwardStack)) {
                        pop(&forwardStack);
                    }
                    while (!isEmptyQueue(&queue)) {
                        dequeue(&queue);
                    }
                    printf("Exiting the program.\n");
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
                }

        }

}



void push(StackNode** stack, char* newUrl){
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!isEmptyStack(stack)) {
        newNode->next = *stack;
    }
    else {
        newNode->next = NULL;
    }
    strncpy(newNode->url, newUrl, MAXURL);
    *stack = newNode; 
}

char* pop(StackNode** stack){
    if (isEmptyStack(stack)) {
        return NULL;
    }
    StackNode* temp = *stack;
    *stack = (*stack)->next;
    char* url = (char*)malloc(MAXURL * sizeof(char));
    strncpy(url, temp->url, MAXURL);
    free(temp);
    return url;
}

char* peekStack(StackNode** stack){
    if (isEmptyStack(stack)) {
        return NULL;
    }
    return (*stack)->url;
}

bool isEmptyStack(StackNode** stack){
    return *stack == NULL;
}

void enqueue(QueueNode** queue, char* newUrl){
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    strncpy(newNode->url, newUrl, MAXURL);
    newNode->front = NULL;
    if (*queue == NULL) {
        *queue = newNode;
    } 
    else {
        QueueNode* current = *queue;
        while (current->front != NULL) {
            current = current->front;
        }
        current->front = newNode;
    }
}

char* dequeue(QueueNode** queue){
    if (isEmptyQueue(queue)){
        return NULL;
    }
    else {
        QueueNode* temp = *queue;
        *queue = (*queue)->front;
        char* url = (char*)malloc(MAXURL * sizeof(char));
        strncpy(url, temp->url, MAXURL);
        free(temp);
        return url;
    }
}

char* peekQueue(QueueNode** queue){
    if (isEmptyQueue(queue)){
        return NULL;
    }
    else {
        return (*queue)->url;
    }
}

bool isEmptyQueue(QueueNode** queue){
    return *queue == NULL;
}