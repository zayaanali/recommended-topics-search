#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <unordered_set>
#include<sstream>

/** filter_edges.cpp
 * second step in data parsing pipeline
 * creates and stores an adjacency list with only the top 24K nodes from the Wikipedia data set
 * Uses the edges file and the list of top 24K nodes from "filter_data.cpp" to create the adjacency list
 * writes out output to "filteredadj.txt" as a csv where each line has the index of the node followed by all the nodes it is adjacent to
*/
int main() {
  //stores the current full adjacency list
  std::map<int, std::vector<int>> full_adj;

  //stores the set of nodes that were not filtered out (~24K)
  std::unordered_set<int> trimmed;

  //open the file generated from "filter_data"
  std::ifstream infile("../data/filteredwiki.txt");
  std::ifstream infile2("../data/wikidata.txt"); //original edge file
  
  //construct original adjacency list
  int from, to;
  while (infile2 >> from >> to) {
    full_adj[from].push_back(to); //push back "to" to the vector containing neighbors of "from"
  }

  //read the remaining vertices from "filteredwiki.txt"
  std::string line;
  int idx = 0;
  while (infile) {
    if (idx == 23757) { //length of file, will run into error without this check
      break;
    }
    std::getline(infile, line);
    std::stringstream s_stream(line);
    size_t pos = line.find(',');
    int nodeID = std::stoi(line.substr(0, pos));
    //add to the set of valid vertices
    trimmed.insert(nodeID);
    idx++;
  }

  //write out adjacency list
  std::ofstream Writing("../data/filteredadj.txt");

  //iterate over every vertex and update its neighbors
  for (auto itr = trimmed.begin(); itr != trimmed.end(); itr++) {
    //get current vector of neighbors
    std::vector<int> adjacent = full_adj[*itr];
    std::vector<int> newadj;

    //create a new vector of neighbors with only valid vertices
    for (int v: adjacent) {
      if (trimmed.find(v) != trimmed.end()) {
        newadj.push_back(v);
      }
    }

    //write out index of node and its neighbors as a line in the CSV containing the output adjacency list
    std::string adding;
    for (int to: newadj) {
      adding += std::to_string(to) + ","; 
    }
    //remove the extra comma at the end
    if (adding.length() > 0) {
      adding.pop_back();
    }
    //write out to the CSV
    Writing << *itr << ',' << adding << '\n';
  }
  Writing.close();
}
