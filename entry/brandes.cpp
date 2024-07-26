#include "graph.h"


/** brandes.cpp
 * Runs Brandes on the trimmed Wikipedia data set
 * Writes a CSV out to betweenness.txt where each line is of the form "node index","betweenness centrality"
 * WARNING: TAKES MULTIPLE HOURS TO RUN. 
 * OUTPUT FILE CAN BE DOWNLOADED USING THE LINK TO THE GOOGLE DRIVE FOLDER IN THE GIT REPO AT TOP OF DATA PARSING/TRIMMING SECTION
*/
int main() {
  //load graph
  Graph graph("../data/finaladj.txt", 15470);
  std::map<int,std::string> titles = load_titles("../data/finaltitles.txt", graph, 15470);

  //run Brandes
  std::map<int, double> betweenness = graph.brandes();

  //write out betweenness centrality output to file 
  std::ofstream Writing("../data/betweenness.txt");
  for (auto i: betweenness) {
    Writing << i.first << ',' << i.second << '\n';
  }
  Writing.close();
}
