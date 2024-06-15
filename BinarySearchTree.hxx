/*
	Copyright (C) 2023 Marzan Ivan
 	Binary Search Tree program header
	GNU GENERAL PUBLIC LICENSE v3.0
*/

#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

namespace custom {

    template<class valtype, class comparator>
    class BinarySearchTree {
    private:
        std::unique_ptr <std::vector<valtype>> heap;
        comparator comp; //custom comparator
        size_t size;

    public:
        BinarySearchTree() {
            heap.reset(new std::vector<valtype>());
            size = 0;
        }

        explicit BinarySearchTree(valtype *array, size_t size, size_t freesize = 0) {
            this->size = size;
            std::vector <valtype> *newheap = new std::vector<valtype>();
            newheap->reserve(size + freesize);
            newheap->assign(array, array + size);
            this->heap.reset(newheap);
            for (int i = (size >> 1) - 1; i >= 0; i--) {
                heapify(i, this->size);
            }
        }

        ~BinarySearchTree() {
            heap.reset();
        }

        BinarySearchTree(const BinarySearchTree &copy) = delete;

        BinarySearchTree &operator=(BinarySearchTree &arg) = delete;

        void rebuildheap();

        valtype at(int index);

        void heapify(int index, int size);

        void heapifybyparent(int index, int size);

        void sort();

        void insert(valtype value);

        valtype max();

        bool remove(int index);

        void clear();

        void removeroot();

        const int getsize() {
            return size;
        }

        std::vector<int>::iterator begin();

        std::vector<int>::iterator end();


        const int capacity() {
            return heap.get()->capacity();
        }
    };

    template<class valtype, class comparator>
    void BinarySearchTree<valtype, comparator>::rebuildheap() {
        for (int i = (size >> 1) - 1; i >= 0; i--) {
            heapify(i, this->size);
        }
    }

    template<class valtype, class comparator>
    void BinarySearchTree<valtype, comparator>::clear() {
        size = 0;
        heap.get()->clear();
    }

    template<class valtype, class comparator>
    inline std::vector<int>::iterator BinarySearchTree<valtype, comparator>::begin() {
        return heap.get()->begin();
    }

    template<class valtype, class comparator>
    inline std::vector<int>::iterator BinarySearchTree<valtype, comparator>::end() {
        return heap.get()->end();
    }

    template<class valtype, class comparator>
    inline void BinarySearchTree<valtype, comparator>::removeroot() {
        remove(0);
    }

    template<class valtype, class comparator>
    inline bool BinarySearchTree<valtype, comparator>::remove(int index) {
        if (size < 0) throw std::out_of_range("The attempt to get element from empty heap");
        if (index >= size) return false;
        if (size > 1) {
            std::swap(heap.get()->operator[](index), heap.get()->operator[](size - 1));
            heap.get()->pop_back();
            heapify(index, --size);
        } else {
            size = 0;
            heap.get()->clear();
        }
        return true;
    }

    template<class valtype, class comparator>
    inline valtype BinarySearchTree<valtype, comparator>::max() {
        if (size < 0) throw std::out_of_range("The attempt to get element from empty heap");
        return heap.get()->front();
    }

    template<class valtype, class comparator>
    inline void BinarySearchTree<valtype, comparator>::heapifybyparent(int index, int size) {
        int parent = (index - 1) >> 1;
        if (parent > -1) {
            if (comp(heap.get()->operator[](index), heap.get()->operator[](parent))) {
                std::swap(heap.get()->operator[](index), heap.get()->operator[](parent));
                heapifybyparent(parent, size);
            }
        }
    }

    template<class valtype, class comparator>
    inline void BinarySearchTree<valtype, comparator>::insert(valtype value) {
        ++size;
        heap.get()->push_back(value);
        heapifybyparent(size - 1, size);
    }

    template<class valtype, class comparator>
    inline valtype BinarySearchTree<valtype, comparator>::at(int index) {
        if (index >= size) throw std::out_of_range("the index is out of size");
        return heap.get()->operator[](index);
    }

    template<class valtype, class comparator>
    inline void BinarySearchTree<valtype, comparator>::heapify(int index, int size) {
        int LeftNodeIndex = (index << 1) + 1;
        int RightNodeIndex = (index << 1) + 2;
        int MaxNodeIndex = index;
        if (LeftNodeIndex < size && comp(heap.get()->operator[](LeftNodeIndex), heap.get()->operator[](MaxNodeIndex))) {
            MaxNodeIndex = LeftNodeIndex;
        }
        if (RightNodeIndex < size &&
            comp(heap.get()->operator[](RightNodeIndex), heap.get()->operator[](MaxNodeIndex))) {
            MaxNodeIndex = RightNodeIndex;
        }
        if (MaxNodeIndex != index) {
            std::swap(heap.get()->operator[](index), heap.get()->operator[](MaxNodeIndex));
            heapify(MaxNodeIndex, size);
        }
    }

    template<class valtype, class comparator>
    inline void BinarySearchTree<valtype, comparator>::sort() {
        for (int i = this->size; i > 0;) {
            std::swap(heap.get()->operator[](0), heap.get()->operator[](i - 1));
            heapify(0, i);// i is size here
            --i;
        }
    }

    int *Heapify(int *array, int i, int size) {
        int left = (i << 1) + 1;
        int right = (i << 1) + 2;
        int max = i;
        if (left <= size && array[left] > array[max]) max = left;
        if (right <= size && array[right] > array[max]) max = right;
        if (max != i) {
            auto temp = array[max];
            array[max] = array[i];
            array[i] = temp;
            Heapify(array, max, size);
        }
        return array;
    }

    int *BuildBinaryHeap(int *array, size_t size) {
        int AmountParentNodes = (size >> 1) - 1;
        for (int i = AmountParentNodes; i >= 0; i--) {
            Heapify(array, i, size);
        }
        return array;
    }
}