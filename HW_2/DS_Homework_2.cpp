#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <limits.h>
using namespace std;
class solution {
private:
    template <class T>
    static void Merge_help(vector<T>& arr, unsigned left, unsigned right) {
        if (left == right) 
            return;
        unsigned mid = left + (right - left) / 2;
        Merge_help(arr, left, mid);
        Merge_help(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
    template <class T>
    static void Merge(vector<T>& arr, unsigned left, unsigned mid, unsigned right) {
        vector<T> left_arr(arr.begin() + left, arr.begin() + mid + 1);
        vector<T> right_arr(arr.begin() + mid + 1, arr.begin() + right + 1);
        unsigned l = 0, r = 0, index = left;
        while (l < left_arr.size() && r < right_arr.size()) 
            arr[index++] = left_arr[l] < right_arr[r] ? left_arr[l++] : right_arr[r++];
        while (l < left_arr.size())
            arr[index++] = left_arr[l++];
        while (r < right_arr.size())
            arr[index++] = right_arr[r++];
    }
    template <class T>
    static int partition(vector<T>& arr, int low, int high)
    {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
    template <class T> 
    static void Quick_help(vector<T>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            Quick_help(arr, low, pi - 1);
            Quick_help(arr, pi + 1, high);
        }
    }
    template <class T>
    static void max_heapify(vector<T>& arr, int start, int end) {
        int dad = start;
        int son = dad * 2 + 1;
        while (son <= end) {
            if (son + 1 <= end && arr[son] < arr[son + 1]) 
                son++;
            if (arr[dad] > arr[son])
                return;
            else {
                swap(arr[dad], arr[son]);
                dad = son;
                son = son * 2 + 1;
            }
        }
    }
    template <class T>
    static void heap_help(vector<T>& arr, int length) {
        for (int i = (length / 2) - 1; i >= 0; i--) 
            max_heapify(arr, i, length - 1);
        for (int i = length - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            max_heapify(arr, 0, i - 1);
        }
    }
public:
    template <class T> 
    static void Insertion_sort(vector<T>& arr) {
        for (int i = 1; i < arr.size(); i++) { 
            T tmp = arr[i];
            T j = i - 1;
            while (j >= 0 && tmp < arr[j]) 
                arr[j + 1] = arr[j--];
            arr[j + 1] = tmp;
        }
    } 
    template <class T> 
    static void Selection_sort(vector<T>& arr) {
        for (int i = 0; i < arr.size() - 1; i++) {
            int index = i;
            T tmp_min = arr[i];
            for (int j = i; j < arr.size(); j++) {
                if (arr[j] < tmp_min) {
                    index = j;
                    tmp_min = arr[j];
                }
            }
            swap(arr[i], arr[index]);
        }
    }
    template <class T>
    static void Merge_sort(vector<T>& arr) {
        Merge_help(arr, 0, arr.size() - 1);
    }
    template <class T>
    static void Quick_sort (vector<T>& arr) {
        Quick_help(arr, 0, arr.size() - 1);
    }
    template <class T>
    static void Heap_sort(vector<T>& arr){
        heap_help(arr, arr.size());
    }
    template <class T>
    static bool Sorted(const vector<T>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1])
                return false;
        }
        return true;
    } 
    static vector<int> random_vec(unsigned size) {
        vector<int> arr(size);
        srand(static_cast<unsigned>(time(NULL)));
        for (int i = 0; i < size; i++)
            arr[i] = rand();
        return arr;
    }
};
int main() {
    ofstream output;
    output.open("data.txt");
    for (long i = 10000; i <= 100000; i += 1000) {
        int sum = 0;
        cout << i << endl;
        output << i << "\t";
        vector<int> arr;
        for (int j = 0; j < 3; j++) {
            arr = solution::random_vec(i);
            clock_t start = clock();
            solution::Insertion_sort(arr);
            clock_t end = clock();
            sum += (solution::Sorted(arr) ? end - start : INT_MIN);
        }
        output << (sum / 3) << "\t";
        sum = 0;
        for (int j = 0; j < 3; j++) {
            arr = solution::random_vec(i);
            clock_t start = clock();
            solution::Selection_sort(arr);
            clock_t end = clock();
            sum += (solution::Sorted(arr) ? end - start : INT_MIN);
        }
        output << (sum / 3) << "\t";
        sum = 0;
        for (int j = 0; j < 3; j++) {
            arr = solution::random_vec(i);
            clock_t start = clock();
            solution::Quick_sort(arr);
            clock_t end = clock();
            sum += (solution::Sorted(arr) ? end - start : INT_MIN);
        }
        output << (sum / 3) << "\t";
        sum = 0;
        for (int j = 0; j < 3; j++) {
            arr = solution::random_vec(i);
            clock_t start = clock();
            solution::Merge_sort(arr);
            clock_t end = clock();
            sum += (solution::Sorted(arr) ? end - start : INT_MIN);
        }
        output << (sum / 3) << "\t";
        sum = 0;
        for (int j = 0; j < 3; j++) {
            arr = solution::random_vec(i);
            clock_t start = clock();
            solution::Heap_sort(arr);
            clock_t end = clock();
            sum += (solution::Sorted(arr) ? end - start : INT_MIN);
        }
        output << (sum / 3) << "\t";
        output << endl;
    }
    output.close();
    return 0;
}