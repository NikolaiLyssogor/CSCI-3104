#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

void addEdge(vector<int> adj[], int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
}

void printGraph(vector<int> adj[], int V) {
  for (int v = 0; v < V; v++) {
        cout << "\n Adjacency list of vertex "
             << v << "\n head ";
        for (auto x : adj[v])
           cout << "-> " << x;
        printf("\n");
    }
}

// modified breadth-first search
int countVerticesHelper(vector<int> adj[], bool visited[], int node, int k, int distance) {
  visited[node] = true;

  // counts vertices in this subtree
  int count = 1;

  // stop recursing once we've searched wide enough
  if(distance == k) return 1;

  // call helper function on all adjacent nodes
  for(int i = 0; i < adj[node].size(); i++) {
    // recurse on nodes that haven't been visited
    if(!visited[adj[node][i]])
      count += countVerticesHelper(adj, visited, adj[node][i], k, distance + 1);
  }

  // all adjacent nodes have been visited
  return count;
}

int countVertices(vector<int> adj[], int V, int start, int k) {
  // edge cases
  if(k == 0) return 0;
  if(k == 1) return adj[start].size();

  int count = 0;

  // keep track of visited nodes
  int distance = 1;
  bool visited[V];
  memset(visited, false, sizeof(visited));
  visited[start] = true;

  // call helper function for each vertex the starting node is connected to
  for(int i = 0; i < adj[start].size(); i++) {
    count += countVerticesHelper(adj, visited, adj[start][i], k, distance);
  }

  return count;
}

int main() {
  // graph test cas has same structure as one pictured in the PDF
  int V = 12;
  vector<int> adj[V];

  addEdge(adj, 0, 7);
  addEdge(adj, 0, 1);
  addEdge(adj, 1, 2);
  addEdge(adj, 0, 3);
  addEdge(adj, 3, 4);
  addEdge(adj, 4, 5);
  addEdge(adj, 3, 6);
  addEdge(adj, 0, 8);
  addEdge(adj, 8, 9);
  addEdge(adj, 9, 10);
  addEdge(adj, 10, 11);

  // printGraph(adj, V);

  cout << countVertices(adj, V, 0, 2);

  return 0;
}
