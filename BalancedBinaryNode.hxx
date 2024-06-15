#pragma once

#include <iostream>
#include <memory>

namespace custom {

    template<
            class valtype,
            class keytype,
            class comparator = std::less<keytype>
    > class BalancedNode {
    private:
        //unique_ptr is used to support RAII
        std::unique_ptr<valtype> value;
        std::unique_ptr<keytype> key;
        //to support lambda, function pointer and functor to compare keys
        comparator comp; //custom comparator

    public:
        //balance acceptable values are range [-1, +1]
        int height;
        BalancedNode<valtype, keytype, comparator>* left;
        BalancedNode<valtype, keytype, comparator>* right;

    public:
        explicit BalancedNode(valtype value, keytype key, int height = 1, BalancedNode<valtype, keytype, comparator> *left = nullptr,
                              BalancedNode<valtype, keytype, comparator> *right = nullptr) : value(new valtype(value)), key(new keytype(key)),height(height),
                                                                                    left(left), right(right) {
            /*to use initializer list constructor*/
        }// other converting is prohibited

        BalancedNode() = delete; // empty object mustn't exist

        const valtype &getvalue() const {
            return *value.get();
        }

        const int& getheight() const {
            return height;
        }

        const keytype& getkey() const {
            return *key.get();
        }

        ~BalancedNode() {
            key.reset();
            value.reset();
        }

        // set pointer of left BalancedNode (delete nullptr(worthless) and set pointer)
        void setleft(BalancedNode<valtype, keytype, comparator> *child) {
            left = child;
        }

        // set pointer of right BalancedNode (delete nullptr(worthless) and set pointer)
        void setright(BalancedNode<valtype, keytype, comparator> *child) {
            right = child;
        }

        // (using ref) to support lambda, functor and pointer function comparators
        bool compare(const BalancedNode<valtype, keytype, comparator> &arg) {
            return comp(*this->key.get(), *arg.key.get());
        }

        bool key_compare(const keytype* key) {
            return comp(*this->key.get(), *key);
        }

        // (using pointer) to support lambda, functor and pointer function comparators
        bool compare(const BalancedNode<valtype, keytype, comparator> *arg) {
            return comp(*this->key.get(), *arg->key.get());
        }

        BalancedNode(const BalancedNode &copy) = delete;

        BalancedNode &operator=(const BalancedNode &arg) = delete;

    };
}