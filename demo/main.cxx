#include "libTree_Lib.hxx"
#include <iostream>
#include <string>

using namespace std;

template<
        class valtype,
        class keytype,
        class comparator
> void travers(custom::BalancedNode<valtype, keytype, comparator> *node) {
    if (node != NULL) {
        std::cout << "(" << node->getkey() << " key)" << "\n";
        travers(node->left);
        travers(node->right);
    }
}

int main() {
    custom::BalancedBinaryTree<int, int, std::greater<int>> map;
    map.insert(10,10);
    map.insert(20,20);
    map.insert(30,30);
    map.insert(40,40);
    map.insert(50,50);
    map.insert(60,60);

    map.remove(30);
    map.remove(10);
    map.remove(60);
    std::cout << "something\n";
    travers(map.head);
    std::cout << "  " << map.head->getkey() << '\n';
    std::cout << map.head->right->getkey() << "  " << map.head->left->getkey() << std::endl;
    std::cout << "\nEXIT\n";
    return EXIT_SUCCESS;
}