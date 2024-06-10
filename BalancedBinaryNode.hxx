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
        const comparator comp; //custom comparator

    public:
        signed char balance;
        std::shared_ptr<BalancedNode<valtype, keytype, comparator>> left;
        std::shared_ptr<BalancedNode<valtype, keytype, comparator>> right;

    public:
        explicit BalancedNode(valtype value, keytype key, char balance = 0, BalancedNode<valtype, keytype, comparator> *left = nullptr,
                              BalancedNode<valtype, keytype, comparator> *right = nullptr) : value(value), key(key), balance(balance),
                                                                                    left(left), right(right) {
            /*to use initializer list constructor*/
        }// other converting is prohibited

        BalancedNode() = delete; // empty object mustn't exist

        const valtype &getvalue() const {
            return *value.get();
        }

        const keytype& getkey() const {
            return *key.get();
        }

        ~BalancedNode() {
            value.reset();
            left.reset();
            right.reset();
        }

        // set pointer of left BalancedNode (delete nullptr(worthless) and set pointer)
        void setleft(BalancedNode<valtype, keytype, comparator> *child) {
            left.reset(child);
        }

        // set pointer of right BalancedNode (delete nullptr(worthless) and set pointer)
        void setright(BalancedNode<valtype, keytype, comparator> *child) {
            right.reset(child);
        }

        // swap nodes to exchange pointers
        void swapleft(std::unique_ptr<BalancedNode<valtype, keytype, comparator>> &child) {
            left.swap(child);
        }

        // swap nodes to exchange pointers
        void swapright(std::unique_ptr<BalancedNode<valtype, keytype, comparator>> &child) {
            right.swap(child);
        }

        // (using ref) to support lambda, functor and pointer function comparators
        bool compare(const BalancedNode<valtype, keytype, comparator> &arg) {
            return comp(*this->key.get(), *arg.key.get());
        }

        // (using pointer) to support lambda, functor and pointer function comparators
        bool compare(const BalancedNode<valtype, keytype, comparator> *arg) {
            return comp(*this->key.get(), *arg->key.get());
        }

        BalancedNode(const BalancedNode &copy) = delete;

        BalancedNode &operator=(const BalancedNode &arg) = delete;

    };
}