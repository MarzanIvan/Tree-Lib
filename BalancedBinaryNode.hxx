#pragma once

#include <iostream>
#include <memory>

namespace custom {

    template<class valtype, class comparator>
    class BalancedNode {
    private:
        std::unique_ptr<valtype> value;
        const comparator comp; //custom comparator

    public:
        signed char balance;
        std::shared_ptr<BalancedNode<valtype, comparator>> left;
        std::shared_ptr<BalancedNode<valtype, comparator>> right;

    public:
        explicit BalancedNode(valtype value, char balance = 0, BalancedNode<valtype, comparator> *left = nullptr,
                              BalancedNode<valtype, comparator> *right = nullptr) : value(value), balance(balance),
                                                                                    left(left), right(right) {
            /*to use initializer list constructor*/
        }// other converting is prohibited

        BalancedNode() = delete; // empty object mustn't exist

        const valtype &getvalue() const {
            return *value;
        }

        ~BalancedNode() {
            value.reset();
            left.reset();
            right.reset();
        }

        // set pointer of left BalancedNode (delete nullptr(worthless) and set pointer)
        void setleft(BalancedNode<valtype, comparator> *child) {
            left.reset(child);
        }

        // set pointer of right BalancedNode (delete nullptr(worthless) and set pointer)
        void setright(BalancedNode<valtype, comparator> *child) {
            right.reset(child);
        }

        // swap nodes to exchange pointers
        void swapleft(std::unique_ptr<BalancedNode<valtype, comparator>> &child) {
            left.swap(child);
        }

        // swap nodes to exchange pointers
        void swapright(std::unique_ptr<BalancedNode<valtype, comparator>> &child) {
            right.swap(child);
        }

        // (using ref) to support lambda, functor and pointer function comparators
        bool compare(const BalancedNode<valtype, comparator> &arg) {
            return comp(*this->value.get(), *arg.value.get());
        }

        // (using pointer) to support lambda, functor and pointer function comparators
        bool compare(const BalancedNode<valtype, comparator> *arg) {
            return comp(*this->value.get(), *arg->value.get());
        }

        BalancedNode(const BalancedNode &copy) = delete;

        BalancedNode &operator=(const BalancedNode &arg) = delete;

    };
}