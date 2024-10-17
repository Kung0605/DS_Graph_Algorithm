#include <iostream>
#include <stack>
using namespace std;
class MyQueue {
private:
    stack<int> s1;
    stack<int> s2;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        int result = s2.top();
        s2.pop();
        while(!s2.empty()) {
            s1.push(s2.top());
            s1.pop();
        }
        return result;
    }
    
    int peek() {
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        int result = s2.top();
        while(!s2.empty()) {
            s1.push(s2.top());
            s1.pop();
        }
        return result;
    }
    
    bool empty() {
        return s1.empty();
    }
};
int main() {
	MyQueue myQueue;
	myQueue.push(1); // queue is: [1]
	myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
	cout << myQueue.peek() << endl; // return 1
	cout << myQueue.pop() << endl; // return 1, queue is [2]
	cout <<myQueue.empty() << endl; // return false
	return 0;
}