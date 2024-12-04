#include <bits/stdc++.h>
using namespace std;

template<class T>
class MinMaxHeap {
public:
    MinMaxHeap(){}

    // Insert a new element into the Min-Max Heap
    void insert(T value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    // Retrieve the minimum element
    T getMin() const {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }

    // Retrieve the maximum element
    T getMax() const {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[getMaxIndex()];
    }

    // Delete the minimum element
    void deleteMin() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) trickleDownMin(0);
    }

    // Delete the maximum element
    void deleteMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        heap[getMaxIndex()] = heap.back();
        heap.pop_back();
        if (getMaxIndex() < heap.size()) trickleDownMax(getMaxIndex());
    }

private:
    vector<T> heap;

    // Helper function to get the index of the maximum element (either child of root)
    int getMaxIndex() const {
        if (heap.size() == 1) return 0;
        if (heap.size() == 2) return 1;
        return (heap[1] > heap[2]) ? 1 : 2;
    }

    // Helper function to bubble up element at index `i`
    void bubbleUp(int i) {
        if (isMinLevel(i)) {
            if (i > 0 && heap[i] > heap[parent(i)]) {
                swap(heap[i], heap[parent(i)]);
                bubbleUpMax(parent(i));
            } else {
                bubbleUpMin(i);
            }
        } else {
            if (i > 0 && heap[i] < heap[parent(i)]) {
                swap(heap[i], heap[parent(i)]);
                bubbleUpMin(parent(i));
            } else {
                bubbleUpMax(i);
            }
        }
    }

    // Helper functions to bubble up on Min and Max levels
    void bubbleUpMin(int i) {
        while (grandparent(i) >= 0 && heap[i] < heap[grandparent(i)]) {
            swap(heap[i], heap[grandparent(i)]);
            i = grandparent(i);
        }
    }

    void bubbleUpMax(int i) {
        while (grandparent(i) > 0 && heap[i] > heap[grandparent(i)]) {
            swap(heap[i], heap[grandparent(i)]);
            i = grandparent(i);
        }
    }

    // Helper functions to trickle down on Min and Max levels
    void trickleDownMin(int i) {
         while (2 * i + 1 < heap.size()) {
            int m = minIndexDescendants(i);
            if (m == -1 || heap[i] <= heap[m]) break;
            swap(heap[i], heap[m]);
            i = m;
            // 檢查新的 i 是否大於其父節點，若是則交換
            if ((i - 1) / 2 >= 0 && heap[i] > heap[(i - 1) / 2]) {
                swap(heap[i], heap[(i - 1) / 2]);
            }
        }
    }

    void trickleDownMax(int i) {
        while (2 * i + 1 < heap.size()) {
            int m = maxIndexDescendants(i);
            if (m == -1 || heap[i] >= heap[m]) break;
            swap(heap[i], heap[m]);
            i = m;
            // 檢查新的 i 是否小於其父節點，若是則交換
            if ((i - 1) / 2 >= 0 && heap[i] < heap[(i - 1) / 2]) {
                swap(heap[i], heap[(i - 1) / 2]);
            }
        }
    }

     // 找出指定節點 i 的最小子孫索引
    int minIndexDescendants(int i) const {
        int firstChild = 2 * i + 1;
        int lastDescendant = min((int)heap.size() - 1, 2 * firstChild + 2);
        int minIdx = -1;
        for (int j = firstChild; j <= lastDescendant; ++j) {
            if (minIdx == -1 || heap[j] < heap[minIdx]) minIdx = j;
        }
        return minIdx;
    }

    // 找出指定節點 i 的最大子孫索引
    int maxIndexDescendants(int i) const {
        int firstChild = 2 * i + 1;
        int lastDescendant = min((int)heap.size() - 1, 2 * firstChild + 2);
        int maxIdx = -1;
        for (int j = firstChild; j <= lastDescendant; ++j) {
            if (maxIdx == -1 || heap[j] > heap[maxIdx]) maxIdx = j;
        }
        return maxIdx;
    }

    // Utility functions to get parent and grandparent
    int parent(int i) const { return (i - 1) / 2; }
    int grandparent(int i) const { return (i - 3) / 4; }
    bool isMinLevel(int i) const { return ((int)log2(i + 1)) % 2 == 0; }
};

int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        std::cout << mmHeap.getMin() << " ";
        mmHeap.deleteMin();
      }
      catch(std::exception) {
        break;
      }
    }
    std::cout << std::endl;
    
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        std::cout << mmHeap.getMax() << " ";
        mmHeap.deleteMax();
      }
      catch(std::exception) {
        break;
      }
    }

    return 0;
}
