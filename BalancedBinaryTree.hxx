#pragma once

#include <stdint.h>
#include "BalancedBinaryNode.hxx"

namespace custom {
    
    template<
            class valtype,
            class keytype,
            class comparator = std::less <keytype> //to support lambda, function pointer and functor to compare node keys
    > class BalancedBinaryTree {
    public:
        intmax_t size;
        custom::BalancedNode<valtype, keytype, comparator> *head;

        BalancedBinaryTree() {
            size = 0;
            head = nullptr;
        }

        BalancedBinaryTree(custom::BalancedNode<valtype, keytype, comparator> *head) : head{
                new custom::BalancedNode<valtype, keytype, comparator>(head)}, size{1} {
            /*...*/
        }

        BalancedBinaryTree(valtype *value, keytype *key) : head{
                new custom::BalancedNode<valtype, keytype, comparator>(*value, *key)}, size{1} {
            /*...*/
        }

        const intmax_t &getsize() {
            return size;
        }


        BalancedNode<valtype, keytype, comparator> *
        singleRightRotate(custom::BalancedNode<valtype, keytype, comparator> *UnbalancedNode);

        custom::BalancedNode<valtype, keytype, comparator> *
        doubleRightRotate(custom::BalancedNode<valtype, keytype, comparator> *t);

        custom::BalancedNode<valtype, keytype, comparator> *
        singleLeftRotate(custom::BalancedNode<valtype, keytype, comparator> *UnbalancedNode);

        custom::BalancedNode<valtype, keytype, comparator> *
        doubleLeftRotate(custom::BalancedNode<valtype, keytype, comparator> *t);


        bool insert(valtype value, keytype key);
        bool remove(keytype key);
        const valtype* search(keytype key);
        valtype* to_array();
        bool is_empty() {
            return (bool)size;
        }
        void clear() {
            RemoveNodes(head);
            size = 0;
            head = nullptr;
        }
        custom::BalancedNode<valtype, keytype, comparator>* GetMin(custom::BalancedNode<valtype, keytype, comparator>* node);
    private:
        void RemoveNodes(custom::BalancedNode<valtype, keytype, comparator>* node);
        void to_array(custom::BalancedNode<valtype, keytype, comparator>* node, valtype* array, int* position);
        custom::BalancedNode<valtype, keytype, comparator>* RestoreBalanceAfterRemovedNode(custom::BalancedNode<valtype, keytype, comparator>* node);
        custom::BalancedNode<valtype, keytype, comparator>* CutMax(custom::BalancedNode<valtype, keytype, comparator>** node);
        custom::BalancedNode<valtype, keytype, comparator>* remove(custom::BalancedNode<valtype, keytype, comparator>** node,keytype* key);
        custom::BalancedNode<valtype, keytype, comparator>* recursiveinsert(custom::BalancedNode<valtype, keytype, comparator> *node, valtype *value, keytype *key);
        int countbalance(custom::BalancedNode<valtype, keytype, comparator>* node);
        int countheight(custom::BalancedNode<valtype, keytype, comparator>* node);

    };

}

template<
        class valtype,
        class keytype,
        class comparator
> void custom::BalancedBinaryTree<valtype, keytype, comparator>::RemoveNodes(custom::BalancedNode<valtype, keytype, comparator>* node) {
    if (!node) {
        return;
    }
    RemoveNodes(node->left);
    RemoveNodes(node->right);
    delete node;
}

template<
        class valtype,
        class keytype,
        class comparator
> valtype* custom::BalancedBinaryTree<valtype, keytype, comparator>::to_array() {
    valtype* array = new valtype[size];
    int position{0};
    to_array(head, array, &position);
    return array;
}

template<
        class valtype,
        class keytype,
        class comparator
> void custom::BalancedBinaryTree<valtype, keytype, comparator>::to_array(custom::BalancedNode<valtype, keytype, comparator>* node, valtype* array, int* position) {
    if (node) {
        to_array(node->left, array, position);
        array[(*position)++] = node->getvalue();
        to_array(node->right, array, position);
    }
}

template<
        class valtype,
        class keytype,
        class comparator
> const valtype* custom::BalancedBinaryTree<valtype, keytype, comparator>::search(keytype key) {
    auto iter = head;
    auto pkey = &key;
    while(iter) {
        if (iter->getkey() == *pkey)
            return &iter->getvalue();
        iter = iter->key_compare(&key) ? iter->left : iter->right;
    }
    return nullptr;
}

template<
        class valtype,
        class keytype,
        class comparator
> custom::BalancedNode<valtype, keytype, comparator>* custom::BalancedBinaryTree<valtype, keytype, comparator>::GetMin(custom::BalancedNode<valtype, keytype, comparator>* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template<
        class valtype,
        class keytype,
        class comparator
> custom::BalancedNode<valtype, keytype, comparator>* custom::BalancedBinaryTree<valtype, keytype, comparator>::RestoreBalanceAfterRemovedNode(custom::BalancedNode<valtype, keytype, comparator>* node) {
    if (!node) return node;

    node->height = 1 + std::max(countheight(node->left), countheight(node->right));
    int balance = countbalance(node);

    if (balance > 1 && countbalance(node->left) >= 0)
        return singleRightRotate(node);
    if (balance > 1 && countbalance(node->left) < 0) {
        node->left = singleLeftRotate(node->left);
        return singleRightRotate(node);
    }
    if (balance < -1 && countbalance(node->right) <= 0) {
        return singleLeftRotate(node);
    }
    if (balance < -1 && countbalance(node->right) > 0) {
        node->right = singleRightRotate(node->right);
        return singleLeftRotate(node);
    }
    return node;
}

template<
        class valtype,
        class keytype,
        class comparator
> bool custom::BalancedBinaryTree<valtype, keytype, comparator>::remove(keytype key) {
    /*if (!size) return false;
    int savedsize = size;*/
    head = remove(&head,&key);
    return true;
    /*if (savedsize != size) {
        return true;
    }
    return false;*/
}

template<
        class valtype,
        class keytype,
        class comparator
> custom::BalancedNode<valtype, keytype, comparator> *custom::BalancedBinaryTree<valtype, keytype, comparator>::CutMax(
        custom::BalancedNode<valtype, keytype, comparator> **node) {
    if(!(*node)->left)
        return (*node)->right;
    (*node)->left = CutMax(&(*node)->left);
    return *node;
}

template<
        class valtype,
        class keytype,
        class comparator
> custom::BalancedNode<valtype, keytype, comparator>* custom::BalancedBinaryTree<valtype, keytype, comparator>::remove(custom::BalancedNode<valtype, keytype, comparator>** node, keytype* key) {
    if (!(*node)) return nullptr;
    if ((*node)->key_compare(key)) {
        (*node)->left = remove(&((*node)->left), key);
    } else if ((*node)->getkey() == *key) {
        --size;
        auto left = (*node)->left;
        auto right = (*node)->right;
        delete *node;
        *node = nullptr;
        if (!right) {
            *node = left;
            return RestoreBalanceAfterRemovedNode(*node);
        }
        auto min = GetMin(right);
        min->right = CutMax(&right);
        min->left = left;
        return RestoreBalanceAfterRemovedNode(min);
    } else {
        (*node)->right = remove(&((*node)->right), key);
    }
    return RestoreBalanceAfterRemovedNode(*node);
}

template<
        class valtype,
        class keytype,
        class comparator
> int custom::BalancedBinaryTree<valtype, keytype, comparator>::countheight(custom::BalancedNode<valtype, keytype, comparator>* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

template<
        class valtype,
        class keytype,
        class comparator
> int custom::BalancedBinaryTree<valtype, keytype, comparator>::countbalance(custom::BalancedNode<valtype, keytype, comparator>* node) {
    if (node == nullptr)
        return 0;
    return countheight(node->left) - countheight(node->right);
}

template<
        class valtype,
        class keytype,
        class comparator
> bool custom::BalancedBinaryTree<valtype, keytype, comparator>::insert(valtype value, keytype key) {
    auto root = recursiveinsert(head, &value, &key);
    if (root) {
        head = root;
    }
    return (bool)root;
}

template<
        class valtype,
        class keytype,
        class comparator
> custom::BalancedNode<valtype, keytype, comparator> *
custom::BalancedBinaryTree<valtype, keytype, comparator>::recursiveinsert(
        custom::BalancedNode<valtype, keytype, comparator> *node, valtype *value, keytype *key) {
    if (!node) {
        node = new custom::BalancedNode<valtype, keytype, comparator>(*value, *key, 1);
        ++size;
        return node;
    }

    if (node->key_compare(key)) {
        node->left = recursiveinsert(node->left, value, key);
    } else if (node->getkey() == *key) {
        return nullptr;
    } else {
        node->right = recursiveinsert(node->right, value, key);
    }

    node->height = 1 + std::max(countheight(node->left), countheight(node->right));
    int balance = countbalance(node);

    if (balance > 1 && node->left->key_compare(key)) {
        return singleRightRotate(node);
    }
    if (balance < -1 && node->right->key_compare(key)) {
        node->right = singleRightRotate(node->right);
        return singleLeftRotate(node);
    }
    if (balance < -1 && !node->right->key_compare(key)) {
        return singleLeftRotate(node);
    }
    if (balance > 1 && !node->left->key_compare(key)) {
        node->left = singleLeftRotate(node->left);
        return singleRightRotate(node);
    }
    return node;
}


template<
        class valtype,
        class keytype,
        class comparator
>
custom::BalancedNode<valtype, keytype, comparator> *
custom::BalancedBinaryTree<valtype, keytype, comparator>::singleRightRotate(
        custom::BalancedNode<valtype, keytype, comparator> *UnbalancedNode) {
    custom::BalancedNode<valtype, keytype, comparator> *NewParentOfUnbalanced = UnbalancedNode->left;
    UnbalancedNode->left = NewParentOfUnbalanced->right;
    NewParentOfUnbalanced->right = UnbalancedNode;

    UnbalancedNode->height = std::max(countheight(UnbalancedNode->left), countheight(UnbalancedNode->right)) + 1;
    NewParentOfUnbalanced->height = std::max(countheight(NewParentOfUnbalanced->left), countheight(NewParentOfUnbalanced->right)) + 1;
    return NewParentOfUnbalanced;
}


template<
        class valtype,
        class keytype,
        class comparator
>
custom::BalancedNode<valtype, keytype, comparator> *
custom::BalancedBinaryTree<valtype, keytype, comparator>::singleLeftRotate(
        custom::BalancedNode<valtype, keytype, comparator> *UnbalancedNode) {
    custom::BalancedNode<valtype, keytype, comparator> *NewParentOfUnbalanced = UnbalancedNode->right;
    UnbalancedNode->right = NewParentOfUnbalanced->left;
    NewParentOfUnbalanced->left = UnbalancedNode;
    UnbalancedNode->height = 1 + std::max(countheight(UnbalancedNode->left), countheight(UnbalancedNode->right));
    NewParentOfUnbalanced->height = 1 + std::max(countheight(NewParentOfUnbalanced->left), countheight(NewParentOfUnbalanced->right));
    return NewParentOfUnbalanced;
}


template<
        class valtype,
        class keytype,
        class comparator
>
custom::BalancedNode<valtype, keytype, comparator> *
custom::BalancedBinaryTree<valtype, keytype, comparator>::doubleLeftRotate(
        custom::BalancedNode<valtype, keytype, comparator> *t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}


template<
        class valtype,
        class keytype,
        class comparator
>
custom::BalancedNode<valtype, keytype, comparator> *
custom::BalancedBinaryTree<valtype, keytype, comparator>::doubleRightRotate(
        custom::BalancedNode<valtype, keytype, comparator> *t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

