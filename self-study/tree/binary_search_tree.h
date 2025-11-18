#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <tree.h>

void insertNode(TreeNodePointer root, int data);
void deleteNode(TreeNodePointer root, int data);
bool isMember(TreeNodePointer root, int data);
int getMin(TreeNodePointer root);
int getMax(TreeNodePointer root);

#endif