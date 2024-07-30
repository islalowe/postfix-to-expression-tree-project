//
// Created by Isla Lowe on 7/29/24.
//

#include "tree_node.h"

/**
 * Default Constructor
 */
TreeNode::TreeNode() {
}

/**
 * Destructor
 */
TreeNode::~TreeNode() {
}

/**
 * Returns the data value for the current node
 */
string TreeNode::GetValue() const {
    return _value;
}

/**
 * Sets the value of the current node
 * @param value: The data value to be set for the current node
 */
void TreeNode::SetValue(string& value) {
    _value = value;
}


/**
 * Returns the node to the left of the current node.
 */
TreeNode* TreeNode::GetLeft() const {
    return left;
}

/**
 * Returns the node to the right of the current node.
 */
TreeNode* TreeNode::GetRight() const {
    return right;
}

/**
 * Sets the value of the node to the left of the current node
 * @param leftValue: the value to  be set for the left node
 */
void TreeNode::SetLeft(TreeNode* leftValue) {
    left = leftValue;
}

/**
 * Sets the value of the node to the right of the current node
 * @param rightValue: the value to  be set for the right node
 */
void TreeNode::SetRight(TreeNode* rightValue) {
    right = rightValue;
}


/**
 * Sets the individual Id of each node, and allows for tracking parents' Ids.
 * Id is set during tree building.
 * @param id: The id that will be assigned to nodes during tree building. It will be incremented.
 */
void TreeNode::SetId(int id) {
    _id = id;
}

/**
 * Sets the id of a parent node.
 * Id is set during tree building and root parent Ids are -1.
 * @param id: The id that will be assigned to the parent nodes.
 */
void TreeNode::SetParentId(int parentId) {
    _parentId = parentId;
}

/**
 * Returns the value of the Id
 */
int TreeNode::GetId() const {
    return _id;
}

/**
 * Returns the value of the parent Id
 */
int TreeNode::GetParentId() const{
    return _parentId;
}
