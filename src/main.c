#include "../lib/bst.h"
#include <stdio.h>

int main() {
  // Tree creation
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

  // TRAVERSALS
  printf("Traversals (pre, in, post): \n");
  printf("\npreOrderPrint: \n");
  preOrderPrint(&root);

  printf("\nInOrderPrint: \n");
  inOrderPrint(&root);

  printf("\npostOrderPrint: \n");
  postOrderPrint(&root);

  // DEBUG STUFF
  printf("\n\nPRINT TREE: \n");
  treeLevelPrint(&root);

  printf("\n\nFIND HEIGHT 2: \n");
  printLevelNodes(2, &root);

  printf("\n\nFIND HEIGHT 1: \n");
  printLevelNodes(1, &root);

  printf("\n\nFIND HEIGHT 0: \n");
  printLevelNodes(0, &root);

  printf("\n\nTREE ASCII: \n");
  treePrint(&root);

  // Tree Debug
  printf("\n\nDEBUG INFO\n");
  treeNodePrint(&root);

  return 0;
}
