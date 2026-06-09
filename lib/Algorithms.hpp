#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <vector>
#include <functional>
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
template<typename T , typename comp = less<T>>
void bubbleSort(vector<T> &a, int n, comp cmp = comp{}) {
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(cmp(a[j + 1], a[j])) {
                Swap(a[j], a[j + 1]);
            }
        }
    }
}
template<typename T, typename comp = less<T>>
void selectionSort(vector<T> &a, int n, comp cmp = comp{}) {
    for(int i = 0; i < n; i++){
        int min_index = i;
        for(int j = i + 1; j < n; j++){
            if(cmp(a[j], a[min_index])) min_index = j;
        }
        Swap(a[i], a[min_index]);
    }
}
template<typename T, typename comp = less<T>>
void insertionSort (vector<T> &a, int n, comp cmp = comp{}) {
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j > 0 && cmp(a[j], a[j - 1])) {
            Swap(a[j], a[j - 1]);
            j--;
        }
    }
}
template<typename T, typename comp = less<T>>
void heapify (vector<T> &a, int n, int i, comp cmp = comp{}){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    if(l < n && cmp(a[largest], a[l])) largest = l;
    if(r < n && cmp(a[largest], a[r])) largest = r;
    
    if(largest != i){
        Swap(a[i], a[largest]);
        heapify(a, n, largest, cmp);
    }
}
template<typename T, typename comp = less<T>>
void heapSort(vector<T> &a, int n, comp cmp = comp{}){
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i, cmp);
    }
    for(int i = n - 1; i >= 0; i--){
        Swap(a[0], a[i]);
        heapify(a, i, 0, cmp);
    }
}

template<typename T, typename comp = less<T>>
int partition(vector<T> &a, int l, int r, comp cmp = comp{}) {
    T pivot = a[l];
    int i = l - 1;
    int j = r + 1;
    while(true) {
        do {
            i++;
        } while(cmp(a[i], pivot));
        do {
            j--;
        } while (cmp(pivot, a[j]));
        if(i < j) {
            Swap(a[i], a[j]);
        } else return j;
    }
}
template<typename T, typename comp = less<T>>
void quickSort(vector<T> &a, int l, int r, comp cmp = comp{}) {
    if(l >= r) return;
    int p = partition(a, l, r, cmp);
    quickSort(a, l, p, cmp);
    quickSort(a, p + 1, r, cmp);
}

template<typename T, typename comp = less<T>>
void merge(vector<T> &a, int l, int m, int r, comp cmp = comp{}){
    vector<T> x(a.begin() + l, a.begin() + m + 1);
    vector<T> y(a.begin() + m + 1, a.begin() + r + 1);
    int i = 0, j = 0;
    while (i < x.size() && j < y.size()){
        if(!cmp(y[j], x[i])){
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
template<typename T, typename comp = less<T>>
void mergeSort(vector<T> &a,int l, int r, comp cmp = comp{}) {
    if(l < r){
        int m = (l + r)/2;
        mergeSort(a, l, m, cmp);
        mergeSort(a, m + 1, r, cmp);
        merge(a, l, m, r, cmp);
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