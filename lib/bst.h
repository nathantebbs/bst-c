#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// Binary Search Tree Node
typedef struct BSTNode {
	bool isLeftChild;
	bool isRightChild;
	int key;
	int height;
	int curNodeX;
	struct BSTNode *left;
	struct BSTNode *right;
} BSTNode;


// Node Array
typedef struct {
	BSTNode **array;
  size_t size;
} Array;
void freeArray(Array *arr);

// Node Stack
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


// BST Functionality
void nodeInit(int key, BSTNode *node);
BSTNode *nodeInsert(BSTNode *node, BSTNode *root);
BSTNode *nodeSearch(int key, BSTNode *node);
int nodeHeight(int heightStart, BSTNode *node, BSTNode *root);
int treeHeight(BSTNode *node);
Array *nodeSearchHeight(int height, BSTNode *root);

// Prints
void nodePrint(BSTNode *node);
void preOrderPrint(BSTNode *node);
void inOrderPrint(BSTNode *node);
void postOrderPrint(BSTNode *node);
void treeNodePrint(BSTNode *root);
void printLevelNodes(int height, BSTNode *root);
void treeLevelPrint(BSTNode *root);
void treePrint(BSTNode *root);
#endif
