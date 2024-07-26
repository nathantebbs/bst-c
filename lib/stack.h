#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "./bst.h"

typedef struct {
	
	BSTNode **array;
	int top;
	int capacity;
	int curSize;

} Stack;

Stack *stackInit(int capacity);

bool isEmpty(Stack *stack);
bool isFull(Stack *stack);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *stack);
BSTNode *peek(Stack *stack);
void freeStack(Stack *stack);


#endif // !DEBUG
