#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
class segment_tree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;
public:
    /*void print() {
        for (int i = 0; i < tree.size(); i++)
            cout << tree[i] << " ";
        cout << endl;
    }*/
    segment_tree(vector<int> input) {  
        arr = input;
        n = input.size();
        int height = static_cast<int>(ceil(log2(n)));
        int size = 2 * static_cast<int>(pow(2, height)) - 1;
        tree = vector<int>(size);
        initialize(input, 0, n - 1, 0);
    }
    int initialize(vector<int> input, int start, int end, int index) {
        if (start == end) {
            tree[index] = input[start];
            return tree[index];
        }
        int mid = start + (end - start) / 2;
        tree[index] = initialize(input, start, mid, index * 2 + 1) + 
                   initialize(input, mid + 1, end, index * 2 + 2);
        return tree[index];
    }
    int getsum(int tmp_left, int tmp_right, int left, int right, int index) {
        if (tmp_right <= right && tmp_left >= left) 
            return tree[index];
        if (tmp_right < left || tmp_left > right) 
            return 0;
        int mid = tmp_left + (tmp_right - tmp_left) / 2;
        return getsum(tmp_left, mid, left, right, 2 * index + 1) +
               getsum(mid + 1, tmp_right, left, right, 2 * index + 2);
    }
    string getsum(int left, int right) {
        return (left < 0 || right >= n) ? "Invalid interval" : to_string(getsum(0, n - 1, left, right, 0));
    }
    void setval(int left, int right, int target, int diff, int index) {
        if (target < left || target > right)
            return;
        tree[index] += diff;
        if (left != right) {
            int mid = left + (right - left) / 2;
            setval(left, mid, target, diff, 2 * index + 1);
            setval(mid + 1, right, target, diff, 2 * index + 2);
        }
    }
    void setval(int target, int val) {
        if (target < 0 || target >= n) {
            cout << "Invalid index" << endl;
            return ;
        }
        int diff = val - arr[target];
        arr[target] = val;
        setval(0, n - 1, target, diff, 0);
    }
};
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    segment_tree tmp(arr);
    char command;
    while (cin >> command) {
        if (command == 's') {
            int target, val;
            cin >> target >> val;
            tmp.setval(target, val);
        }
        else if (command == 'g') {
            int left, right;
            cin >> left >> right;
            cout << tmp.getsum(left, right) << endl;
        }
        else 
            cout << "invalid command" << endl;
    }
    return 0;
}