#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
template <class T>
struct ListNode {
    ListNode* next;
    T val;
};
template <class T>
class queue {
public:
    ListNode<T>* head;
    ListNode<T>* tail;
    unsigned current_size;
    queue() {
        head = nullptr;
        tail = nullptr;
        current_size = 0;
    }
    void push(T input) {
        if (current_size == 0) {
            ListNode<T>* ptr = new ListNode<T>();
            ptr -> val = input;
            head = ptr;
            tail = ptr;
        }
        else {
            ListNode<T>* ptr = new ListNode<T>();
            ptr -> val = input;
            ptr -> next = nullptr;
            tail -> next = ptr;
            tail = tail -> next;
        }
        current_size++;
    }
    void pop() {
        if (current_size == 0) {
            cout << "Error, Pop from a empty queue is illegal" << endl;
            return;
        }
        ListNode<T>* tmp = head;
        head = head -> next;
        delete tmp;
        current_size--;
    }
    T front() {
        return head -> val;
    }
    unsigned size() {
        return current_size;
    }
    bool empty() {
        return current_size == 0;
    }
};
class coordinate {
public:
    int x;
    int y;
    coordinate() {}
    coordinate(unsigned a, unsigned b) : x(a), y(b) {}
    bool operator == (const coordinate& input) const {
        return (this -> x == input.x && this -> y == input.y);
    }
};
void print_result(const coordinate& input,const vector<vector<coordinate>>& previous, const coordinate& start, vector<vector<char>>& maze) {
    if (input == start) {
        cout << "(" << start.x + 1 << ", " << start.y + 1<< ")"<< endl;
        return;
    }
    print_result(previous[input.x][input.y], previous, start, maze);
    cout << "(" << input.x + 1 << ", " << input.y + 1 << ")" << endl;
    maze[input.x][input.y] = 'P';
}
int main() {
    int row, col;
    while (cin >> row >> col) {
        vector<vector<char>> maze(row, vector<char>(col, '0'));
        vector<vector<int>> distance(row, vector<int>(col, INT_MAX));
        vector<vector<coordinate>> previous(row, vector<coordinate>(col));
        coordinate start, end;
        for (int i = 0; i < row; i++) {
            int pos;
            cin >> pos;
            while (pos != 0) {
                char operation;
                cin >> operation;
                maze[i][pos - 1] = operation;
                if (operation == 's') {
                    start.x = i;
                    start.y = pos - 1;
                    distance[start.x][start.y] = 0;
                }
                if (operation == 't') {
                    end.x = i;
                    end.y = pos - 1;
                }
                cin >> pos;
            }
        }
        queue<coordinate> queue;
        queue.push(start);
        while (!queue.empty()) {
            coordinate tmp = queue.front();
            queue.pop();
            if (tmp.x >= 1 && distance[tmp.x - 1][tmp.y] == INT_MAX && maze[tmp.x - 1][tmp.y] != 'x') {
                queue.push(coordinate(tmp.x - 1, tmp.y));
                distance[tmp.x - 1][tmp.y] = distance[tmp.x][tmp.y] + 1;
                previous[tmp.x - 1][tmp.y] = tmp;
            }
            if (tmp.x < row - 1 && distance[tmp.x + 1][tmp.y] == INT_MAX && maze[tmp.x + 1][tmp.y] != 'x') {
                queue.push(coordinate(tmp.x + 1, tmp.y));
                distance[tmp.x + 1][tmp.y] = distance[tmp.x][tmp.y] + 1;
                previous[tmp.x + 1][tmp.y] = tmp;
            }
            if (tmp.y >= 1 && distance[tmp.x][tmp.y - 1] == INT_MAX && maze[tmp.x][tmp.y - 1] != 'x') {
                queue.push(coordinate(tmp.x, tmp.y - 1));
                distance[tmp.x][tmp.y - 1] = distance[tmp.x][tmp.y] + 1;
                previous[tmp.x][tmp.y - 1] = tmp;
            }
            if (tmp.y < col - 1 && distance[tmp.x][tmp.y + 1] == INT_MAX && maze[tmp.x][tmp.y + 1] != 'x') {
                queue.push(coordinate(tmp.x, tmp.y + 1));
                distance[tmp.x][tmp.y + 1] = distance[tmp.x][tmp.y] + 1;
                previous[tmp.x][tmp.y + 1] = tmp;
            }
        }
        if (distance[end.x][end.y] == INT_MAX) 
            cout << "There is no path from start to end" << endl;
        else 
            print_result(end, previous, start, maze);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) 
                cout << maze[i][j] << "\t";
            cout << endl;
        }
    }
    return 0;
}