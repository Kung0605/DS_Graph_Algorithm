#include <iostream>
#include <vector>
using namespace std;
struct ListNode {
    ListNode* next;
    unsigned index;
    int val;
};
class matrix {
private:
    vector<ListNode*> arr;
    unsigned row;
    unsigned col;
public:
    matrix() : row(0), col(0) {}
    matrix (unsigned row, unsigned col) : row(row), col(col) {
        vector<ListNode*> result(row);
        for (int i = 0; i < row; i++) {
            int index;            
            result[i] = new ListNode();
            result[i] -> next = nullptr;
            ListNode* ptr = result[i];
            while (cin >> index && index != 0) {
                ptr -> next = new ListNode();
                ptr = ptr -> next;
                ptr -> index = index;
                cin >> ptr -> val;
            }
            result[i] = result[i] -> next; 
        }
        arr = result;
    }
    friend ostream& operator << (ostream& out, const matrix& mat) {
        if (mat.row == 0 && mat.col == 0) {
            out << "Error" << endl;
            return out;
        }
        for (int i = 0; i < mat.row; i++) {
            ListNode* ptr = mat.arr[i];
            unsigned index = 1;
            while (index <= mat.col) {
                if (ptr != nullptr && ptr -> index == index) {
                    out << ptr -> val << " ";
                    ptr = ptr -> next;
                }   
                else {
                    out << 0 << " ";
                }
                index++;
            }
            out << endl;
        }
        return out;
    }
    bool equal_size(const matrix& input) {
        return (row == input.row && col == input.col);
    }
    bool can_multiply(const matrix& input) {
        return (col == input.row);
    }
    ListNode* find_node(unsigned row, unsigned index) {
        ListNode* ptr = arr[row];
        while (ptr != nullptr && ptr -> index != index) 
            ptr = ptr -> next;
        return (ptr == nullptr) ? nullptr : ptr;
    }
    matrix operator + (matrix& input) {
        if (!equal_size(input))
            return matrix();
        matrix result;
        result.row = row;
        result.col = col;
        vector<ListNode*> tmp(row);
        for (int i = 0; i < row; i++) {
            ListNode* root = new ListNode();
            ListNode* ptr = root;
            for (int j = 0; j < col; j++) {
                int value = ((find_node(i, j + 1) == nullptr) ? 0 : find_node(i, j + 1) -> val)
                + ((input.find_node(i, j + 1) == nullptr) ? 0 : input.find_node(i, j + 1) -> val);
                if (value == 0)
                    continue;
                ptr -> next = new ListNode();
                ptr = ptr -> next;
                ptr -> index = j + 1;
                ptr -> val = value;
            }
            tmp[i] = root -> next;
        }
        result.arr = tmp;
        return result;
    }
    matrix operator * (matrix& input) {
        if (!can_multiply(input))
            return matrix();
        matrix result;
        result.row = row;
        result.col = input.col;
        vector<ListNode*> tmp(row);
        for (int i = 0; i < row; i++) {
            ListNode* root = new ListNode();
            ListNode* ptr = root;
            for (int j = 0; j < col; j++) {
                int value = 0;
                for (int k = 0; k < col; k++) {
                    if (find_node(i, k + 1) == nullptr || input.find_node(k, j + 1) == nullptr) 
                        continue;
                    value += (find_node(i, k + 1) -> val * input.find_node(k, j + 1) -> val);
                }
                if (value == 0)
                    continue;
                ptr -> next = new ListNode();
                ptr = ptr -> next;
                ptr -> index = j + 1;
                ptr -> val = value;
            }
            tmp[i] = root -> next;
        }
        result.arr = tmp;
        return result;
    }
    matrix tranpose() {
        matrix result;
        result.row = col;
        result.col = row;
        vector<ListNode*> tmp(result.row);
        for (int i = 0; i < result.row; i++) {
            ListNode* root = new ListNode();
            ListNode* ptr = root;
            for (int j = 0; j < result.col; j++) {
                if (find_node(j, i + 1) == nullptr)
                    continue;
                ptr -> next = new ListNode();
                ptr = ptr -> next;
                ptr -> index = j + 1;
                ptr -> val = find_node(j, i + 1) -> val;
            }
            tmp[i] = root -> next;
        }
        result.arr = tmp;
        return result;
    }
};
int main() {
    unsigned row, col;
    while (cin >> row >> col) {
        matrix A(row, col);
        cin >> row >> col;
        matrix B(row, col);
        cout << "A:\n" << A << "B:\n" << B 
            << "A tranpose:\n" << A.tranpose() << "B tranpose:\n" << B.tranpose()
            << "A + B:\n" << A + B << "AB:\n" << A * B 
            << "(A + B) tranpose:\n" << ((A + B).tranpose()) << "(A * B) tranpose:\n" << ((A * B).tranpose()) << endl;
    }
    return 0;
}