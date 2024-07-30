//
// Created by Isla Lowe on 7/29/24.
//
#include "tree.h"


/**
 * Default constructor, it only sets the _root to nullptr
 */
Tree::Tree() {
    _root = nullptr;
}

/**
 * Destructor. Takes care of deallocating all the memory used by the tree.
 */
Tree::~Tree() {
    DestructorHelper(_root);
}

/**
 * This method recursively traverses the tree and assigns IDs to the nodes.
 * @param nodeId: the ID that is assigned to the node
 * @param root: the current root node to work from
 */
void Tree::AssignPreorderIds(TreeNode* root, int& nodeId, int parentId) {
    if (root == nullptr) {
        return;
    }
    // Assign ID to current node
    root->SetId(nodeId);
    // Assign parent ID
    root->SetParentId(parentId);
    // Increment ID for the next node
    nodeId++;
    // Traverse left subtree
    AssignPreorderIds(root->GetLeft(), nodeId, root->GetId());
    // Traverse right subtree
    AssignPreorderIds(root->GetRight(), nodeId, root->GetId());
}


/**
 * The method takes in a string representing a postfix arithmetic expression.
 * Given this expression the method will build the expression tree.
 * If the method is unable to do it, then it should return false.
 * If it was to successfully create the tree then it should return true.
 * A stack is used.
 */
bool Tree::BuildTree(const string &postfixExpression) {
    bool treeBuilt = false;
    string sym;
    int pos = 0;                    //current index of iteration through the string parameter
    stack<TreeNode*> postfixStack;
    string postfixString = postfixExpression;
    while (pos < postfixString.size()) {
        //read using Next each element of the string (this may be an operator, int, or double)
        sym = Next(postfixString, pos);
        //put each operand (numerical) element into the stack
        if (isdigit(sym.at(0)) || sym.at(0) == '.' || (sym.at(0) == '-' && sym.length() > 1)) {
            TreeNode *operand = new TreeNode();
            //this nullptr part is for memory management
            operand->SetRight(nullptr);
            operand->SetLeft(nullptr);
            operand->SetValue(sym);
            postfixStack.push(operand);
        }
            //when an operator is reached, that becomes the parent of the operands in the stack
        else if (!isdigit(sym.at(0)) && sym != ")") {
            //the children need to be popped
            //if the stack is too small for operations, the tree building stops
            if (postfixStack.size() < 2) {
                return false;
            }
            TreeNode *rightOperand = postfixStack.top();
            postfixStack.pop();
            TreeNode *leftOperand = postfixStack.top();
            postfixStack.pop();
            //now the operator becomes the parent node
            TreeNode *operatorNode = new TreeNode();
            operatorNode->SetValue(sym);
            operatorNode->SetLeft(leftOperand);
            operatorNode->SetRight(rightOperand);
            //push the node with children node back into the stack - kind of recursive
            postfixStack.push(operatorNode);
        }
    }
    // There should be exactly one element left in the stack: the new tree
    if (postfixStack.size() != 1) {
        return false;
    }
    _root = postfixStack.top();
    postfixStack.pop();

    // Assign preorder IDs
    int nodeId = 0;
    AssignPreorderIds(_root, nodeId, -1);  // Pass -1 as parentId for the root node
    // Set parent ID
    _root->SetParentId(-1);

    treeBuilt = true;
    return treeBuilt;
}


/**
 * This method returns a string with the elements of the tree separated by spaces.
 * The elements will be added to this string according to the type of
 * traversal "requested" by the parameter.
 * All three traversal types are implemented.
 */
string Tree::Traverse(TraversalType traversalType) const {
    string treeElements = "";
    if (traversalType == INORDER) {
        //left subtree -> root -> right subtree
        treeElements = InorderTraversal(_root);
    }
    else if (traversalType == PREORDER) {
        //root -> left subtree -> right subtree
        treeElements = PreorderTraversal(_root);
    }
    else if (traversalType == POSTORDER) {
        //left subtree -> right subtree -> root
        treeElements = PostorderTraversal(_root);
    }
    else {
        std::cerr << "Invalid traversal type";
    }
    return treeElements;
}


/**
 * This method returns a double that is the result of
 * evaluating the expression that is stored in the tree.
 */
//use postorder
double Tree::Evaluate() const{
    return EvaluatePostorder(_root);
}


/**
 * this method will send to the ostream parameter the data stored on
 * each of the nodes as they were calculated.
 * The information that this operation displays will show the "structure" of the tree.
 * It will show the expression tree with its evaluation values.
 * Each evaluation step is represented by a JSON formatted line.
 * The output parameter is where these strings are going to be sent to.
 * The useLevel parameter is used when a leveled output is desired.
 */
void Tree::StepByStepEvaluation(ostream& output, bool useLevel) const {
    int id = 0;
    PostorderStepByStep(_root, output, 0, useLevel, _root, id);
}


/**
 * This method takes in a string and returns the next "thing"
 * (operator, operand or parenthesis) from the string sent as parameter.
 * @param infixString the string that will be read through and the next character returned
 */
string Tree::Next(string& postfixString, int& pos) const {
    string sym = "";
    while (pos < static_cast<int>(postfixString.length())) {
        //if the index is one of these, it's not a number
        //and SO it is only one digit
        if (postfixString[pos] == '+' || postfixString[pos] == '-' || postfixString[pos] == '*'
            || postfixString[pos] == '/' || postfixString[pos] == '^' || postfixString[pos] == '#') {
            //set sym as the one digit operator by using pos as the index for assignment, and then incrementing after.
            sym = postfixString[pos++];
            //scoot past the space
            while (pos < postfixString.size() && isspace(postfixString[pos])) {
                pos++;
            }
            break;  //then we're done here
        }
            //if sym is not an operator or a space, it is an operand, and may have multiple digits
            //keep counting the number of digits for the length of the substring until a space is encountered
        else if (isdigit(postfixString[pos]) || postfixString[pos] == '.' ||
                 //if the number is negative
                 (postfixString[pos] == '-' && (pos + 1 < postfixString.size() && isdigit(postfixString[pos + 1])))) {
            //ex: 2.1 4.5 +    --> operand is 2.1, pos should go from 0 to 2, operandLength should be 3
            size_t operandLength = 0;
            size_t operandStart = pos;
            //while (!isspace(postfixString[pos]) && (pos < static_cast<int>(postfixString.length()))) {
            while (pos < postfixString.length() && (isdigit(postfixString[pos]) || postfixString[pos] == '.')) {
                operandLength++;
                ++pos;
            }
            //pos lands on the space following the operand
            sym = postfixString.substr(operandStart,operandLength);
            //pos is sent forward one to the next operator or operand
            while (pos < postfixString.size() && isspace(postfixString[pos])) {
                pos++;
            }
            break;
        }
        else {
            pos++;
        }
    }
    return sym;
}


/**
 * This method performs an inorder traversal and
 * returns a string representation of all of the nodes of the tree
 * @param root: the the current TreeNode being visited in the traversal
 */
string Tree::InorderTraversal(TreeNode *root) const {
    //base case
    if (root==nullptr) {
        return "";
    }
    stringstream inorderStringStream;
    //go left first
    inorderStringStream << InorderTraversal(root->GetLeft());
    if (!inorderStringStream.str().empty()) {
        inorderStringStream << " ";
    }
    //go back to the node
    inorderStringStream << root->GetValue();
    //go right
    string rightString = InorderTraversal(root->GetRight());
    if (!rightString.empty()) {
        inorderStringStream << " " << rightString;
    }
    return inorderStringStream.str();
}

/**
 * This method performs an preorder traversal and
 * returns a string representation of all of the nodes of the tree
 * @param root: the the current TreeNode being visited in the traversal
 */
string Tree::PreorderTraversal(TreeNode *root) const {
    //base case
    if (root==nullptr) {
        return "";
    }
    stringstream preorderStringStream;
    //get the root
    preorderStringStream << root->GetValue();
    //go left
    string leftString = PreorderTraversal(root->GetLeft());
    if (!leftString.empty()) {
        preorderStringStream << " " << leftString;
    }
    //go right
    string rightString = PreorderTraversal(root->GetRight());
    if (!rightString.empty()) {
        preorderStringStream << " " << rightString;
    }
    return preorderStringStream.str();
}

/**
 * This method performs an postorder traversal and
 * returns a string representation of all of the nodes of the tree
 * @param root: the the current TreeNode being visited in the traversal
 */
string Tree::PostorderTraversal(TreeNode* root) const {
    stringstream postorderStringStream;
    //base case
    if (root==nullptr) {
        return "";
    }
    //go left
    string leftString = PostorderTraversal(root->GetLeft());
    if (!leftString.empty()) {
        postorderStringStream << leftString << " ";
    }
    //go right
    string rightString = PostorderTraversal(root->GetRight());
    if (!rightString.empty()) {
        postorderStringStream << rightString << " ";
    }
    //get the root
    postorderStringStream << root->GetValue();
    return postorderStringStream.str();
}

/**
 * This method performs an postorder traversal and
 * sends to output as formatted representation of the tree
 * @param root: the the current TreeNode being visited in the traversal
 * @param output: the ostream that the information will be sent to
 * @param level: the level of the current node
 * @param useLevel: whether the output will have the parent-child relationship represented graphically or textually
 * @param parent: parent ID to be tracked
 * @param id: current node Id to be tracked
 */
void Tree::PostorderStepByStep(TreeNode* root, ostream& output, int level, bool useLevel, TreeNode* parent, int id) const {
    //base case takes care of covering the root
    if (root == nullptr) {
        return;
    }
    //if useLevel is true then the output will be indented
    if (useLevel) {
        for (size_t indentSize = level; indentSize > 0; indentSize--) {
            output << " ";
        }
    }
    //output the root
    output << "{\"value\":";
    //value of the root can be an operator or operand
    string value = root->GetValue();
    bool isOperand = (isdigit(value[0]) || (value[0] == '-' && value.length() > 1));

    //if the current node in the recursion is an operator
    if (!isOperand) {
        output << std::fixed << std::setprecision(2) << EvaluatePostorder(root);
        output << ", \"operator\":\"" << root->GetValue();
        output << "\"";
        output << ", \"operand\":false";
    }
    //if the current node in the recursion is an operand
    if (isOperand) {
        output << std::fixed << std::setprecision(2) << std::stod(root->GetValue());
        output << ", \"operator\":\"#\", \"operand\":true";
    }
    //the fields id and parent are necessary if level is not used
    //ex:   {"value":-3.00, "operator":"-", "operand":false, "id":0, "parent":-1}
    if (!useLevel) {
        output << ", \"id\":" << root->GetId();
        //add the parent
        output << ", \"parent\":"  << root->GetParentId();
        output << "}";
    }
    output << std::endl;
    //go left
    PostorderStepByStep(root->GetLeft(), output, level + 1, useLevel, root, root->GetId() + 1);
    //go right
    PostorderStepByStep(root->GetRight(), output, level + 1, useLevel, root, root->GetId() + 1);
}

/**
 * This method performs an postorder traversal and
 * returns a double representation of the evaluated total of the expression in the tree
 * @param root: the the current TreeNode being visited in the traversal
 */
double Tree::EvaluatePostorder(TreeNode* root) const{
    //base case takes care of covering the root
    if (root==nullptr) {
        return 0.0;
    }
    //in the event of a one-node tree, return that number
    if (isdigit(root->GetValue().at(0))) {
        //converting to a double
        return stod(root->GetValue());
    }
    double operand1 = EvaluatePostorder(root->GetLeft());
    double operand2 = EvaluatePostorder(root->GetRight());
    //if the current node in the recursion is an operator
    if (!isdigit(root->GetValue().at(0))) {
        if (root->GetValue() == "*") {
            return (operand1 * operand2);
        }
        if (root->GetValue() == "/") {
            return (operand1 / operand2);
        }
        if (root->GetValue() == "-") {
            return (operand1 - operand2);
        }
        if (root->GetValue() == "+") {
            return (operand1 + operand2);
        }
        if (root->GetValue() == "^") {
            return (pow(operand1, operand2));
        }
    }
    return 0.0;
}

/**
 * This method performs an postorder traversal and
 * deletes all of the subtrees from the current node
 * @param root: the the current TreeNode being visited in the traversal
 */
void Tree::DestructorHelper(TreeNode* node){
    //base case
    if (node == nullptr) {
        return;
    }
    //traverse postfix method
    //and delete the whole tree, bottom-up
    //go left
    DestructorHelper(node->GetLeft());
    //go right
    DestructorHelper(node->GetRight());
    delete(node);
}