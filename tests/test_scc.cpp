#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <unordered_set>
#include "graph.h"
using std::cout;
using std::endl;
using std::string;


TEST_CASE("test scc simple 1") {
    Graph graph("../tests/test_scc_simple.txt", 5);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 3);
    std::vector<std::unordered_set<int>> expecteds;
    std::unordered_set<int> expected1({0, 1, 2});
    std::unordered_set<int> expected2({3});
    std::unordered_set<int> expected3({4});
    expecteds.push_back(expected1);
    expecteds.push_back(expected2);
    expecteds.push_back(expected3);
    for (int i = 0; i < 3; i++) {
        std::unordered_set<int> actual(sccs[i].begin(), sccs[i].end());
        REQUIRE(actual == expecteds[i]);
    }
}

TEST_CASE("test scc simple 2") {
    Graph graph("../tests/test_scc_simple2.txt", 8);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 3);
    std::unordered_set<int> expected1({0});
    std::unordered_set<int> expected2({1,2,3,4});
    std::unordered_set<int> expected3({5,6,7});
    std::vector<std::unordered_set<int>> expecteds;
    expecteds.push_back(expected1);
    expecteds.push_back(expected2);
    expecteds.push_back(expected3);
    for (int i = 0; i < 3; i++) {
        std::unordered_set<int> actual(sccs[i].begin(), sccs[i].end());
        REQUIRE(actual == expecteds[i]);
    }
}
TEST_CASE("test scc line not connected") {
    //straight line of vertices
    Graph graph("../tests/testbfs2.txt", 12);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 13);
}
TEST_CASE("test scc line connected") {
    //straight line of vertices
    Graph graph("../tests/test_scc_line_connected.txt", 13);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 1);
}
TEST_CASE("test scc three linked") {
    //straight line of vertices
    Graph graph("../tests/test_scc_three_linked.txt", 6);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 3);
    std::unordered_set<int> expected1({0,1});
    std::unordered_set<int> expected2({2,3});
    std::unordered_set<int> expected3({4,5});
    std::vector<std::unordered_set<int>> expecteds;
    expecteds.push_back(expected1);
    expecteds.push_back(expected2);
    expecteds.push_back(expected3);
    for (int i = 0; i < 3; i++) {
        std::unordered_set<int> actual(sccs[i].begin(), sccs[i].end());
        REQUIRE(actual == expecteds[i]);
    }
}
TEST_CASE("test scc disconnected") {
    //two unconnected loops
    Graph graph("../tests/test_scc_disconnected.txt", 6);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 2);
    std::unordered_set<int> expected1({0,1,2});
    std::unordered_set<int> expected2({3,4,5});
    std::vector<std::unordered_set<int>> expecteds;
    expecteds.push_back(expected1);
    expecteds.push_back(expected2);
    for (int i = 0; i < 2; i++) {
        std::unordered_set<int> actual(sccs[i].begin(), sccs[i].end());
        REQUIRE(actual == expecteds[i]);
    }
}

TEST_CASE("test scc no edges") {
    //only nodes
    Graph graph("../tests/test_scc_no_edges.txt", 4);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 4);
    std::unordered_set<int> expected1({0});
    std::unordered_set<int> expected2({1});
    std::unordered_set<int> expected3({2});
    std::unordered_set<int> expected4({3});
    std::vector<std::unordered_set<int>> expecteds;
    expecteds.push_back(expected1);
    expecteds.push_back(expected2);
    expecteds.push_back(expected3);
    expecteds.push_back(expected4);
    for (int i = 0; i < 4; i++) {
        std::unordered_set<int> actual(sccs[i].begin(), sccs[i].end());
        REQUIRE(actual == expecteds[i]);
    }
}

TEST_CASE("test scc loop branch") {
    //only nodes
    Graph graph("../tests/test_scc_loop_branch.txt", 6);
    std::map<int, std::vector<int>> sccs = graph.getSCCs();
    REQUIRE(sccs.size() == 3);
    std::unordered_set<int> expected1({1, 2, 5, 6});
    std::unordered_set<int> expected2({3});
    std::unordered_set<int> expected3({4});
    std::vector<std::unordered_set<int>> expecteds;
    expecteds.push_back(expected1);
    expecteds.push_back(expected2);
    expecteds.push_back(expected3);
    for (int i = 0; i < 3; i++) {
        std::unordered_set<int> actual(sccs[i].begin(), sccs[i].end());
        REQUIRE(actual == expecteds[i]);
    }
}


