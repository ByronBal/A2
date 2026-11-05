#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXURL 50 // Maximum length of a URL

typedef struct StackNode{
    char url[MAXURL];
    struct StackNode* next;
} StackNode;

typedef struct QueueNode{
    char url[MAXURL];
    struct QueueNode* front;
    struct QueueNode* rear;
} QueueNode;

// Function prototypes
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
            choice = getchar(); // Read the user input
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {   // Clear the input buffer
                continue;
            }

            switch (choice) {
                case '1':   // Visit New Web Page
                    printf("Enter the URL of the new web page: ");
                    char newUrl[MAXURL];
                    if (fgets(newUrl, sizeof(newUrl), stdin) != NULL) {     // Read the url from the user
                        if (!strchr(newUrl, '\n')) {
                            int ch;
                            while (((ch = getchar()) != '\n') && ch != EOF) {   // Clear the input buffer
                                continue;
                            }
                        }
                    }
                    enqueue(&queue, newUrl);    // Add the new url to the queue from the user
                    push(&backStack, newUrl);   // Add the new url to the back stack
                    break;
                case '2':   // Navigate Backward
                    if (isEmptyStack(&backStack)) {     // Check if the back stack is empty 
                        break;
                    }
                    dequeue(&queue);    // Remove the current page from the queue
                    push(&forwardStack, peekStack(&backStack));   // Add the current page to the forward stack
                    printf("Forward page: %s", peekStack(&backStack));  // I left this in from testing, but it is not necessary for the program to function
                    pop(&backStack);    // Remove the current page from the back stack
                    printf("Current Page: %s\n", peekStack(&backStack));    // I left this in from testing, but it is not necessary for the program to function
                    break;
                case '3':   // Navigate Forward
                    if (isEmptyStack(&forwardStack)) {  // Check if the forward stack is empty
                        break;
                    }
                    printf("Forward page: %s", peekStack(&forwardStack));   // I left this in from testing, but it is not necessary for the program to function
                    push(&backStack, peekStack(&forwardStack));   // Add the current page to the back stack
                    dequeue(&queue);    // Remove the current page from the queue
                    printf("Current Page: %s\n", peekStack(&backStack));    // I left this in from testing, but it is not necessary for the program to function
                    break;
                case '4':   // Display Current Page
                    if (isEmptyQueue(&queue)) { // Check if the queue is empty
                        printf("Queue is empty.\n");
                        break;
                    }
                    printf("Current Page: %s\n", peekQueue(&queue)); 
                    break;
                case '5':   // Browsing History Log
                   current = queue; // Set current to the front of the queue
                   while (current != NULL) {    // Loop through the queue and print the urls
                       printf("%s\n", current->url);
                       current = current->front;    // Move to the next node in the queue
                   }
                   break;
                case '6':   // Exit
                    while (!isEmptyStack(&backStack)) { // Clear the back stack
                        pop(&backStack);
                    }
                    while (!isEmptyStack(&forwardStack)) {  // Clear the forward stack
                        pop(&forwardStack);
                    }
                    while (!isEmptyQueue(&queue)) { // Clear the queue
                        dequeue(&queue);
                    }
                    printf("Exiting the program.\n");
                    return 0;
                default:    // Invalid choice
                    printf("Invalid choice. Please try again.\n");
                }

        }

}


// FUNCTION		: push
// DESCRIPTION	: Adds to the top of the stack, if the stack is empty, it will set the next pointer to NULL
// PARAMETERS	: StackNode** stack
//              : char* newUrl
// RETURNS		: void
void push(StackNode** stack, char* newUrl){
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode)); // Allocate memory for a new stack node
    if (!isEmptyStack(stack)) { // Check if the stack is not empty
        newNode->next = *stack; // Set the next pointer of the new node to the current top of the stack
    }
    else {
        newNode->next = NULL;
    }
    strncpy(newNode->url, newUrl, MAXURL);  // Copy the new url into the new node
    *stack = newNode;   // Set the new node as the top of the stack
}

// FUNCTION		: pop
// DESCRIPTION	: Takes off the top of the stack, using a temp to keep track of the old one
// PARAMETERS	: StackNode** stack
// RETURNS		: char* - returns the url of the popped node
char* pop(StackNode** stack){
    if (isEmptyStack(stack)) {  // Check if the stack is empty
        return NULL;
    }
    StackNode* temp = *stack;   // Store the current top of the stack in a temp variable
    *stack = (*stack)->next;    // Set the top of the stack to the next node
    char* url = (char*)malloc(MAXURL * sizeof(char));   // Allocate memory for the url to be returned
    strncpy(url, temp->url, MAXURL);    // Copy the url from the temp node to the url variable
    free(temp); // Free the memory of the temp node
    return url; // Return the url of the popped node
}

// FUNCTION		: peekStack
// DESCRIPTION	: Returns the url of the top of the stack without removing it
// PARAMETERS	: StackNode** stack
// RETURNS		: char* - returns the url of the top node
char* peekStack(StackNode** stack){
    if (isEmptyStack(stack)) {  // Check if the stack is empty
        return NULL;
    }
    return (*stack)->url;   // Return the url of the top node
}

// FUNCTION		: isEmptyStack
// DESCRIPTION	: Is used to verify whether the stack is null
// PARAMETERS	: StackNode** stack
// RETURNS		: bool
bool isEmptyStack(StackNode** stack){
    return *stack == NULL;
}

// FUNCTION		: enqueue
// DESCRIPTION	: Adds a node to the queue
// PARAMETERS	: QueueNode** queue
//              : char* newUrl
// RETURNS		: void
void enqueue(QueueNode** queue, char* newUrl){
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    strncpy(newNode->url, newUrl, MAXURL);  // Copy the new url into the new node
    newNode->front = NULL;  // Set the front pointer of the new node to NULL
    if (*queue == NULL) {   // Check if the queue is empty
        *queue = newNode;
    } 
    else {
        QueueNode* current = *queue;    // Set current to the front of the queue
        while (current->front != NULL) {    // Loop through the queue until the end is reached
            current = current->front;
        }
        current->front = newNode;   // Set the front pointer of the last node to the new node
    }
}

// FUNCTION		: dequeue
// DESCRIPTION	: Removes a node from the queue
// PARAMETERS	: QueueNode** queue
// RETURNS		: char* - returns the url of the dequeued node
char* dequeue(QueueNode** queue){
    if (isEmptyQueue(queue)){   // Check if the queue is empty
        return NULL;
    }
    else {
        QueueNode* temp = *queue;   // Store the current front of the queue in a temp variable
        *queue = (*queue)->front;   // Set the front of the queue to the next node
        char* url = (char*)malloc(MAXURL * sizeof(char));   // Allocate memory for the url to be returned
        strncpy(url, temp->url, MAXURL);    // Copy the url from the temp node to the url variable
        free(temp); // Free the memory of the temp node
        return url; // Return the url of the dequeued node
    }
}

// FUNCTION		: peekQueue
// DESCRIPTION	: Returns the url of the front of the queue without removing it
// PARAMETERS	: QueueNode** queue
// RETURNS		: char* - returns the url of the front node
char* peekQueue(QueueNode** queue){
    if (isEmptyQueue(queue)){   // Check if the queue is empty
        return NULL;
    }
    else {
        return (*queue)->url;   // Return the url of the front node
    }
}

// FUNCTION		: isEmptyQueue
// DESCRIPTION	: Is used to verify whether the queue is null
// PARAMETERS	: QueueNode** queue
// RETURNS		: bool
bool isEmptyQueue(QueueNode** queue){
    return *queue == NULL;
}