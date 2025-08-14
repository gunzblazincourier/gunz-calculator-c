#ifndef STACK_CHAR_H
#define STACK_CHAR_H
#define MAX_SIZE 100


typedef struct {
    char arr[100];
    int top;
} Stack_char;

void initialize_char(Stack_char *stack);
bool is_empty_char(Stack_char *stack);
bool is_full_char(Stack_char *stack);
void push_char(Stack_char *stack, char value);
char pop_char(Stack_char *stack);
char peek_char(Stack_char *stack);


#endif // STACK_CHAR_H