#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include "graph.h"
using std::cout;
using std::endl;
using std::string;


TEST_CASE("test brandes no edges") {
    Graph graph("../tests/test_scc_no_edges.txt", 4);
    std::map<int, double> betweeness = graph.brandes();
    for (int i = 1; i <= 4; i++) {
        REQUIRE(betweeness[i] == 0); //nothing is connected
    }
}
TEST_CASE("test brandes simplest") {
    Graph graph("../tests/test_brandes_simplest.txt", 3);
    std::map<int, double> betweeness = graph.brandes();
    REQUIRE(betweeness[1] == 0);
    REQUIRE(betweeness[2] == 1);
    REQUIRE(betweeness[3] == 0);
}
TEST_CASE("test brandes simple 1") {
    Graph graph("../tests/test_brandes_simple1.txt", 4);
    std::map<int, double> betweeness = graph.brandes();
    REQUIRE(betweeness[1] == 0);
    REQUIRE(betweeness[2] == 2);
    REQUIRE(betweeness[3] == 2);
    REQUIRE(betweeness[4] == 0);
}
TEST_CASE("test brandes simple 2") {
    Graph graph("../tests/test_brandes_simple2.txt", 4);
    std::map<int, double> betweeness = graph.brandes();
    for (int i = 1; i <= 4; i++) {
        REQUIRE(betweeness[i] == 3); //graph is one cycle so all nodes should have the same centrality
    }
}
TEST_CASE("test brandes simple 3") {
    Graph graph("../tests/test_brandes_simple3.txt", 20);
    std::map<int, double> betweeness = graph.brandes();
    for (int i = 1; i <= 20; i++) {
        REQUIRE(betweeness[i] == 171); //graph is one cycle so all nodes should have the same centrality
        //1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12 + 13 + 14 + 15 + 16 + 17 + 18
    }
}
TEST_CASE("test brandes wheel") {
    Graph graph("../tests/test_brandes_wheel.txt", 7);
    std::map<int, double> betweeness = graph.brandes();
    REQUIRE(betweeness[1] == 30); //30 ordered pairs of the nodes on the outside of the wheel
    for (int i = 2; i <= 7; i++) {
        REQUIRE(betweeness[i] == 0); // check outside of wheel all have betweenness centrality of 0
    }
}
TEST_CASE("test brandes multiple shortest paths") {
    Graph graph("../tests/test_brandes_multiple_paths.txt", 8);
    std::map<int, double> betweeness = graph.brandes();
    //check nodes that aren't on any shortest paths
    REQUIRE(betweeness[1] == 0);
    REQUIRE(betweeness[4] == 0);
    //check middle nodes
    REQUIRE(betweeness[2] == (1.0/2.0) + (1.0/4.0));
    REQUIRE(betweeness[3] == (2.0/4.0) + (1.0/2.0) + 1 + (1.0/2.0));
    REQUIRE(betweeness[5] == 1 + (1.0/2.0) + (2.0/4.0));
    REQUIRE(betweeness[6] == (1.0/4.0) + (1.0/2.0));
    REQUIRE(betweeness[7] == (1.0/4.0) + 1);
    REQUIRE(betweeness[8] == (1.0/4.0) + 1);
}

