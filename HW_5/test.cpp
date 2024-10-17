#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
    unordered_map<char, int> map;
    char c;
    for (int i = 0; i < 5; i++) {
        cin >> c;
        map[c] = 5;
    }
    for (auto it = map.begin(); it != map.end(); it++) {
        cout << it -> first << " " << it -> second << endl;
    }
    return 0;
}