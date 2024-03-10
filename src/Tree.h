#pragma once
#include <string>
#include "Student.h"


class Tree
{
public:
	Tree(); // Default constructor
	~Tree(); // Non-default destructor
	void InsertStudent(const std::string&, int); // Inserts students into tree
	void RemoveStudent(int idToRemove); // Removes students from tree
	Student* SearchId(int idToSearch); // Searches for students by id
	Student* SearchRightmostNode(Student* _root); // Grabs the most right node of given subtree root
	void SearchName(const std::string& nameToFind, Student* _root, // Searches for students by name
		std::vector<int>& foundMatches);
	void printInorder(Student* _root, Student* stoppingNode); // Prints tree in-order
	void printPreorder(Student* _root, Student* stoppingNode); // Prints tree pre-order
	void printPostorder(Student* _root); // Prints tree post-order
	void printLevelCount(); // Prints level count of tree
	Student* accessNthStudent(Student* _root, int& counter, int& n); // Returns nth student
	void removeInorder(int n); // Remove nth student in the in-order traversal of the tree
	void BalanceTree(Student* parentOfDeletion); // Takes node and balances and updates heights of tree
	void RightRotation(Student* nodeToRotate); // Performs right rotation
	void LeftRotation(Student* nodeToRotate); // Performs left rotation
	static int QuickBalanceGrab(Student* nodeToCheck); // Quickly grabs balance of a node
	static void QuickHeightUpdate(Student* startingNode); // Quickly updates height of a node
	void EmptyTree(Student* _root); // Used to empty the tree during tree destruction
	Student* GetRoot(); // Root getter
	size_t GetNodeCount() const; // Node getter
    void InOrderTester(Student* _root, std::vector<int>& nodes); // Used for catch2 testing

private:
	Student* root{ nullptr }; // Stores the root node of the tree
	size_t nodeCount{ 0 }; // Stores the node count of the tree
};