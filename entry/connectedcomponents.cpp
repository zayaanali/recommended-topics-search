#include "graph.h"


/** connectedcomponents.cpp
 * Runs Kosaraju's on the trimmed Wikipedia data set
 * Prints out the size of each strongly connected component
*/
int main() {
  //load graph
  Graph graph("../data/finaladj.txt", 15470);
  std::map<int,std::string> titles = load_titles("../data/finaltitles.txt", graph, 15470);

  //run Kosaraju's
  std::map<int, std::vector<int>> sccs = graph.getSCCs();

  //print out the number of connected components
  std::cout << sccs.size() << '\n';
  
  //print out the size of each strongly connected component
  for (unsigned int i = 0; i < sccs.size(); i++) {
    std::cout << i << ": " << sccs[i].size() << '\n';
  }
}