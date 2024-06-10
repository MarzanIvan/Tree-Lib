#pragma once

#include <stdint.h>
#include "BalancedBinaryNode.hxx"

namespace custom {

    template<
            class valtype,
            class keytype,
            class comparator = std::less<keytype> //to support lambda, function pointer and functor to compare node keys
    > class BalancedBinaryTree {
        //shared_ptr is used to be able to switch over nodes
        std::shared_ptr<custom::BalancedNode<valtype, keytype, comparator>> head;
        intmax_t size;
    public:

        BalancedBinaryTree() {
            size = 0;
            head.reset(nullptr);
        }

        BalancedBinaryTree(custom::BalancedNode<valtype, keytype, comparator> *head) : head{head}, size{1} {
            /*...*/
        }

        BalancedBinaryTree(valtype *value, keytype* key) : head{new custom::BalancedNode<valtype, keytype, comparator>(*value, *key)}, size{1} {
            /*...*/
        }

        const intmax_t& getsize() {
            return size;
        }



        bool insert(valtype value);
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

template<class valtype, class keytype, class comparator>
bool custom::BalancedBinaryTree<valtype, keytype, comparator>::insert(valtype value) {

}
// custom
/*
BalancedNode* singleRightRotate(BalancedNode* &t)
{
    BalancedNode* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}
BalancedNode* singleLeftRotate(BalancedNode* &t)
{
    BalancedNode* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

BalancedNode* doubleLeftRotate(BalancedNode* &t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}
BalancedNode* doubleRightRotate(BalancedNode* &t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}
*/
