#ifndef STACK_INT_H
#define STACK_INT_H
#define MAX_SIZE 100


typedef struct {
    int arr[100];
    int top;
} Stack_int;

void initialize_int(Stack_int *stack);
bool is_empty_int(Stack_int *stack);
bool is_full_int(Stack_int *stack);
void push_int(Stack_int *stack, int value);
int pop_int(Stack_int *stack);
int peek_int(Stack_int *stack);


#endif // STACK_INT_H