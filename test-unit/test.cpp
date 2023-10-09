#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../src/Tree.h"
#include <iostream>
/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Small Left Rot.", "[Rotations]")
{
    std::cout << "BST Small Left Rot.\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve", 44958256);
    ourTree.InsertStudent("Tom", 87878787);
    ourTree.InsertStudent("Joey", 99999999);

    std::vector<int> actualOut;
    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    std::vector<int> expectedOut = {44958256, 87878787, 99999999};

    REQUIRE(ourTree.GetRoot()->heightGet() == 2);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
}


TEST_CASE("BST Small Right Rot.", "[Rotations]")
{
    std::cout << "BST Small Right Rot.\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve", 44958256);
    ourTree.InsertStudent("Tom", 31111111);
    ourTree.InsertStudent("Joey", 30000000);

    std::vector<int> actualOut;
    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    std::vector<int> expectedOut = {30000000, 31111111, 44958256};

    REQUIRE(ourTree.GetRoot()->heightGet() == 2);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
}

TEST_CASE("BST Right-Left Rot.", "[Rotations]")
{
    std::cout << "BST Right-Left Rot.\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve", 52500000);
    ourTree.InsertStudent("Tom", 50000000);
    ourTree.InsertStudent("Joey", 62500000);
    ourTree.InsertStudent("Sam", 65500000);
    ourTree.InsertStudent("Arthur", 64000000);

    std::vector<int> actualOut;
    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    std::vector<int> expectedOut = {50000000, 52500000, 62500000, 64000000, 65500000};

    REQUIRE(ourTree.GetRoot()->heightGet() == 3);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
}

TEST_CASE("BST Left-Right Rot.", "[Rotations]")
{
    std::cout << "BST Left-Right Rot.\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve", 52500000);
    ourTree.InsertStudent("Tom", 50000000);
    ourTree.InsertStudent("Joey", 62500000);
    ourTree.InsertStudent("Sam", 45000000);
    ourTree.InsertStudent("Arthur", 47000000);

    std::vector<int> actualOut;
    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    std::vector<int> expectedOut = {45000000, 47000000, 50000000, 52500000, 62500000};

    REQUIRE(ourTree.GetRoot()->heightGet() == 3);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
}