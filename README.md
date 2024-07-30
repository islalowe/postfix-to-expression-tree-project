# Expression Tree Project
This project implements an expression tree that can be built from a postfix arithmetic expression. The expression tree supports various operations including tree traversal, evaluation, and a step-by-step evaluation output.

## Features
 **Tree Construction**: Build an expression tree from a postfix arithmetic expression.
- **Traversal**: Supports inorder, preorder, and postorder traversals.
- **Evaluation**: Evaluate the arithmetic expression stored in the tree.
- **Step-by-Step Evaluation**: Outputs a step-by-step evaluation of the expression in JSON format.

## Files

- `tree.h` and `tree.cpp`: Contains the implementation of the `Tree` class which represents the expression tree.
- `tree_node.h` and `tree_node.cpp`: Contains the implementation of the `TreeNode` class which represents nodes in the expression tree.

## Class Descriptions

### Tree

- **Constructor**: Initializes an empty tree with the root set to `nullptr`.
- **Destructor**: Recursively deallocates all nodes in the tree.
- **AssignPreorderIds**: Recursively assigns IDs to nodes in a preorder traversal.
- **BuildTree**: Builds an expression tree from a postfix expression string.
- **Traverse**: Returns a string representation of the tree's elements in the specified traversal order.
- **Evaluate**: Returns the result of evaluating the expression stored in the tree.
- **StepByStepEvaluation**: Outputs a step-by-step evaluation of the tree to a provided `ostream`.
- **Next**: Parses the next token from a postfix expression string.
- **InorderTraversal**: Returns a string representation of the tree's elements in inorder.
- **PreorderTraversal**: Returns a string representation of the tree's elements in preorder.
- **PostorderTraversal**: Returns a string representation of the tree's elements in postorder.
- **PostorderStepByStep**: Outputs a JSON representation of the tree in postorder to a provided `ostream`.
- **EvaluatePostorder**: Evaluates the tree's expression in postorder.
- **DestructorHelper**: Recursively deallocates all nodes in the tree.

### TreeNode

- **Constructor**: Initializes a tree node.
- **Destructor**: Deallocates a tree node.
- **GetValue**: Returns the node's value.
- **SetValue**: Sets the node's value.
- **GetLeft**: Returns the left child node.
- **GetRight**: Returns the right child node.
- **SetLeft**: Sets the left child node.
- **SetRight**: Sets the right child node.
- **SetId**: Sets the node's ID.
- **SetParentId**: Sets the node's parent ID.
- **GetId**: Returns the node's ID.
- **GetParentId**: Returns the node's parent ID.
