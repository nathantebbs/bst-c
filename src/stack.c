#include "../lib/stack.h"
#include "../lib/bst.h"
#include <stdio.h>
#include <stdlib.h>

Stack *stackInit(int capacity) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->curSize = 0;
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (BSTNode **)malloc(stack->capacity * sizeof(BSTNode *));
  return stack;
}

bool isEmpty(Stack *stack) { return stack->top == -1; }

bool isFull(Stack *stack) { return stack->top == stack->capacity - 1; }

void push(Stack *stack, BSTNode *node) {
  if (isFull(stack)) {
    printf("Stack is full!\n");
  } else {
    stack->curSize++;
    stack->top++;
    stack->array[stack->top] = node;
  }
}

BSTNode *pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack is empty!\n");
    return NULL;
  } else {
    BSTNode *node = stack->array[stack->top];
    stack->curSize--;
    stack->top--;
    return node;
  }
}

BSTNode *peek(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack is empty!\n");
    return NULL;
  } else {
    return stack->array[stack->top];
  }
}

void freeStack(Stack *stack) {
  if (stack) {
    free(stack->array);
    free(stack);
  }
}
