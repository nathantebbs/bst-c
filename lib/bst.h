#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdbool.h>

typedef struct BSTNode {
	bool isLeftChild;
	bool isRightChild;
	int key;
	int height;
	int curNodeX;
	struct BSTNode *left;
	struct BSTNode *right;
} BSTNode;

typedef struct {
	BSTNode **array;
  size_t size;
} Array;



void nodeInit(int key, BSTNode *node);
void freeArray(Array *arr);
BSTNode *nodeSearch(int key, BSTNode *node);
BSTNode *nodeInsert(BSTNode *node, BSTNode *root);
int nodeHeight(BSTNode *root, BSTNode *node, int heightStart);
int treeHeight(BSTNode *node);
void nodePrint(BSTNode *node);
char *preOrderPrint(BSTNode *node, size_t bufSize);
void inOrderPrint(BSTNode *node);
void postOrderPrint(BSTNode *node);
int printSpaces(int count);
void treeNodePrint(BSTNode *root);
Array *nodeSearchHeight(int height, BSTNode *root);
void treeLevelPrint(BSTNode *root);
void treePrint(BSTNode *root);
void printLevelNodes(BSTNode *root, int height);


#endif
