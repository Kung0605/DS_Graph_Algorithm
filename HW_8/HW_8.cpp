#include <iostream>
#include <vector>
using namespace std;
class edge {
public:
    int s, t, w; //start point, terminal point and weight
    edge(int s, int t, int w) : s(s), t(t), w(w) {} // constructor
    edge() {} // default constructor
    bool operator < (const edge& other) { // overload operator < for sorting
        return w < other.w;
    }
    bool operator == (const edge& input) { // overload operator == for checking equality
        return (s == input.s && t == input.t && w == input.w) || (s == input.t && t == input.s && w == input.w);
    }
};
class set {
private:
    vector<int> data; // vector to store vertex in the set
public:
    set() { // default constructor
        data = vector<int>();
    }
    set(int size) { // constructor with given size
        data = vector<int>(size);
    }
    bool Count(const int& input) { // check whether a vertex is in the set
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == input)
                return true;
        }
        return false;
    }
    set Union(const set& input) { // return union of the set with input set
        for (int i = 0; i < input.data.size(); ++i) 
            this -> Insert(input.data[i]);
        return *this;
    }
    void Insert(const int& input) { // insert a element to the set
        if (this -> Count(input)) // if the element is already in the set then don't insert it again
            return;
        this -> data.push_back(input);
    }
};
template <class T> //
void Merge(vector<T>& arr, unsigned left, unsigned mid, unsigned right) {
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
void Merge_help(vector<T>& arr, unsigned left, unsigned right) {
    if (left == right) 
        return;
    unsigned mid = left + (right - left) / 2;
    Merge_help(arr, left, mid);
    Merge_help(arr, mid + 1, right);
    Merge(arr, left, mid, right);
}
template <class T>
void Merge_sort(vector<T>& arr) {
    Merge_help(arr, 0, arr.size() - 1);
}
int find(vector<set> sets, int n) { // find v ertex n is in which sets and return set's index
    for (int i = 0; i < sets.size(); ++i) {
        if (sets[i].Count(n))
            return i;
    }
    return -1; // if no sets contains n then return -1
}
void print_MST(const vector<edge>& MST) { // a function to print the edge in MST
    int weight = 0; // initialize total weight to be 0
    for (int i = 0; i < MST.size(); ++i) {
        cout << MST[i].s << " " << MST[i].t << " " << MST[i].w << endl; //print each edge
        weight += MST[i].w; 
    }
    cout << "MST weight = " << weight << endl;
}
int main() {
    int n;
    cin >> n; // make user key in the number of vertex
    vector<edge> edges; // a vector to store each edge in the graph
    int start = 1, end, weight;
    while (n--) { // for each vertex input vertex connected to it and the edge's weight
        while (cin >> end && end != 0) { // if the end point is 0 then break the input
            cin >> weight;
            edge tmp = edge(start, end, weight); // construct a edge 
            bool flag = false; // this flag is to cheak whether the edge is in edges already
            for (int i = 0; i < edges.size(); ++i) {
                if (edges[i] == tmp) { // if edge already in edges then do not add it again
                    flag = true;
                    break;
                }
            }
            if (!flag) // if edge not already in edges then add it
                edges.push_back(tmp);
        }
        start++; 
    }
    Merge_sort(edges); // sort the edges by weight(I use merge sort here)
    vector<set> disjoint_sets; //vector of disjoint sets
    vector<edge> MST; // vector of edges in MST
    for (int i = 0; i < edges.size(); ++i) { // Kruskal's algorithm
        int s_index = find(disjoint_sets, edges[i].s); // return the index which edges[i].s in 
        int t_index = find(disjoint_sets, edges[i].t); // return the index which edges[i].t in 
        if (s_index == -1 && t_index == -1) { // if s and t are both not in any set
            set new_set; // create a new set
            new_set.Insert(edges[i].s); // put s into new set
            new_set.Insert(edges[i].t); // put t into new set
            disjoint_sets.push_back(new_set); // put new set in disjoint set
            MST.push_back(edges[i]); // put the edge in MST
        }
        else if (s_index == -1 || t_index == -1) { // if ont of s or t is in disjoint sets
            if (s_index == -1) // if t in but s not in then append s in t's set
                disjoint_sets[t_index].Insert(edges[i].s);
            else  // if s in but t not in then append t in s's set
                disjoint_sets[s_index].Insert(edges[i].t);
            MST.push_back(edges[i]); // put th edge in MST
        }
        else if (s_index != t_index) { // if s and t in different sets
            disjoint_sets[s_index].Union(disjoint_sets[t_index]); // s = Union of two set
            swap(disjoint_sets[t_index], disjoint_sets[disjoint_sets.size() - 1]); // swap t's set and last set
            disjoint_sets.pop_back(); // pop the last set
            MST.push_back(edges[i]); // put the edge in MST
        }
        else // if s and t in same sets then reject the edge
            continue;
    }
    print_MST(MST); // print the MST
    return 0;
}
/*
4
2 1 3 3 4 2 0
1 1 4 4 0
1 3 4 5 0
2 4 3 5 1 2 0
*/
/*
9
2 10 3 12 0
1 10 3 9 4 8 0
1 12 2 9 5 3 6 1 0
2 8 5 7 7 8 8 5 0
3 3 4 7 6 3 0
3 1 5 3 8 6 0
4 8 8 9 9 2 0
4 5 6 6 7 9 9 11 0
7 2 8 11 0
*/
/*
7
2 5 3 1 4 4 0
1 5 4 8 6 6 0
1 1 4 3 5 2 0
1 4 2 8 3 3 6 8 0
3 2 6 7 7 9 0
2 6 4 8 5 7 0
5 9 0
*/
/*
5
5 1 2 15 3 9 0
1 15 4 6 5 18 0
1 9 5 4 4 23 0
2 6 3 23 5 11 0
1 1 3 4 4 11 2 18 0
*/