#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits.h>
#include <unordered_map>
#include <cmath>
using namespace std;
class MinHeapNode { // A Huffman tree node
public:
	char data; // One of the input characters
	unsigned freq; // Frequency of the character
	MinHeapNode *left, *right;// Left and right child
	MinHeapNode(char data, unsigned freq) : data(data), freq(freq) , left(nullptr), right(nullptr) {}
    class MinHeap {
    private:
        vector<MinHeapNode*> arr;// vector to store pointer to the min heap nodes
        int capacity; // maximum possible size of min heap
        int heap_size; // Current number of elements in min heap
    public:
        MinHeap(int cap) { // constructor with capacity n
            heap_size = 0;
            capacity = cap;
            arr = vector<MinHeapNode*>(cap, nullptr);
        }
        void MinHeapify(int i) { // to heapify a subtree with the root at given index
            int l = left(i);
            int r = right(i);
            int smallest = i;
            if (l < heap_size && arr[l] -> freq < arr[i] -> freq)
                smallest = l;
            if (r < heap_size && arr[r] -> freq < arr[smallest] -> freq)
                smallest = r;
            if (smallest != i) {
                swap(arr[i], arr[smallest]);
                MinHeapify(smallest);
            }
        }
        int size() { return heap_size;} 
        int parent(int i) { return (i - 1) / 2; } // to get index of left child of node at index i
        int left(int i) { return (2 * i + 1); } // to get index of right child of node at index i
        int right(int i) { return (2 * i + 2); } // to extract the root which is the minimum element
        // function to extract min node in heap and heapify the heap
        MinHeapNode* extractMin() { 
            if (heap_size <= 0)
                return new MinHeapNode('$', INT_MAX);
            if (heap_size == 1) {
                heap_size--;
                return arr[0];
            }
            // Store the minimum value, and remove it from heap
            MinHeapNode* root = arr[0];
            arr[0] = arr[heap_size - 1];
            heap_size--;
            MinHeapify(0);
            return root;
        }
        // Decreases key value of key at index i to new_val
        void decreaseKey(int i, int new_val) {
            arr[i] -> freq = new_val;
            while (i != 0 && arr[parent(i)] -> freq > arr[i] -> freq) {
                swap(arr[i], arr[parent(i)]);
                i = parent(i);
            }
        }
        // Returns the minimum key (key at root) from min heap
        MinHeapNode* getMin() { return arr[0]; }
        // Deletes a key stored at index i
        void deleteKey(int i) {
            decreaseKey(i, INT_MIN);
            extractMin();
        }
        // Inserts a new key 'k'
        void insertKey(MinHeapNode* k) {
            if (heap_size == capacity) {
                cout << "\nOverflow: Could not insertKey\n";
                return;
            }
            // First insert the new key at the end
            heap_size++;
            int i = heap_size - 1;
            arr[i] = k;
            // Fix the min heap property if it is violated
            while (i != 0 && arr[parent(i)] -> freq > arr[i] -> freq) {
                swap(arr[i], arr[parent(i)]);
                i = parent(i);
            }
        }
    };
};
// function use pointer to exchange two nodes
void swap(MinHeapNode* x, MinHeapNode* y) {
    MinHeapNode* temp = x;
    *x = *y;
    *y = *temp;
}
// Prints huffman codes from the root of Huffman Tree.
void printCodes(MinHeapNode* root, string str, unordered_map<char, string>& map) {
	if (root == nullptr)
		return;
	if (root -> data != '$') { // if not internode
		cout << root -> data << ": " << str << "\n";
        map[root -> data] = str;
    }
	printCodes(root -> left, str + "0", map); // left child
	printCodes(root -> right, str + "1", map); // right child
}
// function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
unordered_map<char, string> HuffmanCodes(vector<char> data, vector<unsigned> freq) {
    int size = data.size();
	MinHeapNode *left, *right, *top;
    MinHeapNode::MinHeap minHeap(data.size()); // construct a heap with capacity equal to data.size()
	for (int i = 0; i < size; ++i)
		minHeap.insertKey(new MinHeapNode(data[i], freq[i]));
	while (minHeap.size() != 1) { // choose two min nodes and merge them into one internode
		left = minHeap.extractMin();
		right = minHeap.extractMin();
		top = new MinHeapNode('$', left -> freq + right -> freq);
		top -> left = left;
		top -> right = right;
		minHeap.insertKey(top);
	}
	unordered_map<char, string> map; //a map to store the mapping from char to huffman code
    printCodes(minHeap.getMin(), "", map); // print the mapping of huffman code
    return map; // return the maping
}
int main() {
	ifstream file("text.txt");
    ofstream output("output.txt");
    string str, text;
    unordered_map<char, unsigned> count; // a map to sotre the char and its frequency
    while (getline(file, str)) { //read the file and get the frequency
        text += str + '\n'; // text is the entire file
        for (int i = 0; i < str.length(); ++i) 
            count[str[i]]++;
        count['\n']++;
    }
    vector<char> arr;
    vector<unsigned> freq;
    for (unordered_map<char, unsigned>::iterator it = count.begin(); it != count.end(); ++it) {
        // put char and its frequency into two vector
        arr.push_back(it -> first);
        freq.push_back(it -> second);
    }
	unordered_map<char, string> map = HuffmanCodes(arr, freq);
    unordered_map<string, char> rmap;
    // construct rmap to be the mapping from huffman code to its original character 
    for (unordered_map<char, string>::iterator it = map.begin(); it != map.end(); ++it) 
        rmap[it -> second] = it -> first;
    string coded; // s atring to represent the coded 
	for (int i = 0; i < text.length(); ++i) 
        coded += map[text[i]];
    str = "";
    string decoded; //decoded result
    for (int i = 0; i < coded.length(); ++i) {
        if (rmap.count(str)) { // if str is a key in map, put map[str] into decoded
            decoded += rmap[str];
            str = ""; // reset str to be empty
        }
        str += coded[i]; 
    }
    if (rmap.count(str)) // for i == coded.length()
        decoded += rmap[str];
    output << coded; // put coded into output file
    int original = ceil(log2(arr.size())) * text.length(); // calculate original data size
    int compressed =  coded.length(); // claculate compressed data size
    cout << "compression ratio = " << (1 - (static_cast<double>(compressed) / original)) * 100 << "%" << endl;
    cout << (decoded == text ? "decoded successfully" : "decoded failed") << endl; 
    file.close(); 
    output.close();
    return 0;
}