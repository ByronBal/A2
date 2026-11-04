#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct StackNode{
    char url[50];
} StackNode;

typedef struct QueueNode{
    char url[50];
    struct QueueNode* next;
} QueueNode;

void menu();

void push(Stack* stack, char* newUrl);
char* pop(Stack* stack);
char* peek(Stack* stack);
bool isEmpty(Stack* stack);

int main() {
    
    menu();
}

void menu() {
    printf("Menu:\n");
    printf("1. Visit New Web Page\n");
    printf("2. Navigate Backward\n");
    printf("3. Navigate Forward\n");
    printf("4. Display Current Page\n");
    printf("5. Browsing History Log\n");
    printf("6. Exit\n");
}