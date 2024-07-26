#include "graph.h"


/** bfs_trim.cpp
  * fourth and final step in data parsing pipeline
  * Trims down the initially filtered 24K nodes to a single connected graph of around ~15K
  * Runs BFS_trim with 3 seeds. 
  * BFS will start at the 3 seeds ("US", "animal", and "food") and travel up to 2 steps away from the node
  * All nodes that are reached are added to the final set of nodes
  * Writes out the adjacency list of the trimmed, connected graph to "finaladj.txt"
  * Writes out the final CSV of title labels for each node index to "finaltitles.txt"
*/
int main() {

  std::map<int,std::string> titles;

  //will contain the set of trimmed nodes
  std::unordered_set<int> trimmed; 

  //load graph
  Graph graph("../data/filteredadj.txt", 23757);
  titles = load_titles("../data/filteredtitles.txt", graph, 23757);

  //set seeds
  std::vector<int> topten = {2038044, 3846441, 423902}; //United States, Animal, Food (3 general topics)
  trimmed = graph.BFS_Trim(topten, 2); //runs a BFS, going up to 2 steps away from each seed

  //print out size of trimmed data set
  std::cout << "Number of vertices: " << trimmed.size() << '\n';

  //write out the trimmed set of nodes and edges in an adjacency list and the titles for the remaining nodes

  std::ofstream Writing("../data/finaladj.txt");
  std::ofstream Writing2("../data/finaltitles.txt");

  //count the number of edegs
  int edges = 0;
  for (auto itr = trimmed.begin(); itr != trimmed.end(); itr++) {
    //writes out the trimmed titles, each line is "idx, titles"
    Writing2 << *itr << ',' << titles[*itr] << '\n'; 

    std::vector<int> adjacent = graph.getAdjacent(*itr);
    std::vector<int> newadj;

    //creates a new vector of adjacent neighbors (filters out all removed pages)
    for (int v: adjacent) { 
      if (trimmed.find(v) != trimmed.end()) {
        edges++;
        newadj.push_back(v);
      }
    }

    //format as a CSV
    std::string adding;
    for (int to: newadj) {
      adding += std::to_string(to) + ","; 
    }
    if (adding.length() > 0) {
      adding.pop_back(); //remove the comma at the end
    }
    Writing << *itr << ',' << adding << '\n'; //write out the line
  }

  Writing.close();
  Writing2.close();
  
  std::cout << "Number of edges: " << edges << '\n';
}
