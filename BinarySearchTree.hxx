/*
	Copyright (C) 2023 Marzan Ivan
 	Binary Search Tree program header
	GNU GENERAL PUBLIC LICENSE v3.0
*/

#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

template<class valtype, class comparator>
class BinarySearchTree {
private:
    std::unique_ptr<std::vector<valtype>> heap;
    const comparator comp; //custom comparator
    size_t size;

public:
    BinarySearchTree() {
        heap.reset(nullptr);
        size = 0;
    }

    explicit BinarySearchTree(valtype *array, size_t size, size_t freesize = 0) {
        this->size = size;
        std::vector<valtype>* newheap = new std::vector<valtype>();
        newheap->reserve(size + freesize);

        newheap->assign(array, array + size);
        this->heap.reset(newheap);
        for (int i = (size >> 1) - 1; i >= 0; i--) {
            heapify(i, this->size - 1);
        }
    }

    ~BinarySearchTree() {
        heap.reset();
    }

    BinarySearchTree(const BinarySearchTree& copy) = delete;
    BinarySearchTree& operator=(BinarySearchTree& arg) = delete;

    valtype at(int index);

    void heapify(int index, int size);

    void sort();
};
template<class valtype, class comparator>
inline valtype BinarySearchTree<valtype,comparator>::at(int index) {
    if (index > size) throw std::out_of_range("the index is out of size");
    return heap.get()->operator[](index);
}

template<class valtype, class comparator>
inline void BinarySearchTree<valtype,comparator>::heapify(int index, int size) {
    int LeftNodeIndex = (index << 1) + 1;
    int RightNodeIndex = (index << 1) + 2;
    int MaxNodeIndex = index;
    if (LeftNodeIndex <= size && comp(heap.get()->operator[](LeftNodeIndex), heap.get()->operator[](MaxNodeIndex))) {
        MaxNodeIndex = LeftNodeIndex;
    }
    if (RightNodeIndex <= size && comp(heap.get()->operator[](RightNodeIndex), heap.get()->operator[](MaxNodeIndex))) {
        MaxNodeIndex = RightNodeIndex;
    }
    if (MaxNodeIndex != index) {
        std::swap(heap.get()->operator[](index),heap.get()->operator[](MaxNodeIndex));
        heapify(MaxNodeIndex, size);
    }
}

template<class valtype, class comparator>
inline void BinarySearchTree<valtype ,comparator>::sort() {
    for (int i = this->size - 1; i > 0;) {
        std::swap(heap.get()->operator[](0), heap.get()->operator[](i));
        heapify(0, --i);
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
