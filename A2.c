#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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


void push(StackNode* stack, char* newUrl);
char* pop(StackNode* stack);
char* peek(StackNode* stack);
bool isEmpty(StackNode* stack);

void enqueue(QueueNode* queue, char* newUrl);
char* dequeue(QueueNode* queue);
char* peek(QueueNode* queue);
bool isEmpty(QueueNode* queue);


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

            switch (choice) {
                case '1':
                    printf("Enter the URL of the new web page: ");
                    char newUrl[MAXURL];
                    fgets(newUrl, sizeof(MAXURL), stdin);
                    enqueue(&queue, newUrl);
                    push(&backStack, newUrl);
                    break;
                case '2':
                    dequeue(&queue);
                    push(&forwardStack, peek(&backStack));
                    pop(&backStack);
                    break;
                case '3':
                    pop(&forwardStack);
                    push(&backStack, peek(&forwardStack));
                    dequeue(&queue);
                    break;
                case '4':
                    printf("Current Page: %s", peek(&queue)); //////circle back aorund
                    break;
                case '5':
                    current = queue;
                    while (current != NULL) {
                        printf("%s", peek(&queue));
                        current = current->front;   // circle back around
                    }
                    break;
                case '6':
                    printf("Exiting the program.\n");
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
            }


}




void push(StackNode* stack, char* newUrl){
    
}