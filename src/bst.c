#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/bst.h"
#include "../lib/stack.h"

Array *initArray(int size) {
  Array *Arr = (Array *)malloc(sizeof(Array));
  if (Arr == NULL) {
    printf("Array is null");
    return NULL;
  }
  Arr->array = (int *)malloc(size * sizeof(int));
  if (Arr->array == NULL) {
    printf("Arr->array = NULL");
    free(Arr);
    return NULL;
  }
  Arr->size = size;
  Arr->used = 0;
  return Arr;
}

void freeArray(Array *arr) {
  free(arr->array);
  free(arr);
}

void nodeInit(int key, BSTNode *node) {
  node->key = key;
  node->height = 0;
  node->isLeftChild = false;
  node->isRightChild = false;
  node->left = NULL;
  node->right = NULL;
}

void toggleChildStatus(BSTNode *node) {
  bool left = node->isLeftChild;
  bool right = node->isRightChild;

  left = !left;
  right = !right;

  node->isRightChild = right;
  node->isLeftChild = left;
}

BSTNode *nodeSearch(int key, BSTNode *node) {
  BSTNode *cur = node;
  while (cur != NULL) {
    if (key == cur->key) {
      return cur;
    } else {
      if (cur->key < key) {
        nodeSearch(key, cur->left);
      } else {
        nodeSearch(key, cur->right);
      }
    }
  }
  return NULL;
}

void nodeSearchHeightHelper(int height, BSTNode *node, Stack *stack) {
  if (node == NULL) {
    return;
  }

  if (height == node->height) {
    push(stack, node);
  }

  nodeSearchHeightHelper(height, node->left, stack);
  nodeSearchHeightHelper(height, node->right, stack);
}

Array *nodeSearchHeight(int height, BSTNode *root) {
  Stack *stack = stackInit(100);
  nodeSearchHeightHelper(height, root, stack);
  Array *ptr = initArray(stack->curSize);
  int count = 0;
  while (!isEmpty(stack)) {
    BSTNode *node;
    node = pop(stack);
    ptr->array[count] = node->key;
    count++;
  }
  freeStack(stack);
  return ptr;
}

BSTNode *nodeInsert(BSTNode *node, BSTNode *root) {
  if (root == NULL) {
    return node;
  }

  if (node->key < root->key) {
    if (!node->isLeftChild && !node->isRightChild) {
      node->isLeftChild = true;
    } else if (node->isLeftChild && !node->isRightChild) {
      node->isLeftChild = true;
    } else {
      toggleChildStatus(node);
    }
    root->left = nodeInsert(node, root->left);
    node->height++;
  } else if (node->key > root->key) {
    if (!node->isLeftChild && !node->isRightChild) {
      node->isRightChild = true;
    } else if (!node->isLeftChild && node->isRightChild) {
      node->isRightChild = true;
    } else {
      toggleChildStatus(node);
    }
    root->right = nodeInsert(node, root->right);
    node->height++;
  } else {
    return node;
  }
  return root;
}

int nodeHeight(BSTNode *root, BSTNode *node, int heightStart) {
  int heightCur = heightStart;
  if (root == NULL) {
    return -1;
  }

  if (node->key < root->key) {
    heightCur++;
    heightCur = nodeHeight(root->left, node, heightCur);
  } else if (node->key > root->key) {
    heightCur++;
    heightCur = nodeHeight(root->right, node, heightCur);
  }

  return heightCur;
}

int treeHeight(BSTNode *node) {
  if (node == NULL) {
    return -1;
  }

  int leftH = treeHeight(node->left);
  int rightH = treeHeight(node->right);

  if (leftH > rightH) {
    return leftH + 1;
  } else {
    return rightH + 1;
  }
}

void nodePrint(BSTNode *node) {
  printf("%p: {KEY: %d; LEFT: %p; RIGHT: %p; H: %d; RC: %d; LC: %d}\n", node,
         node->key, node->left, node->right, node->height, node->isRightChild,
         node->isLeftChild);
}

char *preOrderPrint(BSTNode *node, size_t bufSize) {
  if (node == NULL) {
    return NULL;
  }

  char buf[bufSize];
  char *target = buf;

  Stack *stack = stackInit(100);

  push(stack, node);

  while (!isEmpty(stack)) {
    BSTNode *curNode = pop(stack);
    target += sprintf(target, "%d\n", curNode->key);
    printf("%d\n", curNode->key);

    if (curNode->right) {
      push(stack, curNode->right);
    }

    if (curNode->left) {
      push(stack, curNode->left);
    }
  }

  printf("\n\nbuffer pre order: \n");
  printf("%s\n", buf);
  freeStack(stack);
  return target;
}

void inOrderPrint(BSTNode *node) {
  if (node == NULL) {
    return;
  }

  inOrderPrint(node->left);
  printf("%d\n", node->key);
  inOrderPrint(node->right);
}

void postOrderPrint(BSTNode *node) {
  if (node == NULL) {
    return;
  }

  postOrderPrint(node->left);
  postOrderPrint(node->right);
  printf("%d\n", node->key);
}

int printSpaces(int count) {
  int i = 0;
  while (i < count) {
    printf("-");
    i++;
  }
  return i;
}

void treeNodePrint(BSTNode *root) {
  if (root == NULL) {
    return;
  }

  nodePrint(root);
  treeNodePrint(root->left);
  treeNodePrint(root->right);
}

void treeLevelPrint(BSTNode *root) {
  int hTotal = treeHeight(root);
  for (int i = 0; i <= hTotal; i++) {
    Array *ptr = nodeSearchHeight(i, root);
    for (int j = 0; j < ptr->size; j++) {
      printf("%d: %d\n", i, ptr->array[j]);
    }
  }
}

void treePrint(BSTNode *root) {
  int hTotal = treeHeight(root);
  int width = (1 << hTotal) * 2;
  int curNodeX = width / 2;
  int spacesPrinted = 0;
  int spacesRem;
  printf("width: %d\n", width);
  printf("hTotal: %d\n", hTotal);

  // spacesPrinted = printSpaces(width / 2);
  // spacesRem = width - spacesPrinted;
  // printf("%d", root->key);
  // spacesRem = width - spacesPrinted;
  // spacesPrinted = printSpaces(spacesRem);
  // printf("\n");

  for (int i = 0; i <= hTotal; ++i) {
    Array *arr = nodeSearchHeight(i, root);
    for (int j = arr->size - 1; j > -1; --j) {
      printf("%d->", arr->array[j]);
    }
    printf("\n");
  }
}
