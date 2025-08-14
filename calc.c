#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Maximum size of structure arrays
#define MAX_SIZE 100

// Structure data type that stores characters; used for operator stack
typedef struct {
    char arr[MAX_SIZE];
    int top;
} Stack_char;

// Structure data type that stores integers; used for solving stack
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
    // printf("Pushed %d onto the stack..\n", value);
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

int pop_int(Stack_int *stack) {
    if (isEmpty_int(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int popped = stack->arr[stack->top];
    stack->top--;
    // printf("Popped %d from the stack..\n", popped);
    return popped;
}


char peek(Stack_char *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return 'X';
    }
    return stack->arr[stack->top];
}

int peek_int(Stack_int *stack) {
    if (isEmpty_int(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}

// Returns precedence of argument operator
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

// Append characters to string
void addChar(char *s, char c) {
    while (*s++);
    *(s - 1) = c;
    *s = '\0';
}

// Push converted numeric string in integer stack and empty string
void push_int_string(Stack_int *stack, char *s) {
    if (s[0] != '\0') {
        push_int(stack, atoi(s));
    }
    memset(s, 0, strlen(s));
}

// Stores operands, detects operator, performs operation and pops that operator
void perform_correct_operation(Stack_int *stack, Stack_char *stack_ch) {
    int val1 = pop_int(stack);
    int val2 = pop_int(stack);

    if (peek(stack_ch) == '+') {
        push_int(stack, val2 + val1);
    } else if (peek(stack_ch) == '-') {
        push_int(stack, val2 - val1);
    } else if (peek(stack_ch) == '*') {
        push_int(stack, val2 * val1);
    } else if (peek(stack_ch) == '/') {
        push_int(stack, val2 / val1);
    } else if (peek(stack_ch) == '^') {
    push_int(stack, pow(val2, val1));
    }
    pop(stack_ch);
}


int main() {
    // Operator stack
    Stack_char op;
    initialize(&op);

    // Solving stack
    Stack_int solving;
    initialize_int(&solving);

    // Input expression is taken and stored
    char expression[MAX_SIZE];
    printf("Expression: ");
    scanf("%s", expression);

    int len = strlen(expression);       // Length of expression
    char num_string[10];                // String that holds numeric characters which are converted to numbers

    // Reads through expression character-by-character
    for (int i = 0; i < len; i++) {
        // Stores character
        char c = expression[i];

        // If character is number, append to num_string
        if (isalnum(c)) {
            addChar(num_string, c);
        
        // For opening bracket, push it to operator stack
        } else if (c == '(') {
            push(&op, c);
        
        // For closing bracket
        } else if (c == ')') {
            push_int_string(&solving, num_string);
            // Runs until operator stack is empty or opening bracket is encountered
            while (!isEmpty(&op) && peek(&op) != '(') {
                perform_correct_operation(&solving, &op);
            }
            // Pop opening bracket from operator stack
            pop(&op);
        
        // For operator
        } else {
            push_int_string(&solving, num_string);
            // Runs until operator stack is empty or a higher precedence operator is encountered
            while (!isEmpty(&op) && prec(c) <= prec(peek(&op))) {
                perform_correct_operation(&solving, &op);
            }
            push(&op, c);
        }
    }

    push_int_string(&solving, num_string);
    // Runs until operator stack is empty
    while (!isEmpty(&op)) {
        perform_correct_operation(&solving, &op);
    }

    while (!isEmpty_int(&solving)) {
        printf("%d\n", peek_int(&solving));
        pop_int(&solving);
    }

    return 0;
}
