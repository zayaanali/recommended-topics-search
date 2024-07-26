#include "graph.h"


/** related_topics_two_inputs.cpp
 * takes two command line arguments of the indexes of two different Wikipedia pages
 * returns related topics to the given input by tracing back the shortest path between them and picking the node with the median betweenness centrality
 * when there are multiple predecessors to choose from.
*/

//map that stores betweenness centrality, defined globally so it can be referenced in functions
std::map<int,double> betweenness;


//compareB is a custom comparator that sorts Wikipedia pages by betweenness centrality
bool compareB(const int &a,const int &b) {
  return betweenness[a] < betweenness[b];
}

//"closest" is set when there is a direct link
double closest = 0;
//closeB is a custom comparator that sorts Wikipedia pages based on how close of a betweenness centrality
//they have to "closest" from most similar to least similar. 
bool closeB(const int &a,const int &b) {
  return std::abs(betweenness[a] - closest) < std::abs(betweenness[b] - closest);
}

int main(int argc, char** argv) {

  //check for correct number of arguments
  if (argc < 3) {
    std::cout << "You did not enter enough arguments. Please enter the indexes of two wikipedia pages" << '\n';
    return 0;
  }
  if (argc > 3) {
    std::cout << "You entered too many arguments. Please enter the indexes of two wikipedia pages" << '\n';
    return 0;
  }

  //load the graph
  Graph graph("../data/finaladj.txt", 15470);
  std::map<int,std::string> titles = load_titles("../data/finaltitles.txt", graph, 15470);
  
  //converts Wikipedia string titles to their index
  std::map<std::string,int> reverse_titles = load_titles_reverse("../data/finaltitles.txt", graph, 15470);

  //check to make sure the first topic is a valid page
  if (reverse_titles.find(argv[1]) == reverse_titles.end()) {
    std::cout << "The first argument is not a valid Wikipedia page title. Please try again." << '\n';
    return 0;
  }
  //check the second topic
  if (reverse_titles.find(argv[2]) == reverse_titles.end()) {
    std::cout << "The second argument is not a valid Wikipedia page title. Please try again." << '\n';
    return 0;
  }

  //convert strings to node indexes
  int topic1 = reverse_titles[argv[1]]; 
  int topic2 = reverse_titles[argv[2]]; 
  betweenness = load_betweenness("../data/betweenness.txt", graph, 15470);
  
  //find shortest paths to topic 1
  std::map<int, std::vector<int>> predecessor = graph.brandes_predecessor(topic1);
  
  //stores a group of three nodes from each step on the shortest path
  std::vector<std::vector<int>> street;

  //retraces the shortest path between topic2 and topic1
  int current = topic2;
  while (current != topic1) {
    std::vector<int> options = predecessor[current]; //access the predecessor vertices
    //break if there is no shortest path
    if (options.size() == 0) {
      break; 
    }
    //sort the predecessors from lowest betweenness centrality to highest
    std::sort(options.begin(), options.end(), compareB);

    //finds the middle three predecessors in "options"
    std::vector<int> collection;
    if (options[options.size() / 2] != topic1) {
      unsigned int median = options.size() / 2; //median node
      collection.push_back(options[median]);

      //pushes back the node to the right of the median and to the left if they exist
      if (median + 1 < options.size()) {
        collection.push_back(options[median + 1]);
      }
      if (median != 0) { //can't use -1 since median will overflow
        collection.push_back(options[median - 1]);
      }
    }
    // picks the node with the middle betweenness centrality if there are multiple predecessors when retracing the path
    // would be too costly to retrace every single shortest path
    current = options[options.size() / 2]; 
    //adds the middle three predecessors to "street"
    if (collection.size() > 0) {
      street.push_back(collection);
    }
  }
  //output the results
  std::cout << "~~~~~" << '\n';
  //direct link case
  if (street.size() == 0) {
    //set "closest", the global variable to be the betweenness centrality of topic2
    closest = betweenness[topic2];

    //get the neighbors of "topic1"
    std::vector<int> neighbors = graph.getAdjacent(topic1);
    //sort them by how close of a betweenness centrality they have to "closest"
    //index 0 should now be "topic2"
    std::sort(neighbors.begin(), neighbors.end(), closeB);
    //output results
    std::cout << "Direct link exists, finding neighbors of " << titles[topic1] << " similar to " << titles[topic2] << '\n';
    if (neighbors.size() == 1) { //index 0 is "topic2" itself
      std::cout << "No other neighbors found!" << '\n';
    }
    for (unsigned int i = 1; i < neighbors.size() && i <=3; i++) {
      std::cout << titles[neighbors[i]] << '\n';
    }

  } else {
    //goes to the group of predecessors at the middle distance on the path, should be most related to both topics
    for (int stop: street[street.size() / 2]) { 
      std::cout << titles[stop] << '\n';
    }
  }
  std::cout << "~~~~~" << '\n';
}
