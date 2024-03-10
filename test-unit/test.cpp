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

TEST_CASE("BST Complex 1", "[Complex]")
{
    std::cout << "BST Complex 1\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve", 52500000);
    ourTree.RemoveStudent(52500000);

    std::vector<int> actualOut;
    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    std::vector<int> expectedOut = {};

    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);

    ourTree.InsertStudent("John", 51500000);
    ourTree.InsertStudent("Eve", 61500000);
    ourTree.InsertStudent("Adam", 42500000);
    ourTree.InsertStudent("Jacob", 50500000);
    ourTree.RemoveStudent(61500000);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {42500000, 50500000, 51500000};

    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    REQUIRE(ourTree.GetRoot()->studentIdGet() == 50500000);
    actualOut.clear();
    expectedOut.clear();

    ourTree.InsertStudent("Eve", 61500000);
    ourTree.InsertStudent("Sam", 40000000);
    ourTree.RemoveStudent(50500000);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {40000000, 42500000, 51500000, 61500000};

    REQUIRE(ourTree.GetRoot()->studentIdGet() == 42500000);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    ourTree.InsertStudent("Lindsey", 61000000);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {40000000, 42500000, 51500000, 61000000, 61500000};

    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    ourTree.RemoveStudent(61000000);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {40000000, 42500000, 51500000, 61500000};

    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    ourTree.RemoveStudent(61500000);
    ourTree.RemoveStudent(42500000);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {40000000, 51500000};

    REQUIRE(ourTree.GetRoot()->studentIdGet() == 40000000);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    ourTree.RemoveStudent(51500000);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {40000000};

    REQUIRE(ourTree.GetRoot()->studentIdGet() == 40000000);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    ourTree.RemoveStudent(40000000);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {};

    REQUIRE(ourTree.GetRoot() == nullptr);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();
}

TEST_CASE("BST Large 1", "[Large]")
{
    std::cout << "BST Large 1\n";

    Tree* ourTree = new Tree();   // Create a Tree object

    ourTree->InsertStudent("Steve", 52500000);
    ourTree->InsertStudent("Tom", 50000000);
    ourTree->InsertStudent("Joey", 62500000);
    ourTree->InsertStudent("Sam", 45000000);
    ourTree->InsertStudent("Arthur", 47000000);
    ourTree->InsertStudent("Albert", 65500000);
    ourTree->InsertStudent("Johnny", 75000000);
    ourTree->InsertStudent("Samantha", 62550000);
    ourTree->InsertStudent("Benjamin", 22000000);
    ourTree->InsertStudent("Einstein", 77000000);
    ourTree->InsertStudent("George", 33300000);
    ourTree->InsertStudent("Carol", 11110000);
    ourTree->InsertStudent("Mike", 69800000);
    ourTree->InsertStudent("Joel", 98770000);
    ourTree->InsertStudent("Luke", 48830000);
    ourTree->InsertStudent("Madonna", 51110000);
    ourTree->InsertStudent("Mary", 55550000);
    ourTree->InsertStudent("Buster", 99990000);
    ourTree->InsertStudent("Joanna", 12120000);
    ourTree->InsertStudent("Jose", 47550000);
    ourTree->InsertStudent("Velma", 46460000);
    ourTree->InsertStudent("Nelson", 12340000);
    ourTree->InsertStudent("Bob", 51230000);
    ourTree->InsertStudent("Max", 94500000);
    ourTree->InsertStudent("Daisy", 77770000);

    std::vector<int> actualOut;
    ourTree->InOrderTester(ourTree->GetRoot(), actualOut);
    std::vector<int> expectedOut = {11110000, 12120000, 12340000, 22000000, 33300000, 45000000, 46460000, 47000000,
                                    47550000, 48830000, 50000000, 51110000, 51230000, 52500000, 55550000, 62500000,
                                    62550000, 65500000, 69800000, 75000000, 77000000, 77770000, 94500000, 98770000,
                                    99990000};

    REQUIRE(ourTree->GetRoot()->studentIdGet() == 52500000);
    REQUIRE(ourTree->GetRoot()->heightGet() == 6);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();


    ourTree->RemoveStudent(50000000);
    ourTree->RemoveStudent(65500000);
    ourTree->RemoveStudent(11110000);
    ourTree->RemoveStudent(47000000);
    ourTree->RemoveStudent(77000000);
    ourTree->RemoveStudent(52500000);

    ourTree->InOrderTester(ourTree->GetRoot(), actualOut);
    expectedOut = {12120000, 12340000, 22000000, 33300000, 45000000, 46460000,
                   47550000, 48830000, 51110000, 51230000, 55550000, 62500000,
                   62550000, 69800000, 75000000, 77770000, 94500000, 98770000,
                   99990000};

    REQUIRE(ourTree->GetRoot()->studentIdGet() == 51230000);
    REQUIRE(ourTree->GetRoot()->heightGet() == 5);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);

    delete ourTree;
    ourTree = nullptr;
}


TEST_CASE("BST Traversals 1", "[Traversals]")
{
    std::cout << "BST Traversals 1\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve", 52500000);
    ourTree.InsertStudent("Tom", 50000000);
    ourTree.InsertStudent("Joey", 62500000);
    ourTree.InsertStudent("Sam", 45000000);
    ourTree.InsertStudent("Arthur", 47000000);

    std::cout << "In: ";
    ourTree.printInorder(ourTree.GetRoot(),
                          ourTree.SearchRightmostNode(ourTree.GetRoot()));

    std::cout << "Pre: ";
    ourTree.printPreorder(ourTree.GetRoot(),
                           ourTree.SearchRightmostNode(ourTree.GetRoot()));

    std::cout << "Post: ";
    ourTree.printPostorder(ourTree.GetRoot());
}

TEST_CASE("BST In-Order Test", "[Removals]")
{
    std::cout << "BST In-Order Test\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve Jobs", 52500000);
    ourTree.InsertStudent("Tom Banks", 50000000);
    ourTree.InsertStudent("Joey Esquire", 62500000);
    ourTree.InsertStudent("Sam Adams", 45000000);
    ourTree.InsertStudent("Arthur Morgan", 47000000);
    ourTree.InsertStudent("Diane Nom", 65000000);
    ourTree.InsertStudent("Jessica Aloe", 87500000);
    ourTree.InsertStudent("Albert Einstein", 99900000);
    ourTree.InsertStudent("Mary Linton", 22200000);
    ourTree.InsertStudent("Linda French", 87800000);

    std::vector<int> actualOut;
    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    std::vector<int> expectedOut = {22200000, 45000000, 47000000, 50000000, 52500000, 62500000, 65000000, 87500000,
                                    87800000, 99900000};

    REQUIRE(ourTree.GetNodeCount() == 10);
    REQUIRE(ourTree.GetRoot()->heightGet() == 4);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    // Grab ID of student to remove
    int nthToRemove{ 0 };

    // Call removeInorder
    ourTree.removeInorder(nthToRemove);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {45000000, 47000000, 50000000, 52500000, 62500000, 65000000, 87500000,
                                    87800000, 99900000};

    REQUIRE(ourTree.GetNodeCount() == 9);
    REQUIRE(ourTree.GetRoot()->heightGet() == 4);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    // Grab ID of student to remove
    nthToRemove = 8;

    // Call removeInorder
    ourTree.removeInorder(nthToRemove);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {45000000, 47000000, 50000000, 52500000, 62500000, 65000000, 87500000,
                   87800000};

    REQUIRE(ourTree.GetNodeCount() == 8);
    REQUIRE(ourTree.GetRoot()->heightGet() == 4);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    // Grab ID of student to remove
    nthToRemove = 5;

    // Call removeInorder
    ourTree.removeInorder(nthToRemove);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {45000000, 47000000, 50000000, 52500000, 62500000, 87500000,
                   87800000};

    REQUIRE(ourTree.GetNodeCount() == 7);
    REQUIRE(ourTree.GetRoot()->heightGet() == 3);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    // Grab ID of student to remove
    nthToRemove = 3;

    // Call removeInorder
    ourTree.removeInorder(nthToRemove);

    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    expectedOut = {45000000, 47000000, 50000000, 62500000, 87500000,
                   87800000};

    REQUIRE(ourTree.GetNodeCount() == 6);
    REQUIRE(ourTree.GetRoot()->studentIdGet() == 50000000);
    REQUIRE(ourTree.GetRoot()->heightGet() == 3);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();
}

TEST_CASE("BST Special-Case Removal 1", "[Removals]")
{
    std::cout << "BST Special-Case Removal 1\n";

    Tree ourTree;   // Create a Tree object

    ourTree.InsertStudent("Steve Jobs", 52500000);
    ourTree.InsertStudent("Tom Banks", 50000000);
    ourTree.InsertStudent("Joey Esquire", 62500000);
    ourTree.InsertStudent("Sam Adams", 45000000);
    ourTree.InsertStudent("Arthur Morgan", 47000000);
    ourTree.InsertStudent("Diane Nom", 65000000);

    ourTree.RemoveStudent(47000000);

    std::vector<int> actualOut;
    ourTree.InOrderTester(ourTree.GetRoot(), actualOut);
    std::vector<int> expectedOut = {45000000, 50000000, 52500000, 62500000, 65000000};

    REQUIRE(ourTree.GetNodeCount() == 5);
    REQUIRE(ourTree.GetRoot()->heightGet() == 3);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();

    ourTree.InsertStudent("Arthur Morgan", 47000000);
    ourTree.InsertStudent("George Lopez", 40000000);

    ourTree.RemoveStudent(47000000);

    REQUIRE(ourTree.GetNodeCount() == 6);
    REQUIRE(ourTree.GetRoot()->heightGet() == 3);
    REQUIRE(expectedOut.size() == actualOut.size());
    REQUIRE(actualOut == expectedOut);
    actualOut.clear();
    expectedOut.clear();
}
