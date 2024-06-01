/*
	Copyright (C) 2023 Marzan Ivan
 	Binary Search Tree program header
	GNU GENERAL PUBLIC LICENSE v3.0
*/

#pragma once
#define size_t unsigned int

template <class Ttype>
struct BinarySearchTree {
	Ttype* array;
	size_t size;

	BinarySearchTree() {
		array = nullptr;
		size = 0;
	}
	
	BinarySearchTree(int* array, size_t size) {
		this->size = size;
		this->array = array;
		for (int i = (size >> 1) - 1; i >= 0; i--) {
			heapify(i, this->size - 1);
		}
	}

	~BinarySearchTree() {
		
	}

	void heapify(int index, size_t size);
	
	int* sort();
};

template <class Ttype>
inline void BinarySearchTree<Ttype>::heapify(int index, size_t size) {
	int LeftNodeIndex = (index << 1) + 1;
	int RightNodeIndex = (index << 1) + 2;
	int MaxNodeIndex = index;
	if (LeftNodeIndex <= size && array[LeftNodeIndex] > array[MaxNodeIndex]) {
		MaxNodeIndex = LeftNodeIndex;
	}
	if (RightNodeIndex <= size && array[RightNodeIndex] > array[MaxNodeIndex]) {
		MaxNodeIndex = RightNodeIndex;
	}
	if (MaxNodeIndex != index) {
		auto temp = array[MaxNodeIndex];
		array[MaxNodeIndex] = array[index];
		array[index] = temp;
		heapify(MaxNodeIndex, size);
	}
}

template<class Ttype>
inline int* BinarySearchTree<Ttype>::sort() {
	for (int i = this->size - 1; i > 0;) {
		auto max = array[0];
		array[0] = array[i];
		array[i] = max;
		heapify(0, --i);
	}
	return this->array;
}

int* Heapify(int* array, int i, int size) {
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

int* BuildBinaryHeap(int* array, size_t size) {
    int AmountParentNodes = (size >> 1) - 1;
    for (int i = AmountParentNodes; i >= 0; i--) {
        Heapify(array, i, size);
    }
    return array;
}
