#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/stack.h"

Array *initArray(int size) {
  Array *Arr = (Array *)malloc(sizeof(Array));
  if (Arr == NULL) {
    printf("Array is null");
    return NULL;
  }
  Arr->array = (BSTNode **)malloc(size * sizeof(BSTNode *));
  if (Arr->array == NULL) {
    printf("Arr->array = NULL");
    free(Arr);
    return NULL;
  }
  Arr->size = size;
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
  node->curNodeX = 0;
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
    ptr->array[count] = node;
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

void preOrderPrint(BSTNode *node) {
  if (node == NULL) {
    return;
  }

  printf("%d\n", node->key);
  preOrderPrint(node->left);
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
      printf("%d: %d\n", i, ptr->array[j]->key);
    }
    freeArray(ptr);
  }
}

void printLevelNodes(BSTNode *root, int height) {
  Array *ptr = nodeSearchHeight(height, root);
  for (int i = ptr->size - 1; i > -1; --i) {
    if (i == 0) {
      printf("%d", ptr->array[i]->key);
    } else {
      printf("%d->", ptr->array[i]->key);
    }
  }
  printf("\n");
  freeArray(ptr);
}

int printSpaces(int count) {
  int i = 0;
  while (i < count) {
    printf(" ");
    i++;
  }
  return i;
}

void treePrint(BSTNode *root) {
  int hTotal = treeHeight(root);
  int width = (1 << hTotal) * 2;
  int childOffset = width / 4;

  for (int i = 0; i <= hTotal; ++i) {
    Array *arr = nodeSearchHeight(i, root);
    int levelWidth = width / (1 << i);
    int nodeSpacing = levelWidth / (arr->size + 1);

    for (int j = arr->size - 1; j > -1; --j) {
      // Calculate actual offset based on child status
      int offset = nodeSpacing * (j + 1) +
                   (arr->array[j]->isRightChild ? childOffset : -childOffset);
      printSpaces(offset);
      printf("%d", arr->array[j]->key);
    }
    printf("\n");

    freeArray(arr);
  }
}
