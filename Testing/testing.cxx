#include <gtest/gtest.h>
#include "BinaryTree.hxx"
#include "BinarySearchTree.hxx"


TEST(uniquebinarytrexe, insert) {
    binarytree<std::string, int> storage;
    std::string stringtoinsert{"some string"};
    auto valuekey{10};
    storage.insert(valuekey, stringtoinsert);
    EXPECT_EQ(stringtoinsert, *storage.search(valuekey));
}

TEST(uniquebinarytree, remove) {
    binarytree<std::string, int> storage;
    std::string stringtoinsert{"some string"};
    auto valuekey{10};
    storage.insert(valuekey, stringtoinsert);
    storage.remove(valuekey, stringtoinsert);
    EXPECT_EQ(nullptr, storage.search(valuekey));
}

TEST(binarysearchtree, sorting) {
    int *array = new int[3]{100, -10, 50000};
    BinarySearchTree<int, std::less<int>> sorter(array, 3);
    sorter.sort();
    EXPECT_EQ(sorter.at(0), 50000);
    EXPECT_EQ(sorter.at(1), 100);
    EXPECT_EQ(sorter.at(2), -10);
}