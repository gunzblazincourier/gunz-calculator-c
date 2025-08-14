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
    printf("Pushed %c onto the stack\n", value);
}

void push_int(Stack_int *stack, int value) {
    if (isFull_int(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
    printf("Pushed %d onto the stack..\n", value);
}

char pop(Stack_char *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return 'X';
    }
    char popped = stack->arr[stack->top];
    stack->top--;
    printf("Popped %c from the stack\n", popped);
    return popped;
}

int pop_int(Stack_int *stack) {
    if (isEmpty_int(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int popped = stack->arr[stack->top];
    stack->top--;
    printf("Popped %d from the stack..\n", popped);
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

void addChar(char *s, char c) {
    while (*s++);
    *(s - 1) = c;
    *s = '\0';
}

int main() {
    Stack_char op;
    initialize(&op);

    Stack_int solving;
    initialize_int(&solving);

    char expression[MAX_SIZE];
    printf("Expression: ");
    scanf("%s", expression);

    // printf("%d\n", strlen(expression));
    int len = strlen(expression);
    char num_string[10];
    for (int i = 0; i < len; i++) {
        char c = expression[i];
        // printf("%c\n", c);
        if (isalnum(c)) {
            addChar(num_string, c);
        } else if (c == '(') {
            // int num = atoi(num_string);
            // printf("%d\n", num);
            // push_int(&solving, num);
            // memset(num_string,0,strlen(num_string));
            push(&op, c);
        } else if (c == ')') {
            // printf("char1,%s\n", num_string);
            if (num_string[0] != '\0') {
                int num = atoi(num_string);
                // printf("%d\n", num);
                push_int(&solving, num);
            }
            memset(num_string,0,strlen(num_string));

            while (!isEmpty(&op) && peek(&op) != '(') {
                // push(&solving, peek(&op));
                // pop(&op);
                printf("peek1,%d\n", peek_int(&solving));
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
            pop(&op);
        } else {
            // printf("char2,%s\n", num_string);
            if (num_string[0] != '\0') {
                int num = atoi(num_string);
                // printf("%d\n", num);
                push_int(&solving, num);
            }
            memset(num_string,0,strlen(num_string));
            while (!isEmpty(&op) && prec(c) <= prec(peek(&op))) {
                // push(&solving, peek(&op));
                // pop(&op);
                printf("peek2,%d\n", peek_int(&solving));
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

    // printf("char3,%s\n", num_string);
    if (num_string[0] != '\0') {
        int num = atoi(num_string);
        // printf("%d\n", num);
        push_int(&solving, num);
    }
    memset(num_string,0,strlen(num_string));
    while (!isEmpty(&op)) {
        // push(&solving, peek(&op));
        // pop(&op);
        printf("peek3,%d\n", peek_int(&solving));
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

    // char num_string[10];
    // addChar(num_string, '2');
    // printf("%s\n", num_string);
    // addChar(num_string, '3');
    // printf("%s\n", num_string);
    // memset(num_string,0,strlen(num_string));
    // addChar(num_string, '4');
    // printf("%s\n", num_string);
    // addChar(num_string, '2');
    // printf("%s\n", num_string);

    // push_int(&solving, atoi("260"));
    // printf("%d", peek_int(&solving));
    return 0;
}
