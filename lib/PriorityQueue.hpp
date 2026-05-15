#include <vector>
using namespace std;
template<typename T>
void Swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
template<typename T>
void heapify(vector<T> &a, int n, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if(l < n && a[l] > a[largest]) largest = l;
    if(r < n && a[r] > a[largest]) largest = r;

    if(largest != i) {
        Swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}
template<typename T>
struct priorityQueue {
    vector<T> heap;
    void insert(T val) {
        heap.push_back(val);
        int i = heap.size() - 1;
        while(i > 0 && heap[(i - 1)/2] < heap[i]) {
            Swap(heap[i], heap[(i - 1)/2]);
            i = (i - 1)/2;
        }
    }
    void extract(){
        if(heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapify(heap, heap.size(), 0);
    }
    T peek() {
        return heap.empty() ? T{} : heap[0]; 
    }
    bool empty() {
        return heap.size() == 0;
    }
    int size() {
        return heap.size();
    }
};