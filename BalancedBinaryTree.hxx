#pragma once

#include <stdint.h>
#include "BalancedBinaryNode.hxx"

namespace custom {

    template<
            class valtype,
            class keytype,
            class comparator = std::less <keytype> //to support lambda, function pointer and functor to compare node keys
    >
    class BalancedBinaryTree {
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
        singleRightRotate(custom::BalancedNode<valtype, keytype, comparator> *t);

        custom::BalancedNode<valtype, keytype, comparator> *
        doubleRightRotate(custom::BalancedNode<valtype, keytype, comparator> *t);

        custom::BalancedNode<valtype, keytype, comparator> *
        singleLeftRotate(custom::BalancedNode<valtype, keytype, comparator> *t);

        custom::BalancedNode<valtype, keytype, comparator> *
        doubleLeftRotate(custom::BalancedNode<valtype, keytype, comparator> *t);


        bool insert(valtype value, keytype key);

    private:
        custom::BalancedNode<valtype, keytype, comparator>* recursiveinsert(custom::BalancedNode<valtype, keytype, comparator> *node, valtype *value, keytype *key);
        int countbalance(custom::BalancedNode<valtype, keytype, comparator>* node);
        int countheight(custom::BalancedNode<valtype, keytype, comparator>* node);
        /*
        void remove(valtype value);

        valtype search(valtype value);

        void clear();

        void removeallnodes();

        bool is_empty();

        valtype find_max();

        valtype find_min();

        valtype *to_array();

        intmax_t get_size();*/
        /*
         * insert
         * remove
         * search
         * clear
         * removeallnodes
         * isempty
         * find_max
         * find_min
         * to_array
         * size
         * operator[key]
         * singlerightrotate
         * singleleftrotate
         * doubleleftrotate
         * doublerightrotate
         */

        //to remove BalancedNode by unique we use release()


    };

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
    if (node == NULL)
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
        custom::BalancedNode<valtype, keytype, comparator> *t) {
    std::cout << "right rotation\n";
    custom::BalancedNode<valtype, keytype, comparator> *x = t->left;
    custom::BalancedNode<valtype, keytype, comparator> *T2 = x->right;
    /* t->left = x->right;
     x->right = t;*/

    // Perform rotation
    x->right = t;
    t->left = T2;

    t->height = std::max(countheight(t->left), countheight(t->right)) + 1;
    x->height = std::max(countheight(x->left), countheight(x->right)) + 1;
    return x;
}


template<
        class valtype,
        class keytype,
        class comparator
>
custom::BalancedNode<valtype, keytype, comparator> *
custom::BalancedBinaryTree<valtype, keytype, comparator>::singleLeftRotate(
        custom::BalancedNode<valtype, keytype, comparator> *t) {
    custom::BalancedNode<valtype, keytype, comparator> *y = t->right;
/*
    t->right = y->left;
    y->left = t;*/
    std::cout << "left rotation\n";
    custom::BalancedNode<valtype, keytype, comparator> *T2 = y->left;

    // Perform rotation
    y->left = t;
    t->right = T2;

    t->height = 1 + std::max(countheight(t->left), countheight(t->right));
    y->height = 1 + std::max(countheight(y->left), countheight(y->right));

    return y;
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

