#include <gtest/gtest.h>
#include "libTree_Lib.hxx"

TEST(BinaryTree, insert) {
    BinaryTree<std::string, int> storage;
    std::string stringtoinsert{"some string"};
    auto valuekey{10};
    storage.insert(valuekey, stringtoinsert);
    EXPECT_EQ(stringtoinsert, *storage.search(valuekey));
}

TEST(BinaryTree, remove) {
    BinaryTree<std::string, int> storage;
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
    EXPECT_EQ(sorter.at(0), -10);
    EXPECT_EQ(sorter.at(1), 100);
    EXPECT_EQ(sorter.at(2), 50000);
}
#include <cmath>
TEST(binarysearchtree, rebuildheap) {
    const int sizecollection = 10;

    int *array = new int[10]{0};
    for (int i = 0; i < sizecollection; ++i) {
        array[i] = rand() % 100;
    }

    BinarySearchTree<int, std::greater<int>> storage(array, sizecollection);
    int* heap = new int[sizecollection]{0};
    for (int i = 0; i < sizecollection; ++i) {
        heap[i] = storage.at(i);
    }
    storage.sort();
    storage.rebuildheap();
    for (int i = 0; i < sizecollection; ++i) {
        int max{0};
        int maxindex{0};
        for (int j = 0; j < sizecollection; ++j) {
            if (array[j] >= max) {
                max = array[j];
                maxindex = j;
            }
        }
        array[maxindex] = -1000000;
        EXPECT_EQ(max, storage.at(0));
        storage.remove(0);
    }
    EXPECT_EQ(0, storage.getsize());

}

TEST(binarysearchtree, inserting) {
    BinarySearchTree<int, std::less<int>> storage;
    storage.insert(5);
    EXPECT_EQ(5, storage.at(0));
}

TEST(binarysearchtree, getmax) {
    BinarySearchTree<int, std::greater<int>> storage;
    storage.insert(5);
    storage.insert(10);
    storage.insert(-1000);
    storage.insert(-500);
    EXPECT_EQ(10, storage.max());
}


TEST(binarysearchtree, removing) {
    BinarySearchTree<int, std::greater<int>> storage;
    storage.insert(5);
    storage.insert(15);
    storage.insert(25);
    storage.remove(0);
    EXPECT_EQ(storage.at(0), 15);
}

TEST(binarysearchtree, removeall) {
    BinarySearchTree<int, std::greater<int>> storage;
    storage.insert(5);
    storage.insert(15);
    storage.insert(25);
    storage.clear();
    EXPECT_EQ(storage.getsize(), 0);
}


TEST(binarysearchtree, removeroot) {
    BinarySearchTree<int, std::greater<int>> storage;
    storage.insert(5);
    storage.insert(15);
    storage.insert(25);
    storage.removeroot();
    EXPECT_EQ(storage.at(0), 15);
}
