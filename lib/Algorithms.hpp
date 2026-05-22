#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <vector>
using namespace std;
template<typename T>
void Swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
int Max(int a, int b) {
    if(a > b) return a;
    return b;
}
template<typename T>
void bubbleSort(vector<T> &a, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(a[j] > a[j + 1]){
                Swap(a[j], a[j + 1]);
            }
        }
    }
}
template<typename T>
void selectionSort(vector<T> &a, int n){
    for(int i = 0; i < n; i++){
        int min_index = i;
        for(int j = i + 1; j < n; j++){
            if(a[j] < a[min_index]) min_index = j;
        }
        Swap(a[i], a[min_index]);
    }
}
template<typename T>
void insertionSort (vector<T> &a, int n) {
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j > 0 && a[j] < a[j - 1]) {
            Swap(a[j], a[j - 1]);
            j--;
        }
    }
}
template<typename T>
void heapify (vector<T> &a, int n, int i){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if(l < n && a[largest] < a[l]) largest = l;
    if(r < n && a[largest] < a[r]) largest = r;
    
    if(largest != i){
        Swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}
template<typename T>
void heapSort(vector<T> &a, int n){
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i);
    }
    for(int i = n - 1; i >= 0; i--){
        Swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

template<typename T>
int partition(vector<T> &a, int l, int r) {
    T pivot = a[l];
    int i = l - 1;
    int j = r + 1;
    while(true) {
        do {
            i++;
        } while(a[i] < pivot);
        do {
            j--;
        } while (a[j] > pivot);
        if(i < j) {
            Swap(a[i], a[j]);
        } else return j;
    }
}
template<typename T>
void quickSort(vector<T> &a, int l, int r) {
    if(l >= r) return;
    int p = partition(a, l, r);
    quickSort(a, l, p);
    quickSort(a, p + 1, r);
}

template<typename T>
void merge(vector<T> &a, int l, int m, int r){
    vector<T> x(a.begin() + l, a.begin() + m + 1);
    vector<T> y(a.begin() + m + 1, a.begin() + r + 1);
    int i = 0, j = 0;
    while (i < x.size() && j < y.size()){
        if(x[i] <= y[j]){
            a[l] = x[i];
            i++,l++;
        } else {
            a[l] = y[j];
            j++,l++;
        }
    }
    while (i < x.size()){
        a[l] = x[i], l++,i++;
    }
    while (j < y.size()){
        a[l] = y[j], j++,l++;
    }
}
template<typename T>
void mergeSort(vector<T> &a,int l, int r){
    if(l < r){
        int m = (l + r)/2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    } 
}
template<typename T>
T* binarySearch(vector<T> &a, T val) {
    int l = 0; 
    int r = a.size() - 1;
    while(l <= r) {
        int m = (l + r)/2;
        if(a[m] == val) return &a[m];
        else if(a[m] > val) r = m - 1;
        else l = m + 1;
    }
    return nullptr;
}
#endif