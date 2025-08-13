#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    char arr[MAX_SIZE];
    int top;
} Stack_char;

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack_int;

void initialize(Stack_char *stack) {
    stack->top = -1;
}

void initialize_int(Stack_int *stack) {
    stack->top = -1;
}

bool isEmpty(Stack_char *stack) {
    return stack->top == -1;
}

bool isEmpty_int(Stack_int *stack) {
    return stack->top == -1;
}

bool isFull(Stack_char *stack) {
    return stack->top == MAX_SIZE - 1;
}

bool isFull_int(Stack_int *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack_char *stack, char value) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
    // printf("Pushed %c onto the stack\n", value);
}

void push_int(Stack_int *stack, int value) {
    if (isFull_int(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
    // printf("Pushed %c onto the stack\n", value);
}

char pop(Stack_char *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return 'X';
    }
    char popped = stack->arr[stack->top];
    stack->top--;
    // printf("Popped %c from the stack\n", popped);
    return popped;
}

char pop_int(Stack_int *stack) {
    if (isEmpty_int(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    char popped = stack->arr[stack->top];
    stack->top--;
    // printf("Popped %d from the stack\n", popped);
    return popped;
}

char peek(Stack_char *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return 'X';
    }
    return stack->arr[stack->top];
}

char peek_int(Stack_int *stack) {
    if (isEmpty_int(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int main() {
    Stack_char op;
    initialize(&op);

    Stack_int solving;
    initialize_int(&solving);

    char expression[] = "3+4*7";
    for (int i = 0; i < 5; i++) {
        char c = expression[i];
        if (isalnum(c)) {
            int num = c - '0';
            push_int(&solving, num);
        } else {
            while (!isEmpty(&op) && prec(c) <= prec(peek(&op))) {
                // push(&solving, peek(&op));
                // pop(&op);
                int val1 = pop_int(&solving);
                int val2 = pop_int(&solving);
                printf("%d%c%d\n", val2, peek(&op), val1);

                if (peek(&op) == '+') {
                    push_int(&solving, val2 + val1);
                } else if (peek(&op) == '-') {
                    push_int(&solving, val2 - val1);
                } else if (peek(&op) == '*') {
                    push_int(&solving, val2 * val1);
                } else if (peek(&op) == '/') {
                    push_int(&solving, val2 / val1);
                }
                pop(&op);
            }
            push(&op, c);
        }
    }

    while (!isEmpty(&op)) {
        // push(&solving, peek(&op));
        // pop(&op);
        int val1 = pop_int(&solving);
        int val2 = pop_int(&solving);
        printf("%d%c%d\n", val2, peek(&op), val1);

        if (peek(&op) == '+') {
            push_int(&solving, val2 + val1);
        } else if (peek(&op) == '-') {
            push_int(&solving, val2 - val1);
        } else if (peek(&op) == '*') {
            push_int(&solving, val2 * val1);
        } else if (peek(&op) == '/') {
            push_int(&solving, val2 / val1);
        }
        pop(&op);
    }

    while (!isEmpty_int(&solving)) {
        printf("%d\n", peek_int(&solving));
        pop_int(&solving);
    }
    return 0;
}
