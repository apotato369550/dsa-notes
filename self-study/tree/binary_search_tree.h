#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} *TreeNodePointer, TreedNode;

void insertNode(TreeNodePointer root, int data);
void deleteNode(TreeNodePointer root, int data);
bool isMember(TreeNodePointer root, int data);
int getMin(TreeNodePointer root);
int getMax(TreeNodePointer root);

#endif