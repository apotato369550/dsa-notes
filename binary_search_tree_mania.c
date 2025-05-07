#include <stdio.h>
#include <stdlib.h>

// basic treenode definition with treenode and root aliases
typedef struct TreeNode{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *Root;

// function prototypes
// basic functionalities to include in program

// 1. main menu with options - maybe this time I should delegate the options thing to a separate function
void mainMenu();

// helper functions
TreeNode *createNode(int value);
void printTabs(int tabs);

// 2. print tree
void printTree(Root root, int tabs);

// 3. insert node to tree
void insertNodeMenu(Root *root, int value);

// 4. delete node with value
void deleteNode(Root *root, int value);

// 5. check if value exists in tree
int doesValueExist(Root root, int value);

// 6. traverse tree submenu - inorder, preorder, postorder, level order
void traverseTreeSubmenu(Root *root);

// 7. structural check submenu - height of tree, number of nodes, is tree balanced?, is tree bst?
void structuralCheckSubmenu(Root *root);



int main() {
    printf("--- WELCOME TO BINARY TREE MANIA ---\nWhere trees are grown fresh every day!");
    mainMenu();
    return 0;
}

void mainMenu() {
    Root root = NULL;
    int input = -1;
    while (input != 0) {
        printf("Here are your choices: \n");
        printf("0 - Exit \n");
        printf("1 - Print tree \n");
        printf("2 - Insert node into tree \n");
        printf("3 - Delete node with value \n");
        printf("4 - Check if value exists in tree \n");
        printf("5 - Traverse tree \n");
        printf("6 - Perform structural checks on tree \n");

        scanf("%d", &input);

        switch(input) {
            case 0:
                printf("See you next time! Bye:)\n");
                break;
            case 1:
                printf("Printing tree...\n");
                break;
            case 2:
                printf("Inserting node into tree...\n");
                break;
            case 3:
                printf("Deleting node with value...\n");
                break;
            case 4:
                printf("Checking if value exists within tree...\n");
                break;
            case 5:
                printf("Entering tree traversal submenu...\n");
                break;
            case 6:
                printf("Entering structural checks submenu...\n");
                break;
        }
    }
}

// helper function to create nodes and stuff
TreeNode *createNode(int value) {
    TreeNode *newTreeNode = malloc(sizeof(TreeNode));
    if (newTreeNode != NULL) {
        newTreeNode->value = value;
        newTreeNode->left = NULL;
        newTreeNode->right = NULL;
    }
    return newTreeNode;
}

void printTabs(int tabs) {
    for (int i = 0 ; i < tabs; i++) {
        printf("\t");
    }
}

// 2. print tree
void printTree(Root root, int tabs) {
    if (root == NULL) {
        printTabs(tabs);
        printf("--- EMPTY ---\n");
    }
    printTree(root->right, tabs + 1);
    printTabs(tabs);
    printf("%d\n", root->value);
    printTree(root->left, tabs + 1);
}

// 3. insert node to tree
void insertNodeMenu(Root *root, int value) {
    int input = -1;
    printf("How would you like your node inserted? \n");
    while (input != 0) {
        printf("0 - Cancel insertion :(( \n");
        printf("1 - Insert Level Order \n");
        printf("2 - Insert BST (binary search tree) \n");
        scanf("%d", &input);
        switch(input) {
            case 0:
                printf("Cancelling insertion. Returning back to main menu...\n");
                break;
            case 1:
                printf("Inserting level-order... \n");
                break;
            case 2:
                printf("Inserting BST... \n");
                break;
        }
    }
}

// 4. delete node with value
void deleteNode(Root *root, int value);

// 5. check if value exists in tree
int doesValueExist(Root root, int value);

// 6. traverse tree submenu - inorder, preorder, postorder, level order
void traverseTreeSubmenu(Root *root);

// 7. structural check submenu - height of tree, number of nodes, is tree balanced?, is tree bst?
void structuralCheckSubmenu(Root *root);
