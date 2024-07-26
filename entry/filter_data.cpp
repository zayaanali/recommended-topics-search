#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include<sstream>

/** filter_data.cpp
 * first step in data parsing pipeline
 * finds the top 24K nodes (nodes with the highest in-degree) from the downloaded data set of Wikipedia pages (Stanford Large Network Dataset Collection) and writes them to a file
 * writes output to "filteredwiki.txt"
 * each line in the output file has the node index followed by its title
 * output is sorted by highest in-degree (line 1 will be the node with the most links to it)
 * all nodes with more than 100 links to it are included in the initial filter.
*/

//function used as a custom comparator to sort a vector of pairs
bool compare(const std::pair<int,int> &a,const std::pair<int,int> &b) {
  return a.second > b.second;
}
int main() {
  //keeps track of the in-degree of each node
  std::map<int, int> log;

  //maps indexes to titles
  std::map<int,std::string> titles;

  //will hold the filtered set of nodes
  std::vector<std::pair<int,int>> filtered;

  std::ifstream infile("../data/wikidata.txt"); //edge file
  std::ifstream infile2("../data/enwiki-2013-names.csv"); //titles file


  std::string line;
  int idx = 0;
  while (infile2) {
    if (idx == 4206784) { //number of lines in file, will run into an error without this check
      break;
    }
    std::getline(infile2, line);
    std::stringstream s_stream(line);

    size_t pos = line.find(',');


    //splits the line by comma and converts the index to an int
    int nodeID = std::stoi(line.substr(0, pos));
    line.erase(0, pos + 1);
    //stores the title in titles map
    titles[nodeID] = line;
    idx++;
    
  }
  //keeps track of in-degrees by reading in every edge and adding to the destination of the edge
  int from, to;
  while (infile >> from >> to) {
    log[to]++;
  }

  //adds Wikipedia pages above the threshold to filtered
  for (auto i = log.begin(); i != log.end(); i++) {
    if (i->second > 450) {
      filtered.push_back(std::make_pair(i->first, i->second));
    }
  }
  //sorts filtered by in-degree, from greatest to least
  std::sort(filtered.begin(), filtered.end(), compare);

  //write out the filtered Wikipedia pages 
  std::ofstream Writing("../data/filteredwiki.txt");
  for (auto i: filtered) {
    if (i.first == 3165770) {
      continue; //Exclude "List of sovereign states"
    }
    Writing << i.first << ',' << titles[i.first] << '\n';
  }
  Writing.close();
  //print out the number of vertices remaining
  std::cout << "SIZE OF FILTERED IS: " << filtered.size() - 1 << '\n';
}
