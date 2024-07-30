//
// Created by Isla Lowe on 7/29/24.
//

#ifndef POSTFIX_TO_EXPRESSION_TREE_PROJECT_TREE_H
#define POSTFIX_TO_EXPRESSION_TREE_PROJECT_TREE_H


#include <iostream>
#include <string>
#include "stack"
#include <sstream>
#include <cctype>
#include <iomanip>
#include <cmath>
using std::stack;
using std::string;
using std::ostream;
using std::stringstream;
using std::endl;

#include "tree_node.h"


enum TraversalType {INORDER, PREORDER, POSTORDER};

class Tree {
protected:
    TreeNode* _root;
    Tree(const Tree& other);
    const Tree& operator=(const Tree& rhs);
public:
    Tree();
    ~Tree();
    bool BuildTree(const string& postfixExpression);
    string Traverse(TraversalType traversalType)const;
    double Evaluate()const;
    void StepByStepEvaluation(ostream& output, bool useLevel = false)const;
    string Next(string& postfixString, int& pos) const;
    string InorderTraversal(TreeNode* root) const;
    string PreorderTraversal(TreeNode* root) const;
    string PostorderTraversal(TreeNode* root) const;
    void PostorderStepByStep(TreeNode* root, ostream& output, int level, bool useLevel, TreeNode* parent, int id) const;
    double EvaluatePostorder(TreeNode* root) const;
    void DestructorHelper(TreeNode* root);
    void AssignPreorderIds(TreeNode* root, int& nodeId, int parentId);
};


#endif //POSTFIX_TO_EXPRESSION_TREE_PROJECT_TREE_H
