#pragma once
#include <string>
#include "Student.h"


class Tree
{
public:
	Tree();
	~Tree();
	void InsertStudent(std::string, int);
	void RemoveStudent(int idToRemove);
	Student* SearchId(int idToSearch);
	Student* SearchRightmostNode(Student* _root);
	void SearchName(std::string nameToFind, Student* _root,
		std::vector<int>& foundMatches);
	void printInorder(Student* _root, Student* stoppingNode);
	void printPreorder(Student* _root, Student* stoppingNode);
	void printPostorder(Student* _root);
	void printLevelCount();
	Student* accessNthStudent(Student* _root, int& counter, int& n);
	void removeInorder(int n);
	void InsertionBalance(Student* startingNode);
	void BalanceTree(Student* parentOfDeletion);
	void RightRotation(Student* nodeToRotate);
	void LeftRotation(Student* nodeToRotate);
	int QuickBalanceGrab(Student* nodeToCheck);
	void QuickHeightUpdate(Student* startingNode);
	void EmptyTree(Student* _root);
	Student* GetRoot();
	size_t GetNodeCount();
    void InOrderTester(Student* _root, std::vector<int>& nodes);

private:
	Student* root{ nullptr };
	size_t nodeCount{ 0 };
};