//
// Created by Isla Lowe on 7/29/24.
//

#ifndef POSTFIX_TO_EXPRESSION_TREE_PROJECT_TREE_NODE_H
#define POSTFIX_TO_EXPRESSION_TREE_PROJECT_TREE_NODE_H

#include<string>
using std::string;


class TreeNode {
protected:
    TreeNode* left;
    TreeNode* right;
    string _value;
    int _id;
    int _parentId;
public:
    TreeNode();
    virtual ~TreeNode();
    string GetValue() const;
    void SetValue(string& value);
    TreeNode* GetLeft() const;
    TreeNode* GetRight() const;
    void SetLeft(TreeNode* left);
    void SetRight(TreeNode* right);
    void SetId(int id);
    void SetParentId(int parentId);
    int GetId() const;
    int GetParentId() const;
};


#endif //POSTFIX_TO_EXPRESSION_TREE_PROJECT_TREE_NODE_H
