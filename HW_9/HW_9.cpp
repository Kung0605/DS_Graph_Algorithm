#include <iostream> //輸入輸出流
#include <limits.h> //initialize distance to be infinity
#include <vector> //use to replace heap and store some data 
using namespace std;
int minDistance(vector<int> dist, vector<bool> sptSet, int n) { // return the index of the closest vertex
	int min = INT_MAX, min_index;
	for (int v = 0; v < n; v++) {
		if (sptSet[v] == false && dist[v] <= min) // if v is not in spt and it is shorter than min
			min = dist[v], min_index = v; // set v to be min vertex
    }
	return min_index;
}
void printSolution(vector<int> dist, int n, vector<int> prev) { //print the solution
	cout << "Vertex \t Distance from Source \t Path" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " \t\t" << dist[i] << " \t\t"; // since 0-indexed so use i + 1 instead of i
		vector<int> path; // a vector to store path
		int p = i;
		while (p != -1) { // if p is -1 than it is finished
			path.push_back(p + 1); 
			p = prev[p]; // find previous vertex
		}
		for (int j = path.size() - 1; j >= 0; j--) // print the shortest path
			cout << path[j] << " ";
		cout << endl;
	}
}
void dijkstra(vector<vector<int>> graph, int src, int n) {
	vector<int> dist(n); // vector use to store the distances
	vector<bool> sptSet(n); // vector to check if a vertex is in shortest path tree
	vector<int> prev(n, -1); // previous vertex vector
	for (int i = 0; i < n; i++) // initialize dist to be infinity
		dist[i] = INT_MAX, sptSet[i] = false;
	dist[src] = 0; // distance of starting vertex is 0
	for (int count = 0; count < n - 1; count++) { 
		int u = minDistance(dist, sptSet, n);// choose vertex which is closest to source and not in shortest path tree
		sptSet[u] = true; // put it in the shortest path tree
		for (int v = 0; v < n; v++) // update the distance which is not in shortest path tree
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
				dist[v] = dist[u] + graph[u][v];
				prev[v] = u;
			}
	}
	printSolution(dist, n, prev); // print solution
}
int main() {
    int n;
    cin >> n;
	vector<vector<int>> graph (n, vector<int> (n, 0));
    for (int i = 0; i < n; ++i) {
        int pos;
        while (cin >> pos && pos != 0) 
            cin >> graph[i][pos - 1];
    }
	dijkstra(graph, 0, n);
	return 0;
}