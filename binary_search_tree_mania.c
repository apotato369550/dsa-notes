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

// helper functions
TreeNode *createNode(int value);
void printTabs(int tabs);

// 1. main menu with options - maybe this time I should delegate the options thing to a separate function
void mainMenu();

// 2. print tree
void printTree(Root root, int tabs);

// 3. insert node to tree
void insertNodeMenu(Root *root, int value);
void insertBST(Root *root, int value);

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
    int value = -1;
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
                printTree(root, 0);
                break;
            case 2:
                printf("Inserting node into tree...\n");
                printf("Please enter value to insert: ");
                scanf("%d", &value);
                insertNodeMenu(&root, value);
                break;
            case 3:
                printf("Deleting node with value...\n");
                break;
            case 4:
                printf("Checking if value exists within tree...\n");
                printf("Please enter value to search: ");
                scanf("%d", &value);
                if (doesValueExist(root, value)) {
                    printf("Value %d exists within the tree!\n", value);
                } else {
                    printf("Failed to find %d within the tree\n", value);
                }
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

// prints tabs when printing tree
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
    } else {
        // put it in else statement, otherwise
        // it crashes because it accesses null
        printTree(root->right, tabs + 1);
        printTabs(tabs);
        printf("%d\n", root->value);
        printTree(root->left, tabs + 1);
    }
}

// 3. insert node to tree
void insertNodeMenu(Root *root, int value) {
    int input = -1;
    printf("How would you like your node inserted? \n");
    while (input != 0) {
        printf("0 - Cancel insertion :(( \n");
        printf("1 - Insert BST (binary search tree) \n");
        printf("2 - Insert Level Order \n");
        scanf("%d", &input);
        switch(input) {
            case 0:
                printf("Cancelling insertion. Returning back to main menu...\n");
                break;
            case 1:
                printf("Inserting BST... \n");
                insertBST(root, value);
                input = 0;
                break;
            case 2:
                printf("Inserting level-order... \n");
                break;
        }
    }
}

void insertBST(Root *root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
        printf("Value %d has been inserted into tree!!!", value);
        return;
    }

    // always less than symbol
    if (value < (*root)->value) {
        // insert left
        insertBST(&(*root)->left, value);
    } else {
        // insert right
        insertBST(&(*root)->right, value);
    }
}

// 4. delete node with value
void deleteNode(Root *root, int value);

// 5. check if value exists in tree
int doesValueExist(Root root, int value) {
    // if value is found, return 1
    // recursively check if it exists in left and in right
    // if it exists in either, return 1, otherwise return 0

    // does not work. should try and handle NULL case
    // test this now.
    if (root->value == value) {
        return 1;
    } else {
        int existsInLeft = root->left == NULL ? 0 : doesValueExist(root->left, value);
        int existsInRight = root->right == NULL ? 0 : doesValueExist(root->right, value);

        return existsInLeft || existsInRight;
    }
}

// 6. traverse tree submenu - inorder, preorder, postorder, level order
void traverseTreeSubmenu(Root *root);

// 7. structural check submenu - height of tree, number of nodes, is tree balanced?, is tree bst?
void structuralCheckSubmenu(Root *root);
