#include "utils.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
//COPIED FROM CS 225 CLASS FILES (splitstring is slightly modified for our purposes)
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

int SplitString(const std::string & str1, char sep, std::vector<int> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        if (str.substr(0, pos).length() > 0) {
            fields.push_back(std::stoi(str.substr(0,pos)));
        }
        str.erase(0,pos+1);  
    }
    if (str.length() == 1 && !std::isdigit(str[0])) {
        str = "";
    } //prevents weird bug for lines where vertices dont have neighbors
    if (str.length() > 0) {
        fields.push_back(std::stoi(str));
    }
    return fields.size();
}