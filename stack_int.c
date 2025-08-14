#include <stdio.h>
#include <stdbool.h>
#include "stack_int.h"

void initialize_int(Stack_int *stack) {
    stack->top = -1;
}

bool is_empty_int(Stack_int *stack) {
    return stack->top == -1;
}

bool is_full_int(Stack_int *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push_int(Stack_int *stack, int value) {
    if (is_full_int(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
    // printf("Pushed %d onto the stack..\n", value);
}

int pop_int(Stack_int *stack) {
    if (is_empty_int(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int popped = stack->arr[stack->top];
    stack->top--;
    // printf("Popped %d from the stack..\n", popped);
    return popped;
}

int peek_int(Stack_int *stack) {
    if (is_empty_int(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}