#include <bits/stdc++.h>
using namespace std;

template<class T>
class MaxHeap {
public:
  // Constructor: constructing an empty heap.
  MaxHeap() = default;

  // Add an element to the heap.
  void insert(T elem) {
    heap.push_back(elem);
    swim(heap.size() - 1);
  }

  // Remove and return the root element in the heap.
  T extract() {
    if (heap.empty()) throw runtime_error("Heap is empty");
    T max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) sink(0);
    return max;
  }

  // Return the number of elements in the heap.
  int count() const {
    return heap.size();
  }

private:
  vector<T> heap;

  void swim(int k) {
    while (k > 0 && heap[(k - 1) / 2] < heap[k]) {
      swap(heap[(k - 1) / 2], heap[k]);
      k = (k - 1) / 2;
    }
  }

  void sink(int k) {
    int size = heap.size();
    while (2 * k + 1 < size) {
      int j = 2 * k + 1;
      if (j + 1 < size && heap[j] < heap[j + 1]) j = 2 * k + 2;
      if (heap[k] >= heap[j]) break;
      swap(heap[k], heap[j]);
      k = j;
    }
  }
};
