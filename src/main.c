#include "../lib/bst.h"
#include <stdio.h>

int main() {

  BSTNode root;
  nodeInit(50, &root);

  BSTNode child1;
  nodeInit(65, &child1);
  nodeInsert(&child1, &root);

  BSTNode child2;
  nodeInit(70, &child2);
  nodeInsert(&child2, &root);

  BSTNode child3;
  nodeInit(25, &child3);
  nodeInsert(&child3, &root);

  BSTNode child4;
  nodeInit(32, &child4);
  nodeInsert(&child4, &root);

  printf("\npreOrderPrint: \n");
  preOrderPrint(&root, 256);

  printf("\n\nInOrderPrint: \n");
  inOrderPrint(&root);

  printf("\n\npostOrderPrint: \n");
  postOrderPrint(&root);

  printf("\n\nPRINT TREE: \n");
  treeLevelPrint(&root);
  treeNodePrint(&root);

  printf("\n\nFIND HEIGHT 2: \n");
  Array *h2Arr = nodeSearchHeight(2, &root);
  printf("%d\n", h2Arr->array[0]);

  printf("\n\nFIND HEIGHT 1: \n");
  nodeSearchHeight(1, &root);

  printf("\n\nFIND HEIGHT 0: \n");
  nodeSearchHeight(0, &root);

  printf("\n\nTREE PRINT TESTING: \n");
  treePrint(&root);

  return 0;
}
