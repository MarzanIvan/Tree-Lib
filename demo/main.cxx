#include "libTree_Lib.hxx"
#include <iostream>
#include <string>

using namespace std;

template<
        class valtype,
        class keytype,
        class comparator
> void travers(custom::BalancedNode<valtype, keytype, comparator> *node) {
    if (node) {
        std::cout << "(" << node->getkey() << " key)" << "\n";
        travers(node->left);
        travers(node->right);
    }
}

template<
        class valtype,
        class keytype
> void inorder(binarynode<valtype, keytype> *node) {
    if (node) {
        inorder(node->left_node);
        std::cout << "(" << node->key << " key)" << "\n";
        inorder(node->right_node);
    }
}

template<
        class valtype,
        class keytype,
                class comparator
> void inorderbalanced(custom::BalancedNode<valtype, keytype,comparator> *node) {
    if (node) {
        inorderbalanced(node->left);
        std::cout << "(" << node->getkey() << " key)" << "\n";
        inorderbalanced(node->right);
    }
}

const vector<string> mainmenu{"1) Use Binary Search Tree",
                               "2) Use Unique Binary Tree",
                               "3) Use Balanced Binary Tree",
                               "4) Exit app"};

enum MAINMENU {
    OPTIONBinarySearchTree = 1, OPTIONUniqueBinaryTree, OPTIONBalancedBinaryTree, EXIT
};

enum TreeOptions{
    ADD = 1, REMOVE, FIND, SORT, EXITFROM
};

void UniqueBinaryTreeMenu(int choose, vector<string>* OptionsForTree) {
    std::cout << "Press key...";
    cin.get();
    int TreeOptionChoose{0};
    static BinaryTree<int,int> numbers;
    while (TreeOptionChoose != 5) {
        std::cout << "\nUnique Binary Tree menu:\n";
        for (auto option: *OptionsForTree) {
            std::cout << option << std::endl;
        }
        std::cout << "Choose option: ";
        cin >> TreeOptionChoose;
        cout << "You choose " << OptionsForTree->operator[](choose - 1) << '\n';
        cin.get();
        switch(TreeOptionChoose) {
            case (ADD): {
                int value{0};
                int key{0};
                cout << "enter value: ";
                std::cin >> value;
                cout << "\nenter key: ";
                std::cin >> key;
                if (numbers.insert(key,value)) {
                    cout    << "node with key "
                            << key
                            << " and value "
                            << value
                            << " was added\nTree size: "
                            << numbers.size
                            << "\n\n";
                }
                break;
            }
            case (REMOVE): {
                int key{0};
                cout << "enter key to delete node: ";
                cin >> key;
                if (numbers.remove(key)) {
                    cout    << "node with key "
                            << key
                            << " was removed\nTree size: "
                            << numbers.size
                            << "\n\n";
                }
                break;
            }
            case (FIND): {
                int key{0};
                cout << "enter node key to get search: ";
                cin >> key;
                auto value = numbers.search(key);
                if (!value) {
                    cout << "Node wasn't found in tree\n";
                } else {
                    cout << *value << " value was found\n";
                }
                cout << "Press key...";
                cin.get();
                break;
            }
            case (SORT): {
                cout << '\n';
                cout << "Sorted values: \n";
                auto array = numbers.to_array();
                for (int i = 0; i < numbers.size; ++i) {
                    cout << array[i] << ' ';
                }
                cout << '\n';
                cin.get();
                break;
            }
            case (EXITFROM): {
                break;
            }
        }
    }
}

void BalancedBinaryTree(int choose, vector<string>* OptionsForTree) {
    std::cout << "Press key...";
    cin.get();
    int TreeOptionChoose{0};
    static custom::BalancedBinaryTree<int,int, greater<int>> numbers;
    while (TreeOptionChoose != 5) {
        std::cout << "\nBalanced Binary Tree menu:\n";
        for (auto option: *OptionsForTree) {
            std::cout << option << std::endl;
        }
        std::cout << "Choose option: ";
        cin >> TreeOptionChoose;
        cout << "You choose " << OptionsForTree->operator[](choose - 1) << '\n';
        cin.get();
        switch(TreeOptionChoose) {
            case (ADD): {
                int value{0};
                int key{0};
                cout << "enter value: ";
                std::cin >> value;
                cout << "\nenter key: ";
                std::cin >> key;
                if (numbers.insert(key,value)) {
                    cout    << "node with key "
                            << key
                            << " and value "
                            << value
                            << " was added\nTree size: "
                            << numbers.size
                            << "\n\n";
                }
                break;
            }
            case (REMOVE): {
                int key{0};
                cout << "enter key to delete node: ";
                cin >> key;
                if (numbers.remove(key)) {
                    cout    << "node with key "
                            << key
                            << " was removed\nTree size: "
                            << numbers.size
                            << "\n\n";
                }
                break;
            }
            case (FIND): {
                int key{0};
                cout << "enter node key to get search: ";
                cin >> key;
                auto value = numbers.search(key);
                if (!value) {
                    cout << "Node wasn't found in tree\n";
                } else {
                    cout << *value << " value was found\n";
                }
                cout << "\nPress key...";
                cin.get();
                break;
            }
            case (SORT): {
                cout << '\n';
                cout << "Sorted values: \n";
                auto array = numbers.to_array();
                for (int i = 0; i < numbers.size; ++i) {
                    cout << array[i] << ' ';
                }
                cout << '\n';
                cin.get();
                break;
            }
            case (EXITFROM): {
                break;
            }
        }
    }
}

custom::BinarySearchTree<int, std::greater<int>> binaryheap;

void BinarySearchTreeMenu(int choose, vector<string>* OptionsForTree) {
    std::cout << "Press key...";
    cin.get();
    int TreeOptionChoose{0};
    while (TreeOptionChoose != 5) {
        std::cout << "\nBinary Search Tree menu:\n";
        for (auto option: *OptionsForTree) {
            std::cout << option << std::endl;
        }
        std::cout << "Choose option: ";
        cin >> TreeOptionChoose;
        cout << "You choose " << OptionsForTree->operator[](choose - 1) << '\n';
        cin.get();
        switch(TreeOptionChoose) {
            case (ADD): {
                int value{0};
                cout << "enter value: ";
                std::cin >> value;
                if (binaryheap.insert(value)) {
                    cout    << "node with value "
                            << value
                            << " was added\nTree size: "
                            << binaryheap.getsize()
                            << "\n\n";
                }
                break;
            }
            case (REMOVE): {
                int index{0};
                cout << "enter index to delete node: ";
                cin >> index;
                cout << "\nAttempt to remove " << binaryheap.at(index) << " value from tree";
                if (binaryheap.remove(index)) {
                    cout    << "node with key "
                            << index
                            << " was removed\nTree size: "
                            << binaryheap.getsize()
                            << "\n\n";
                }
                break;
            }
            case (FIND): {
                int key{0};
                cout << "enter node key to get search: ";
                cin >> key;
                auto value = binaryheap.search(key);
                if (!value) {
                    cout << "Node wasn't found in tree\n";
                } else {
                    cout << *value << " value was found\n";
                }
                cout << "\nPress key...";
                cin.get();
                break;
            }
            case (SORT): {
                binaryheap.sort();
                std::cin.clear();
                cout << "Sorted values: ";
                for (int i = 0; i < binaryheap.getsize(); ++i) {
                    std::cout << binaryheap.at(i) << ' ';
                }
                binaryheap.rebuildheap();
                cout << '\n';
                cin.get();
                break;
            }
            case (EXITFROM): {
                break;
            }
            default:
                std::cout << "Option not found(";
                std::cin.get();
        }
    }
}

int main() {
    int choose{-1};
    cout << "Hello to demo project!\nProject provides: \n* Binary Search Tree\n* Unique Binary Tree\n* AVL Tree\n";
    cout << "\nPress key to switch in menu...";
    cin.get();
    try {
        while (choose != EXIT) {
            vector<string> OptionsForTree{"1) add element",
                                          "2) delete element",
                                          "3) find element",
                                          "4) get sorted collection",
                                          "5) exit"};
            for (auto option: mainmenu) {
                cout << option << '\n';
            }
            cout << "Choose option: ";
            cin >> choose;
            cout << "\nYour choose is option: " << choose << '\n';
            if (choose >= 1 && choose <= 4) {
                cout << "You choose " << mainmenu[choose - 1] << '\n';
            }
            cin.clear();
            cin.get();
            cin.clear();
            switch (choose) {
                case (OPTIONBinarySearchTree): {
                    BinarySearchTreeMenu(choose,&OptionsForTree);
                    break;
                }
                case (OPTIONUniqueBinaryTree):
                    UniqueBinaryTreeMenu(choose,&OptionsForTree);
                    break;
                case (OPTIONBalancedBinaryTree):
                    BalancedBinaryTree(choose,&OptionsForTree);
                    break;
                case (EXIT):
                    std::cout << "Press key...";
                    return EXIT_SUCCESS;
                default:
                    std::cerr << "Option not found(";
                    cin.get();
            }
        }
    } catch (...) {
        std::cerr << "something went wrong";
    }

    return EXIT_SUCCESS;
}