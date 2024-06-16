/*
	Copyright (C) 2023 Marzan Ivan
 	Binary Tree program header
	GNU GENERAL PUBLIC LICENSE v3.0
*/
#pragma once

#include "BinaryTreeNode.hxx"
#include <utility>
#include <iostream>

template<class ValueType, class KeyType=ValueType>
class BinaryTree {
public:
    binarynode<ValueType, KeyType> *root;
    unsigned int size;

    BinaryTree(ValueType *Array, int SizeOfArray);

    BinaryTree();

    ~BinaryTree();

    bool insert(KeyType Key, ValueType Value);

    bool insert(std::pair<ValueType, KeyType> node_data);

    bool remove(KeyType Key);

    bool is_empty();

    void clear();

    int CountHeight();

    ValueType *search(KeyType Key);

    ValueType *to_array();

    binarynode<ValueType, KeyType> *find_max();

    binarynode<ValueType, KeyType> *find_min();

private:
    binarynode<ValueType, KeyType> *search(binarynode<ValueType, KeyType> *node, KeyType *Key);

    bool remove(binarynode<ValueType, KeyType> **node, KeyType *Key);

    ValueType*  ConvertToArray(binarynode<ValueType, KeyType> *node, ValueType *Array, int* position);

    binarynode<ValueType, KeyType> *CutMax(binarynode<ValueType, KeyType> **node);

    void RemoveAllNodes(binarynode<ValueType, KeyType> *node);

    int CountHeight(binarynode<ValueType, KeyType> *node, int MaxDeep, int Deep);
};

template<class ValueType, class KeyType>
BinaryTree<ValueType, KeyType>::BinaryTree() {
    root = nullptr;
    size = 0;
}

template<class ValueType, class KeyType>
BinaryTree<ValueType, KeyType>::BinaryTree(ValueType *Array, int SizeOfArray) {
    size = 0;
    for (int i = 0; i < SizeOfArray; i++)
        insert(Array[i], Array[i]);
}

template<class ValueType, class KeyType>
void BinaryTree<ValueType, KeyType>::RemoveAllNodes(binarynode<ValueType, KeyType> *node) {
    if (!node) {
        return;
    }
    RemoveAllNodes(node->left_node);
    RemoveAllNodes(node->right_node);
    delete node;
}

template<class ValueType, class KeyType>
inline BinaryTree<ValueType, KeyType>::~BinaryTree() {
    RemoveAllNodes(root);
}

template<class ValueType, class KeyType>
ValueType *BinaryTree<ValueType, KeyType>::search(KeyType Key) {
    return &search(root, &Key)->value;
}

template<class ValueType, class KeyType>
binarynode<ValueType, KeyType> *BinaryTree<ValueType, KeyType>::search(binarynode<ValueType, KeyType> *node, KeyType *Key) {
    if (!node) return nullptr;
    if (node->key == *Key) return node;
    return *Key < node->key ? search(node->left_node, Key) : search(node->right_node, Key);
}

template<class ValueType, class KeyType>
bool BinaryTree<ValueType, KeyType>::insert(KeyType Key, ValueType Value) {
    if (!size) {
        this->root = new binarynode<ValueType, KeyType>(Value, Key);
        size++;
        return true;
    }
    binarynode<ValueType, KeyType> **NodeToSwitch = &root;
    while (*NodeToSwitch) {
        if ((*NodeToSwitch)->value == Value || (*NodeToSwitch)->key == Key) {
            return false;
        }
        NodeToSwitch = Key < (*NodeToSwitch)->key ? &(*NodeToSwitch)->left_node : &(*NodeToSwitch)->right_node;
    }
    *NodeToSwitch = new binarynode<ValueType, KeyType>(Value, Key);
    size++;
    return true;
}

template<class ValueType, class KeyType>
bool BinaryTree<ValueType, KeyType>::remove(KeyType Key) {
    return remove(&root, &Key);
}

template<class ValueType, class KeyType>
bool BinaryTree<ValueType, KeyType>::remove(binarynode<ValueType, KeyType> **node, KeyType *Key) {
    if (!(*node)) return false;
    if ((*node)->key == *Key) {
        auto NodeToRemove = *node;
        size--;
        if (!(*node)->right_node) {
            *node = (*node)->left_node;
            delete NodeToRemove;
            return true;
        }
        if ((*node)->left_node) {
            *node = CutMax(&((*node)->left_node));
            (*node)->left_node = NodeToRemove->left_node;
            (*node)->right_node = NodeToRemove->right_node;
        } else {
            *node = (*node)->right_node;
        }
        delete NodeToRemove;
        return true;
    }
    if (*Key < (*node)->key) {
        remove(&((*node)->left_node), Key);
    } else {
        remove(&((*node)->right_node), Key);
    }
    return false;
}

template<class ValueType, class KeyType>
binarynode<ValueType, KeyType> *BinaryTree<ValueType, KeyType>::CutMax(binarynode<ValueType, KeyType> **node) {
    while ((*node)->right_node) {
        node = &((*node)->right_node);
    }
    binarynode<ValueType, KeyType> *NodeToCut = *node;
    *node = (*node)->left_node;
    return NodeToCut;
}

template<class ValueType, class KeyType>
ValueType *BinaryTree<ValueType, KeyType>::to_array() {
    ValueType *Array = new ValueType[size];
    int position{0};
    Array = ConvertToArray(root, Array, &position);
    return Array;
}

template<class ValueType, class KeyType>
ValueType* BinaryTree<ValueType, KeyType>::ConvertToArray(binarynode<ValueType, KeyType> *node, ValueType *Array, int* position) {
    if (node) {
        ConvertToArray(node->left_node, Array, position);
        Array[(*position)++] = node->value;
        ConvertToArray(node->right_node, Array, position);
    }
    return Array;
}

template<class ValueType, class KeyType>
binarynode<ValueType, KeyType> *BinaryTree<ValueType, KeyType>::find_max() {
    if (!size) {
        throw ("Error has been happened to get max value.\nThe binary tree doesn't have any BalancedNode");
    }
    auto NodeToSwitch = root;
    while (NodeToSwitch->right_node) {
        NodeToSwitch = NodeToSwitch->right_node;
    }
    return NodeToSwitch;
}

template<class ValueType, class KeyType>
binarynode<ValueType, KeyType> *BinaryTree<ValueType, KeyType>::find_min() {
    if (!size) {
        throw ("Error has been happened to get min value from the binary tree.\nThe binary tree doesn't have any BalancedNode");
    }
    auto NodeToSwitch = root;
    while (NodeToSwitch->left_node) {
        NodeToSwitch = NodeToSwitch->left_node;
    }
    return NodeToSwitch;
}

template<class ValueType, class KeyType>
bool BinaryTree<ValueType, KeyType>::insert(std::pair<ValueType, KeyType> node_data) {
    if (!size) {
        this->root = new binarynode<ValueType, KeyType>(node_data.first, node_data.second);
        size++;
        return true;
    }
    binarynode<ValueType, KeyType> **NodeToSwitch = &root;
    while (*NodeToSwitch) {
        if ((*NodeToSwitch)->value == node_data.first || (*NodeToSwitch)->key == node_data.second) {
            return false;
        }
        NodeToSwitch =
                node_data.second < (*NodeToSwitch)->key ? &(*NodeToSwitch)->left_node : &(*NodeToSwitch)->right_node;
    }
    *NodeToSwitch = new binarynode<ValueType, KeyType>(node_data.first, node_data.second);
    size++;
    return true;
}


template<class ValueType, class KeyType>
bool BinaryTree<ValueType, KeyType>::is_empty() {
    return !root;
}

template<class ValueType, class KeyType>
int BinaryTree<ValueType, KeyType>::CountHeight() {
    return CountHeight(root, 0, 0);
}

template<class ValueType, class KeyType>
int BinaryTree<ValueType, KeyType>::CountHeight(binarynode<ValueType, KeyType> *node, int MaxDeep, int Deep) {
    if (!node)
        return MaxDeep;
    if (!node->left_node && !node->right_node) {
        return MaxDeep <= Deep ? Deep : MaxDeep;
    }
    if (node->left_node)
        ++Deep;
    CountHeight(node->left_node, MaxDeep, Deep);
    if (node->right_node)
        ++Deep;
    CountHeight(node->right_node, MaxDeep, Deep);
}

template<class ValueType, class KeyType>
void BinaryTree<ValueType, KeyType>::clear() {
    RemoveAllNodes(root);
    root = nullptr;
    size = 0;
}
