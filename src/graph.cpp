#include "graph.h"
#include <iostream>

/**
 * Constructor to read an file with a comma separated adjacency list (each line has the index followed by the indexes of all the adjacent nodes) and store it in a map adjacency list 
 * Node indexes are also stored in a set 
 * @param filename the name of the file with the comma separated adjacency list
 * @param num_vertices the number of vertices in the graph, should be equivalent to file length
*/
Graph::Graph(const std::string& filename, const int& num_vertices) {
    std::ifstream infile(filename); //edge file
    //load adj list
    std::string line;
    int idx = 0;
    while (infile) {
      if (idx == num_vertices) {
          break;
      }
      std::getline(infile, line);
      //check if line is empty
      if (line.length() == 0) {
        idx++;
        continue;
      }
      std::vector<int> parts;
      try {
        SplitString(line, ',', parts);
      } catch (...) {
        std::cout << "Could not find a valid nodeID on line: " << idx + 1 << '\n';
        std::cout << "Please check the input file" << '\n';
      }
      int nodeID = parts[0];
      idxs_.insert(nodeID);
      parts.erase(parts.begin());
      graph_[nodeID] = parts;
      idx++;
    }

}

/**
 * Runs BFS using the given "seeds" as starting points and traveling a certain number of steps away from the seeds. 
 * Nodes that are reached are added to the trimmed set.
 * @param seeds a vector of the starting points for the BFS
 * @param bound the number of steps to travel from each starting point
 * @return a set of all nodes within "bound" distance from at least one of the seeds, can be used to trim a graph to a single connected component
*/
std::unordered_set<int> Graph::BFS_Trim(const std::vector<int>& seeds, int bound) {
    std::unordered_set<int> trimmed;
    for (int id: seeds) {
        BFS(trimmed, id, bound);
    }
    return trimmed;
}

/**
  * Helper function for BFS_Trim. Runs BFS given a starting index.
  * Adds all nodes within a certain distance from the starting node to the set of trimmed nodes.
  * @param nodes the set to insert the nodes to
  * @param start the index of the starting node for the BFS
  * @param bound the number of steps to go from the starting node in the BFS traversal
*/
void Graph::BFS(std::unordered_set<int>& nodes, int start, int bound) {
  std::map<int, bool> visited;
  std::queue<int> q;
  std::map<int, int> distance;
  distance[start] = 0;
  visited[start] = true;
  q.push(start);
  while (!q.empty()) {
    int v = q.front();
    if (bound > 0 && distance[v] > bound) {
        break;
    }
    nodes.insert(v);
    q.pop();
    for (int neighbor: graph_[v]) {
      if (!visited[neighbor]) {
        distance[neighbor] = distance[v] + 1;
        visited[neighbor] = true;
        q.push(neighbor);

      }
    }
  }
}

/**
  * Runs BFS given a starting index and returns predecessor matrix.
  * @param start the starting index of the BFS
  * @return a map (matrix) of each index to its predecessor in the BFS
*/
std::map<int, int> Graph::BFS(int start) {
  std::map<int, bool> visited;
  std::map<int, int> predecessor;
  
  std::queue<int> q;
  std::map<int, int> distance;

  distance[start] = 0;
  visited[start] = true;
  q.push(start);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int neighbor: graph_[v]) {
      if (!visited[neighbor]) {
        distance[neighbor] = distance[v] + 1;
        visited[neighbor] = true;
        predecessor[neighbor] = v;
        q.push(neighbor);
      }
    }
  }
  return predecessor;
}

/**
 * Wrapper function to access the adjacency list
 * @param idx the index of the node
 * @return a vector of the indexes of the nodes adjacent to the input node
*/
std::vector<int> Graph::getAdjacent(int idx) {
    return graph_[idx];
}

/**
 * runs Brandes algorithm on the graph. Used pseudocode from https://people.csail.mit.edu/jshun/6886-s19/lectures/lecture3-2.pdf
 * @return a map storing the betweenness centrality of each node (maps index to betweeness centrality)
*/
std::map<int, double> Graph::brandes() {
  std::map<int, double> C_b;
  for (auto itr = idxs_.begin(); itr != idxs_.end(); itr++) {
    std::map<int, double> sigma;
    std::map<int, std::vector<int>> predecessor;
    std::stack<int> s;
    std::queue<int> q;
    std::map<int, intdefaultneg> distance; //intdefaultneg is a struct that holds an int initialized to -1
    std::map<int, double> delta;
    q.push(*itr);
    sigma[*itr] = 1;
    distance[*itr] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      s.push(v);
      for (int neighbor: graph_[v]) {
        if (distance[neighbor] < 0) {
          distance[neighbor] = distance[v] + 1;
          q.push(neighbor);
        }
        if (distance[neighbor] == distance[v] + 1) {
          sigma[neighbor] += sigma[v];
          predecessor[neighbor].push_back(v);
        }
      }
    }
    while (!s.empty()) {
      int w = s.top();
      s.pop();
      for (int v : predecessor[w]) {
        delta[v] += (sigma[v] / sigma[w])*(1 + delta[w]);
        if (*itr != w) {
          C_b[w] += delta[w];
        }
      }
    }
  }
  return C_b;
}

/**
 * runs BFS to find all shortest paths to the "start" node
 * @param start the vertex to find shortest paths to
 * @return a map storing predecessors of each vertex on the shortest path to "start"
*/
std::map<int, std::vector<int>> Graph::brandes_predecessor(int start) {
  std::map<int, std::vector<int>> predecessor;
  std::queue<int> q;
  std::map<int, intdefaultneg> distance; //intdefaultneg is a struct that holds an int initialized to -1
  q.push(start);
  distance[start] = 0;
  //BFS
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int neighbor: graph_[v]) {
      if (distance[neighbor] < 0) {
        distance[neighbor] = distance[v] + 1;
        q.push(neighbor);
      }
      if (distance[neighbor] == distance[v] + 1) {
        predecessor[neighbor].push_back(v);
      }
    }
  }
  return predecessor;
}

/**
 * Loads a CSV of the Wikipedia titles for each index into a map. 
 * Each line in the file should be of the form "index, title"
 * load_titles checks if the index is in the graph before adding it to the map of titles
 * @param filename the name of the file with the CSV of titles
 * @param graph the Graph that the titles are for
 * @param file_length the number of vertices in the graph/length of file
 * @return a mapping of each index to its Wikipedia article name
*/
std::map<int,std::string> load_titles(const std::string& filename, const Graph& graph, const int& file_length) {
    std::map<int,std::string> titles;
    std::ifstream infile2(filename); //titles file
    std::string line;
    int idx = 0;
    while (infile2) {
      if (idx == file_length) {
            break;
      }
      std::getline(infile2, line);
      std::stringstream s_stream(line);

      //check if line is empty
      if (line.length() == 0) {
        idx++;
        continue;
      }
      size_t pos = line.find(',');
      //convert id to int
      int id;
      try {
        id = std::stoi(line.substr(0, pos));
      } catch (...) {
        std::cout << "Could not find a valid nodeID on line: " << idx + 1 << '\n';
        std::cout << "Please check the input file" << '\n';
      }
      line.erase(0, pos + 1);
      titles[id] = line;
      idx++;
    }
    return titles;
}

/**
 * Loads a CSV of the Wikipedia titles for each index into a map in reverse.
 * Each line in the file should be of the form "title, index"
 * @param filename the name of the file with the CSV of titles
 * @param graph the Graph that the titles are for
 * @param file_length the number of vertices in the graph/length of file
 * @return a mapping of each Wikipedia article title to its index
*/
std::map<std::string,int> load_titles_reverse(const std::string& filename, const Graph& graph, const int& file_length) {
  std::map<std::string,int> titles;
    std::ifstream infile2(filename); //titles file
    std::string line;
    int idx = 0;
    while (infile2) {
      if (idx == file_length) {
            break;
      }
      std::getline(infile2, line);
      std::stringstream s_stream(line);
      //check if line is empty
      if (line.length() == 0) {
        idx++;
        continue;
      }
      size_t pos = line.find(',');
      //convert id to int
      int id;
      try {
        id = std::stoi(line.substr(0, pos));
      } catch (...) {
        std::cout << "Could not find a valid nodeID on line: " << idx + 1 << '\n';
        std::cout << "Please check the input file" << '\n';
      }
      line.erase(0, pos + 1);
      line = line.substr(1, line.length() - 2);
      titles[line] = id;
      idx++;
    }
    return titles;
}
/**
 * Loads a CSV of the betweenness centrality of each index into a map. 
 * Each line in the file should be of the form "index, betweenness centrality"
 * @param filename the name of the file with the CSV of titles
 * @param graph the Graph that the titles are for
 * @param file_length the number of vertices in the graph/length of file
 * @return a mapping of each index to its betweenness centrality
*/
std::map<int,double> load_betweenness(const std::string& filename, const Graph& graph, const int& file_length) {
  std::map<int,double> betweenness;
  std::ifstream infile2(filename); //titles file
  std::string line;
  int idx = 0;
  while (infile2) {
    if (idx == file_length) {
          break;
    }
    std::getline(infile2, line);
    std::stringstream s_stream(line);
    size_t pos = line.find(',');
    //check if line is empty
    if (line.length() == 0) {
      idx++;
      continue;
    }
    //convert id to int
    int id;
    try {
      id = std::stoi(line.substr(0, pos));
    } catch (...) {
      std::cout << "Could not find a valid nodeID on line: " << idx + 1 << '\n';
      std::cout << "Please check the input file" << '\n';
    }

    line.erase(0, pos + 1);
    betweenness[id] = stod(line);
    idx++;
  }
  return betweenness;
}
