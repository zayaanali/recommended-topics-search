#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>
#include <unordered_set>
#include "graph.h"
using std::cout;
using std::endl;
using std::string;


TEST_CASE("test bfs trim 1 step") {
    Graph graph("../tests/testbfs1.txt", 12);
    std::vector<int> seeds = {1};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 1);
    std::unordered_set<int> expected({2, 3, 9, 1});
    REQUIRE(expected == actual);
}

TEST_CASE("test bfs trim 2 steps") {
    Graph graph("../tests/testbfs1.txt", 12);
    std::vector<int> seeds = {1};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 2);
    std::unordered_set<int> expected({2, 3, 9, 1, 8, 4, 10, 12, 7, 6});
    REQUIRE(expected == actual);
}

TEST_CASE("test bfs trim 3 steps") {
    Graph graph("../tests/testbfs1.txt", 12);
    std::vector<int> seeds = {1};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 3);
    std::unordered_set<int> expected({2, 3, 9, 1, 8, 4, 10, 12, 7, 6, 11, 5});
    REQUIRE(expected == actual);
}
TEST_CASE("test bfs trim line 4") {
    Graph graph("../tests/testbfs2.txt", 12);
    std::vector<int> seeds = {1};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 4);
    std::unordered_set<int> expected({1, 2, 3, 4, 5});
    REQUIRE(expected == actual);
}

TEST_CASE("test bfs trim line from middle") {
    Graph graph("../tests/testbfs2.txt", 12);
    std::vector<int> seeds = {5};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 4);
    std::unordered_set<int> expected({5, 6, 7, 8, 9});
    REQUIRE(expected == actual);
}

TEST_CASE("test bfs trim three lines") {
    Graph graph("../tests/testbfs5.txt", 8);
    std::vector<int> seeds = {1};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 2);
    std::unordered_set<int> expected({1, 2, 3, 5, 6, 8, 9});
    REQUIRE(expected == actual);
}
TEST_CASE("test bfs trim wheel 1") {
    Graph graph("../tests/test_brandes_wheel.txt", 7);
    std::vector<int> seeds = {1};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 1);
    std::unordered_set<int> expected({1, 2, 3, 4, 5, 6, 7});
    REQUIRE(expected == actual);
}
TEST_CASE("test bfs trim wheel 2") {
    Graph graph("../tests/test_brandes_wheel.txt", 7);
    std::vector<int> seeds = {2};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 1);
    std::unordered_set<int> expected({2,1});
    REQUIRE(expected == actual);
}
TEST_CASE("test bfs trim wheel 3") {
    Graph graph("../tests/test_brandes_wheel.txt", 7);
    std::vector<int> seeds = {2};
    std::unordered_set<int> actual = graph.BFS_Trim(seeds, 2);
    std::unordered_set<int> expected({1,2,3,4,5,6,7});
    REQUIRE(expected == actual);
}


