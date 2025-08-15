#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "stack_char.h"
#include "stack_int.h"

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
    *s = '\n';
}

// Push converted numeric string in integer stack and empty string
void push_int_string(Stack_int *stack, char *s) {
    if (s[0] != '\n') {
        push_int(stack, atoi(s));
    }
    memset(s, 0, strlen(s));
}

// Stores operands, detects operator, performs operation and pops that operator
void perform_correct_operation(Stack_int *stack, Stack_char *stack_ch) {
    int val1 = pop_int(stack);
    int val2 = pop_int(stack);

    if (peek_char(stack_ch) == '+') {
        push_int(stack, val2 + val1);
    } else if (peek_char(stack_ch) == '-') {
        push_int(stack, val2 - val1);
    } else if (peek_char(stack_ch) == '*') {
        push_int(stack, val2 * val1);
    } else if (peek_char(stack_ch) == '/') {
        push_int(stack, val2 / val1);
    } else if (peek_char(stack_ch) == '^') {
    push_int(stack, pow(val2, val1));
    }
    pop_char(stack_ch);
}


int main() {
    // Operator stack
    Stack_char op;
    initialize_char(&op);

    // Solving stack
    Stack_int solving;
    initialize_int(&solving);

    // Input expression is taken and stored
    char expression[MAX_SIZE];
    printf("Expression: ");
    // scanf("%s", expression);
    fgets(expression, sizeof(expression), stdin);

    // End program is input is empty
    if (expression[0] == '\n') {
        printf("No input\n");
        return -1;
    }

    int len = strlen(expression);       // Length of expression
    char num_string[10];                // String that holds numeric characters which are converted to numbers

    // Reads through expression character-by-character
    for (int i = 0; i < len-1; i++) {
        // Stores character
        char c = expression[i];

        // If character is number, append to num_string
        if (isalnum(c)) {
            addChar(num_string, c);
        
        // For opening bracket, push it to operator stack
        } else if (c == '(') {
            push_char(&op, c);
        
        // For closing bracket
        } else if (c == ')') {
            push_int_string(&solving, num_string);
            // Runs until operator stack is empty or opening bracket is encountered
            while (!is_empty_char(&op) && peek_char(&op) != '(') {
                perform_correct_operation(&solving, &op);
            }
            // Pop opening bracket from operator stack
            pop_char(&op);
        
        // For operator
        } else {
            push_int_string(&solving, num_string);
            // Runs until operator stack is empty or a higher precedence operator is encountered
            while (!is_empty_char(&op) && prec(c) <= prec(peek_char(&op))) {
                perform_correct_operation(&solving, &op);
            }
            push_char(&op, c);
        }
    }

    push_int_string(&solving, num_string);
    // Runs until operator stack is empty
    while (!is_empty_char(&op)) {
        perform_correct_operation(&solving, &op);
    }

    while (!is_empty_int(&solving)) {
        printf("%d\n", peek_int(&solving));
        pop_int(&solving);
    }

    return 0;
}
