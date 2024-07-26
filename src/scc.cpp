#include "graph.h"
#include <stack>

using std::vector;
using std::map;
using std::stack;
using std::endl;

/**
 * Runs Kosaraju's algorithm on the graph to find connected components
 * @return Returns a map mapping an index to each connected component
*/
map<int, vector<int>> Graph::getSCCs() {
    int numComponents=0; // number of strongly connected components
    stack<int> s;
    map<int, vector<int>> SCCs; // adjacency list of SCCs
    //visited_ is already initialized with false as default values

    // Get DFS traversal order, visit each node
    for (auto itr = idxs_.begin(); itr != idxs_.end(); itr++) {
        if (!visited_[*itr]) {
            dfs_1(*itr, s);
        }
    }
    // create transpose of graph


    map<int, vector<int>> transpose;
    for (auto itr = idxs_.begin(); itr != idxs_.end(); itr++) {
        for (int neighbor: graph_[*itr]) {
            int src = neighbor;
            int dest = *itr;
            transpose[src].push_back(dest);
        }
    }

    // reset visited array to false
    visited_.clear();

    // pop nodes from DFS stack and perform dfs again
    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (!visited_[v]) {
            dfs_2(v, SCCs, numComponents, transpose); // prints all the CCs
            numComponents++;
        }
    }
    return SCCs;
}

// DFS traversal order
void Graph::dfs_1(int v, stack<int> &s)  {
    // mark visited
    visited_[v] = true;

    // continue DFS
    for (int neighbor: graph_[v]) {
        if (!visited_[neighbor])
            dfs_1(neighbor, s);
    }
    // record traversal order
    s.push(v);
}

// DFS traversal order
void Graph::dfs_2(int v, map<int, vector<int>> &SCCs,  int &numComponents, map<int, vector<int>> &transpose) {
    SCCs[numComponents].push_back(v); // add connected component
    visited_[v] = true;

    // continue DFS on transposed graph
    for (int neighbor: transpose[v]) {
        if (!visited_[neighbor])
            dfs_2(neighbor, SCCs, numComponents, transpose);
    }
}