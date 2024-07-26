#include "../lib/bst.h"

/*-----DATA STRUCTURES FOR BST FUNCTIONALITY-----*/

/*---------------Node Aray-----------------------*/
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

/*---------------Node Stack----------------------*/
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
/*-----------END OF DATA STRUCTURES--------------*/

/*----------------------BST----------------------*/

// Create a new node, defaults as root
void nodeInit(int key, BSTNode *node) {
  node->key = key;
  node->height = 0;
  node->isLeftChild = false;
  node->isRightChild = false;
  node->curNodeX = 0;
  node->left = NULL;
  node->right = NULL;
}

/* Helper function to ensure child status of node is
 * correct after the node is inserted into the tree. */
void toggleChildStatus(BSTNode *node) {
  bool left = node->isLeftChild;
  bool right = node->isRightChild;

  left = !left;
  right = !right;

  node->isRightChild = right;
  node->isLeftChild = left;
}

// Insert a node into the tree. A tree is defined by a root.
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

/* Search for a node starting at the root given initially by the
 * caller. Returns Node if found; NULL if the noude cannot be found */
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

/* Helper for the nodeSearchHeight function. edits the passed stack to contain
 * the nodes matching given height query. */
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

// TODO: there is no reason for this to return "reverse level order"

/* Function to find all the nodes present at the given height. Returns a
 * node array containing that levels nodes in reverse level order.*/
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

/* Find the height (index 0), for a given node. Unless you wanna
 * offset your height keep heightStart to 0.*/
int nodeHeight(int heightStart, BSTNode *node, BSTNode *root) {
  int heightCur = heightStart;
  if (root == NULL) {
    return -1;
  }

  if (node->key < root->key) {
    heightCur++;
    heightCur = nodeHeight(heightCur, node, root->left);
  } else if (node->key > root->key) {
    heightCur++;
    heightCur = nodeHeight(heightCur, node, root->right);
  }

  return heightCur;
}

// Return total height of the tree rooted at the initial node.
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

// Debug print a BSTNode
void nodePrint(BSTNode *node) {
  printf("%p: {KEY: %d; LEFT: %p; RIGHT: %p; H: %d; RC: %d; LC: %d}\n", node,
         node->key, node->left, node->right, node->height, node->isRightChild,
         node->isLeftChild);
}

// Print the tree rooted at the initial callers node in preOrderTraversal
void preOrderPrint(BSTNode *node) {
  if (node == NULL) {
    return;
  }

  printf("%d\n", node->key);
  preOrderPrint(node->left);
}

// Print the tree rooted at the initial callers node in inOrderTraversal
void inOrderPrint(BSTNode *node) {
  if (node == NULL) {
    return;
  }

  inOrderPrint(node->left);
  printf("%d\n", node->key);
  inOrderPrint(node->right);
}

// Print the tree rooted at the initial callers node in postOrderTraversal
void postOrderPrint(BSTNode *node) {
  if (node == NULL) {
    return;
  }

  postOrderPrint(node->left);
  postOrderPrint(node->right);
  printf("%d\n", node->key);
}

// Debug print all the nodes of the tree rooted at the callers *root.
void treeNodePrint(BSTNode *root) {
  if (root == NULL) {
    return;
  }

  nodePrint(root);
  treeNodePrint(root->left);
  treeNodePrint(root->right);
}

/* Print the nodes of the tree rooted at the callers *root, attach level
 * values to each print. */
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

// Print all nodes present at a given height in the tree rooted at *root.
void printLevelNodes(int height, BSTNode *root) {
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

// Print a count number of spaces. Helper for treePrint.
int printSpaces(int count) {
  int i = 0;
  while (i < count) {
    printf(" ");
    i++;
  }
  return i;
}

// Print an ascii representation of the Binary Search Tree
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
