#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================================================
// EXPRESSION TREE OPERATIONS (Based on Aho Section 3.6)
// ============================================================================
// Expression trees represent arithmetic expressions
// Leaves = operands (numbers), Interior nodes = operators (+, -, *, /)

// ----------------------------------------------------------------------------
// Basic Operations
// ----------------------------------------------------------------------------

// Initialize expression tree to empty
void initExprTree(ExprTree *T);

// Create an operand node (leaf with a numeric value)
ExprTreeNode* createOperandNode(double value);

// Create an operator node (interior node with left and right operands)
ExprTreeNode* createOperatorNode(char op, ExprTree left, ExprTree right);

// ----------------------------------------------------------------------------
// Tree Construction from Expressions
// ----------------------------------------------------------------------------

// Build expression tree from postfix notation
// Example: "3 4 + 2 *" represents (3+4)*2
ExprTree buildFromPostfix(char *postfix);

// Build expression tree from prefix notation
// Example: "* + 3 4 2" represents (3+4)*2
ExprTree buildFromPrefix(char *prefix);

// Build expression tree from infix notation with full parentheses
// Example: "((3+4)*2)" represents (3+4)*2
ExprTree buildFromInfix(char *infix);

// ----------------------------------------------------------------------------
// Expression Evaluation
// ----------------------------------------------------------------------------

// Evaluate the expression tree and return result
double evaluate(ExprTree T);

// Check if expression tree is valid (proper structure)
bool isValidExpression(ExprTree T);

// ----------------------------------------------------------------------------
// Expression Output (Tree to Notation Conversion)
// ----------------------------------------------------------------------------

// Convert expression tree to prefix notation
// Example: (3+4)*2 becomes "* + 3 4 2"
void toPrefix(ExprTree T);

// Convert expression tree to postfix notation
// Example: (3+4)*2 becomes "3 4 + 2 *"
void toPostfix(ExprTree T);

// Convert expression tree to infix notation with minimal parentheses
// Example: (3+4)*2 becomes "(3+4)*2"
void toInfix(ExprTree T);

// Convert to fully parenthesized infix
// Example: (3+4)*2 becomes "((3+4)*2)"
void toInfixFull(ExprTree T);

// ----------------------------------------------------------------------------
// Tree Display and Utilities
// ----------------------------------------------------------------------------

// Display expression tree structure
void displayExprTree(ExprTree T);

// Count total nodes in expression tree
int countExprNodes(ExprTree T);

// Calculate height of expression tree
int exprTreeHeight(ExprTree T);

// Check if tree is empty
bool isExprTreeEmpty(ExprTree T);

// Count number of operators in expression
int countOperators(ExprTree T);

// Count number of operands in expression
int countOperands(ExprTree T);

// ----------------------------------------------------------------------------
// Advanced Operations
// ----------------------------------------------------------------------------

// Create a copy of the expression tree
ExprTree copyExprTree(ExprTree T);

// Simplify constant expressions (e.g., 3+4 becomes 7)
ExprTree simplifyConstants(ExprTree T);

// Check if two expression trees are equivalent
bool areEquivalent(ExprTree T1, ExprTree T2);

// Differentiate expression with respect to variable (if using variables)
// Note: This would require extending the type to support variables
// ExprTree differentiate(ExprTree T, char variable);

// Free expression tree
void freeExprTree(ExprTree *T);

#endif
