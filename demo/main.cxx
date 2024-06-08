#include "libTree_Lib.hxx"
#include <iostream>
#include <string>

using namespace std;

int main() {
    int *array = new int[3]{100, -10, 50000};
    BinarySearchTree<int, std::less<int>> sorter(array, 3);
    sorter.sort();
    for (int i = 0; i < 3; ++i) {
        std::cout << sorter.at(i) << std::endl;
    }
    return EXIT_SUCCESS;
}