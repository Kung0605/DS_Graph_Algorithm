#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;
template <class T>
class stack;
template <class T> 
class ListNode {
private:
    ListNode<T>* next;
    ListNode<T>* previous;
    T data;
public:
    ListNode() {}
    ListNode(T data) : data(data), next(nullptr), previous(nullptr) {}
    friend class stack<T>;
};
template <class T> 
class stack {
private:
    unsigned current_size;
    ListNode<T>* tail;
public:
    stack() {
        tail = nullptr;
        current_size = 0;
    }
    unsigned size() {
        return current_size;
    }
    bool empty() {
        return current_size == 0;
    }
    void push(T data) {
        if (current_size == 0) { 
            tail = new ListNode<T>(data);
        }
        else {
            tail -> next = new ListNode<T>(data);
            tail -> next -> previous = tail;
            tail = tail -> next;
        }
        current_size++;
    }
    T top() {
        return tail -> data;
    }
    void pop() {
        if (current_size == 0)
            return;
        if (current_size == 1) 
            tail = nullptr;
        else {
            tail = tail -> previous;
            tail -> next = nullptr;
        }
        current_size--;
    }
};
double pow(double x, int n) {
    if (n == 0)
        return 1;
    double tmp = pow(x, n / 2);
    if (n % 2 == 0) 
        return tmp * tmp;
    else {
        if (n > 0)
            return x * tmp * tmp;
        return tmp * tmp / x;
    }
}
double calculate(double left, char tmp_operator, double right) {
    switch(tmp_operator) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        case '^':
            return pow(left, right);
        default:
            return 0;
    } 
}
int main() {
    stack<char> operators;
    stack<double> operands;
    unordered_map<char, unsigned> precedence = {{'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};
    unordered_map<char, double> variables;
    string input, line;
    char var;
    while (getline(cin, line)) {
        stringstream ss;
        ss << line;
        while (ss >> input) {
            if (((input[0] >= 'a' && input[0] <= 'z') || (input[0] >= 'A' && input[0] <= 'Z'))) {
                if (variables.count(input[0])) 
                    operands.push(variables[input[0]]);
                else 
                    var = input[0];            
            }
            else if (input == "=") {
                operators.push('=');
            }
            else if (input == "+" || input == "-" || input == "*" || input == "/" || input == "(" || input == ")" || input == "^") {
                if (input == "(") 
                    operators.push('(');
                else if (input == ")") {
                    while (operators.top() != '(') {
                        char tmp_operator = operators.top();
                        operators.pop();
                        if (tmp_operator == '=') {
                            variables[var] = operands.top();
                            operands.pop();
                            continue;
                        }
                        double right = operands.top();
                        operands.pop();
                        double left = operands.top();
                        operands.pop();
                        operands.push(calculate(left, tmp_operator, right));
                    }
                    operators.pop();
                }
                else {
                    while ((!operators.empty()) && precedence[operators.top()] >= precedence[input[0]]) {
                        char tmp_operator = operators.top();
                        operators.pop();
                        if (tmp_operator == '=') {
                            variables[var] = operands.top();
                            operands.pop();
                            continue;
                        }
                        double right = operands.top();
                        operands.pop();
                        double left = operands.top();
                        operands.pop();
                        operands.push(calculate(left, tmp_operator, right));
                    }
                    operators.push(input[0]);
                }
            }
            else
                operands.push(stod(input));
        }
        while (!operators.empty()) {
            char tmp_operator = operators.top();
            operators.pop();
            if (tmp_operator == '=') {
                variables[var] = operands.top();
                operands.pop();
                continue;
            }
            double right = operands.top();
            operands.pop();
            double left = operands.top();
            operands.pop();
            operands.push(calculate(left, tmp_operator, right));
        }
        if (operators.empty() && !operands.empty()) {
            cout << operands.top() << endl;
            operands.pop();
        }
    }
    for (unordered_map<char, double>::iterator it = variables.begin(); it != variables.end(); it++) 
        cout << it -> first << " = " << it -> second << endl;
    return 0;
}