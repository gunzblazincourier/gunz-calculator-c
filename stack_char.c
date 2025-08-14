#include <stdio.h>
#include <stdbool.h>
#include "stack_char.h"

void initialize_char(Stack_char *stack) {
    stack->top = -1;
}

bool is_empty_char(Stack_char *stack) {
    return stack->top == -1;
}

bool is_full_char(Stack_char *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push_char(Stack_char *stack, char value) {
    if (is_full_char(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
    // printf("Pushed %c onto the stack\n", value);
}

char pop_char(Stack_char *stack) {
    if (is_empty_char(stack)) {
        printf("Stack Underflow\n");
        return 'X';
    }
    char popped = stack->arr[stack->top];
    stack->top--;
    // printf("Popped %c from the stack\n", popped);
    return popped;
}

char peek_char(Stack_char *stack) {
    if (is_empty_char(stack)) {
        printf("Stack is empty\n");
        return 'X';
    }
    return stack->arr[stack->top];
}