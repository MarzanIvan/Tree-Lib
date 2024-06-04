#include <gtest/gtest.h>
#include "BinaryTree.hxx"

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

