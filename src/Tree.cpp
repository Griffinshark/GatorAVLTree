#include <iostream>
#include <vector>
#include <queue>
#include "Tree.h"

Tree::Tree() = default;

Tree::~Tree()
{
	// If tree is not empty, make it so
	if (root != nullptr)
	{
		// Call to empty tree: delete all the nodes and free memory
		EmptyTree(root);

		// Set root to null
		root = nullptr;
	}
}

void Tree::InsertStudent(const std::string& studentName, int studentId)
{
	// First element insert
	if (root == nullptr)
	{
		root = new Student(studentName, studentId, nullptr);
		nodeCount++;
		std::cout << "successful\n";
		return;
	}

	Student* currentNode{ root }; // Start at root

	// Loop until null child found or non-unique id is determined
	while (true)
	{
		// Check if new ID already exists
		if (studentId == currentNode->studentIdGet())
		{
			std::cout << "unsuccessful\n";
			return;
		}
		// Id is less than current node, go left
		else if (studentId < currentNode->studentIdGet())
		{
			if (currentNode->leftGet() != nullptr)
			{
				currentNode = currentNode->leftGet();
			}
			else
			{
				// Null reached, insert new student on left of current
				// (parent) node
				currentNode->leftSet(new Student(studentName, studentId, currentNode));

				// CHECK BALANCE:
				BalanceTree(currentNode);

				nodeCount++;
				std::cout << "successful\n";
				return;
			}
		}
		// Id is greater than current node, go right
		else
		{
			if (currentNode->rightGet() != nullptr)
			{
				currentNode = currentNode->rightGet();
			}
			else
			{
				// Null reached, insert new student on right of current
				// (parent) node
				currentNode->rightSet(new Student(studentName, studentId, currentNode));

				// CHECK BALANCE:
				BalanceTree(currentNode);

				nodeCount++;
				std::cout << "successful\n";
				return;
			}
		}
	}
}

void Tree::RemoveStudent(int idToRemove)
{
	// Edge case: deleting a lone root
	if (idToRemove == root->studentIdGet() && (root->leftGet() == nullptr) 
		&& (root->rightGet() == nullptr))
	{
		// Free memory, nullify pointer
		delete root;
		root = nullptr;
		nodeCount--;

		// Print success and return
		std::cout << "successful\n";
		return;
	}

	Student* studentToRemove{ SearchId(idToRemove) };

	// If student to remove is non-existent
	if (studentToRemove == nullptr) 
	{ 
		std::cout << "unsuccessful\n";
		return;
	}

	// Student is a leaf
	if (studentToRemove->heightGet() == 1)
	{
		// Check if larger or smaller than parent
		if (studentToRemove->studentIdGet()
			< studentToRemove->parentGet()->studentIdGet())
		{
			// Smaller than parent, set parent left to null
			studentToRemove->parentGet()->leftSet(nullptr);
		}
		else
		{
			// Larger than parent, set parent right to null
			studentToRemove->parentGet()->rightSet(nullptr);
		}

		// Check/Update heights and balances
		BalanceTree(studentToRemove->parentGet());

		// Free memory, nullify pointer
		delete studentToRemove;
		studentToRemove = nullptr;
		nodeCount--;

		// Print success and return
		std::cout << "successful\n";
		return;
	}
	// Student has two children
	else if ((studentToRemove->leftGet() != nullptr)
		&& (studentToRemove->rightGet() != nullptr))
	{
		// Find the largest left subtree node, this will become the replacer node
		Student* replacingNode
		{ SearchRightmostNode(studentToRemove->leftGet()) };

        // Save replacer's original parent for further down
        Student* repOriginalParent{replacingNode->parentGet()};

		// Double link studentToRemove's parent and replacer
		if (studentToRemove->parentGet() != nullptr)
		{
			// Setting parent to replacer
			if (studentToRemove->studentIdGet()
				< studentToRemove->parentGet()->studentIdGet())
			{
				// Smaller than parent, set parent left to replacing node
				studentToRemove->parentGet()->leftSet(replacingNode);
			}
			else
			{
				// Larger than parent, set parent left to replacing node
				studentToRemove->parentGet()->rightSet(replacingNode);
			}

            // Setting replacing node -> parent
			replacingNode->parentSet(studentToRemove->parentGet());
		}
		else
		{
			replacingNode->parentSet(nullptr);
		}

		// Adjust children of studentToRemove to double link with replacer
        // If replacer is the immediate left child of studentToRemove
        if (studentToRemove->leftGet() == replacingNode)
        {
            // Do nothing
        }
        else
        {
            // Set replacer's original parent to it's left child, null or not
            repOriginalParent->rightSet(replacingNode->leftGet());

            replacingNode->leftSet(studentToRemove->leftGet());
            replacingNode->leftGet()->parentSet(replacingNode);
        }
        replacingNode->rightSet(studentToRemove->rightGet());
        replacingNode->rightGet()->parentSet(replacingNode);

		// If "student to delete" was the root, set root to replacer
		if (studentToRemove == root) { root = replacingNode; }

		// Check tree height and balance
		// Start balance and height adjuster at replacer's left if it exists
		if (replacingNode->leftGet() != nullptr)
		{
			BalanceTree(replacingNode->leftGet());
		}
		else
		{
			BalanceTree(replacingNode);
		}

		// Free memory, nullify pointer
		delete studentToRemove;
		studentToRemove = nullptr;
		nodeCount--;

		// Print success and return
		std::cout << "successful\n";
		return;
	}
	// Student has only left child
	else if ((studentToRemove->leftGet() != nullptr)
		&& (studentToRemove->rightGet() == nullptr))
	{
		// See what side of parent, "student to remove" is on
		// Make that parent side point to student's left child
		if (studentToRemove->parentGet() != nullptr) 
		{
			if (studentToRemove->studentIdGet()
				< studentToRemove->parentGet()->studentIdGet())
			{
				studentToRemove->parentGet()->leftSet(studentToRemove->leftGet());
			}
			else
			{
				studentToRemove->parentGet()->rightSet(studentToRemove->leftGet());
			}
		}
		
		// Set this left child to point back to the parent
		studentToRemove->leftGet()->parentSet(studentToRemove->parentGet());

		// Check/Update heights and balances
		BalanceTree(studentToRemove->leftGet());

		// If "student to delete" was the root, set root to student's left
		if (studentToRemove == root) { root = studentToRemove->leftGet(); }

		// Free memory, nullify pointer
		delete studentToRemove;
		studentToRemove = nullptr;
		nodeCount--;

		// Print success and return
		std::cout << "successful\n";
		return;
	}
	// Student has only right child
	else if ((studentToRemove->leftGet() == nullptr)
		&& (studentToRemove->rightGet() != nullptr))
	{
		// See what side of parent, "student to remove" is on
		// Make that parent side point to student's right child
		if (studentToRemove->parentGet() != nullptr)
		{
			if (studentToRemove->studentIdGet()
				< studentToRemove->parentGet()->studentIdGet())
			{
				studentToRemove->parentGet()->leftSet(studentToRemove->rightGet());
			}
			else
			{
				studentToRemove->parentGet()->rightSet(studentToRemove->rightGet());
			}
		}

		// Set this right child to point back to the parent
		studentToRemove->rightGet()->parentSet(studentToRemove->parentGet());

		// Check/Update heights and balances
		BalanceTree(studentToRemove->rightGet());

		// If "student to delete" was the root, set root to student's right
		if (studentToRemove == root) { root = studentToRemove->rightGet(); }

		// Free memory, nullify pointer
		delete studentToRemove;
		studentToRemove = nullptr;
		nodeCount--;

		// Print success and return
		std::cout << "successful\n";
		return;
	}
	else
	{
		std::cout << "Error: removal 1\n";
	}
}

Student* Tree::SearchId(int idToSearch)
{
	// Start at the root
	Student* currentNode{ root };

	while (currentNode != nullptr)
	{
		// ID match found, return student
		if (idToSearch == currentNode->studentIdGet())
		{
			return currentNode;
		}
		// ID not matched, keep looking
		else
		{
			// ID is less than current node, go left if possible
			if (idToSearch < currentNode->studentIdGet())
			{
				// Possible, go left
				if (currentNode->leftGet() != nullptr)
				{
					currentNode = currentNode->leftGet();
				}
				// Not possible, ID cannot exist
				else
				{
					return nullptr;
				}
			}
			// ID is greater than current node, go right if possible
			else
			{
				// Possible, go right
				if (currentNode->rightGet() != nullptr)
				{
					currentNode = currentNode->rightGet();
				}
				// Not possible, ID cannot exist
				else
				{
					return nullptr;
				}
			}
		}
	}

	// Just-in-case return
	return nullptr;
}

Student* Tree::SearchRightmostNode(Student* _root)
{
	Student* rightmostNode{nullptr};

	if (_root->rightGet() != nullptr)
	{
		rightmostNode = SearchRightmostNode(_root->rightGet());
	}
	else
	{
		rightmostNode = _root;
	}

	return rightmostNode;
}

void Tree::SearchName(const std::string& nameToFind, Student* _root,
	std::vector<int>& foundMatches)
{
	// If _root is null, nothing in this position, return
	if (_root == nullptr) 
	{  
		return;
	}

	// Match found in node, store in passed vector
	if (nameToFind == _root->nameGet())
	{
		foundMatches.push_back(_root->studentIdGet());
	}

	// If left child exists, search there recursively
	if (_root->leftGet() != nullptr) 
	{ 
		SearchName(nameToFind, _root->leftGet(), foundMatches);
	}

	// If right child exists, search there recursively
	if (_root->rightGet() != nullptr)
	{
		SearchName(nameToFind, _root->rightGet(), foundMatches);
	}
}

void Tree::printInorder(Student* _root, Student* stoppingNode)
{
	// Subtree root doesn't exist, happens if tree is empty
	if (_root == nullptr)
	{
		std::cout << "unsuccessful\n";
		return;
	}

	// Go left recursively if it exists
	if (_root->leftGet() != nullptr)
	{
		printInorder(_root->leftGet(), stoppingNode);
	}

	// If at the stopping node, print node and don't add comma
	if (_root == stoppingNode)
	{
		std::cout << _root->nameGet() << '\n';
		return;
	}
	// Print node with comma and continue
	else
	{
		std::cout << _root->nameGet() << ", ";
	}

	// Go right recursively if it exists
	if (_root->rightGet() != nullptr)
	{
		printInorder(_root->rightGet(), stoppingNode);
	}
}

void Tree::printPreorder(Student* _root, Student* stoppingNode)
{
	// Subtree root doesn't exist, happens if tree is empty
	if (_root == nullptr)
	{
		std::cout << "unsuccessful\n";
		return;
	}

	// If at the stopping node or is the left child of stop
	if (_root == stoppingNode || _root->parentGet() == stoppingNode)
	{
		// Edge case: rightmost node has a left child
		if (_root->leftGet() != nullptr)
		{
			std::cout << _root->nameGet() << ", ";
			printPreorder(_root->leftGet(), stoppingNode);
			return;
		}
		// If no left child for stopping node, or at left child of stop
		else
		{
			std::cout << _root->nameGet() << '\n';
			return;
		}
	}
	// Print node with comma and continue
	else
	{
		std::cout << _root->nameGet() << ", ";
	}

	// Go left recursively if it exists
	if (_root->leftGet() != nullptr)
	{
		printPreorder(_root->leftGet(), stoppingNode);
	}

	// Go right recursively if it exists
	if (_root->rightGet() != nullptr)
	{
		printPreorder(_root->rightGet(), stoppingNode);
	}
}

void Tree::printPostorder(Student* _root)
{
	// Subtree root doesn't exist, return
	if (_root == nullptr)
	{
		return;
	}

	// If left exists, recurse left
	if (_root->leftGet() != nullptr)
	{
		printPostorder(_root->leftGet());
	}

	// If right exists, recurse right
	if (_root->rightGet() != nullptr)
	{
		printPostorder(_root->rightGet());
	}

	// Print the subtree root, if/else for comma placement
	if (_root == root) { std::cout << _root->nameGet() << '\n'; }
	else { std::cout << _root->nameGet() << ", "; }
}

void Tree::printLevelCount()
{
	if (root != nullptr)
	{
		// 1-based level count
		std::cout << root->heightGet() << '\n';
	}
    // Tree is empty
	else
	{
		std::cout << 0 << '\n';
	}
}

Student* Tree::accessNthStudent(Student* _root, int& counter, int& n) 
{
	Student* nthStudent{ nullptr };

	// If left exists, go left
	if (_root->leftGet() != nullptr)
	{
		nthStudent = accessNthStudent(_root->leftGet(), counter, n);
	}

	// Increment count at this node and this point
	++counter;

	// Index reached:
	if (counter == n) { return _root; }

	// If (counter > n), we already have what we need, so return
	else if (counter > n) { return nthStudent; }

	// If right exists, go right
	if (_root->rightGet() != nullptr)
	{
		nthStudent = accessNthStudent(_root->rightGet(), counter, n);
	}

	return nthStudent;
}

void Tree::removeInorder(int n)
{
	// Index must be positive
	if (n < 0)
	{
		std::cout << "unsuccessful\n";
		return;
	}

	// Start count will be "-1" for proper counting/indexing
	int startCount{ -1 };

	// Grab the nth student
	Student* nthStudent = accessNthStudent(root, startCount, n);

	// Remove them
	RemoveStudent(nthStudent->studentIdGet());
}

void Tree::BalanceTree(Student* parent)
{
	Student* currentNode{ parent };
	size_t rightHeight{ 0 };
	size_t leftHeight{ 0 };
	int balance{ 0 };
	int rightChildBalance{ 0 };
	int leftChildBalance{ 0 };

	while (currentNode != nullptr)
	{
		// Grab child heights
		if (currentNode->leftGet() != nullptr)
		{
			leftHeight = static_cast<int>(currentNode->leftGet()->heightGet());
		}
		else
		{
			leftHeight = 0;
		}

		if (currentNode->rightGet() != nullptr)
		{
			rightHeight = static_cast<int>(currentNode->rightGet()->heightGet());
		}
		else
		{
			rightHeight = 0;
		}

		// Update height of parent/current node to be greater by one of larger child height
		if (rightHeight == leftHeight)
		{
			if (currentNode->heightGet() != (rightHeight + 1))
			{
				currentNode->heightSet(static_cast<size_t>(rightHeight + 1));
			}
		}
		else if (rightHeight > leftHeight)
		{
			if (currentNode->heightGet() != (rightHeight + 1))
			{
				currentNode->heightSet(static_cast<size_t>(rightHeight + 1));
			}
		}
		else
		{
			if (currentNode->heightGet() != (leftHeight + 1))
			{
				currentNode->heightSet(static_cast<size_t>(leftHeight + 1));
			}	
		}

		// Calculate balance
		balance = static_cast<int>(rightHeight - leftHeight);

		// Imbalance found
		if (abs(balance) > 1)
		{
			// Parent balance left leaning
			if (balance == -2)
			{
				// Find left child's balance
				leftChildBalance = QuickBalanceGrab(currentNode->leftGet());

				// Left child balance left leaning or special case
				if (leftChildBalance == -1 || leftChildBalance == 0)
				{
					// Left-Left Imbalance: Right Rot.
					RightRotation(currentNode->leftGet());
				}
				// Left child balance right leaning
				else if (leftChildBalance == 1)
				{
					// Left-Right Imbalance: Left-Right Rot.
					LeftRotation(currentNode->leftGet()->rightGet());

					RightRotation(currentNode->leftGet());
				}
				else
				{
					std::cout << "Error: balance in left child is off\n";
				}
			}
			// Parent balance right leaning
			else if (balance == 2)
			{
				// Find right child's balance
				rightChildBalance = QuickBalanceGrab(currentNode->rightGet());

				// Right child balance right leaning or special case
				if (rightChildBalance == 1 || rightChildBalance == 0)
				{
					// Right-Right Imbalance: Left Rot.
					LeftRotation(currentNode->rightGet());
				}
				// Right child balance left leaning
				else if (rightChildBalance == -1)
				{
					// Right-Left Imbalance: Right-Left Rot.
					RightRotation(currentNode->rightGet()->leftGet());

					LeftRotation(currentNode->rightGet());
				}
				else
				{
					std::cout << "Error: balance in right child is off\n";
					std::cout << rightChildBalance << '\n';
				}
			}
			else
			{
				std::cout << "Error: balance in parent is off\n";
			}

			// Balanced, so, reset balances
			balance = 0;
			leftChildBalance = 0;
			rightChildBalance = 0;

			// Adjust currentNode to account for rotational changes
			currentNode = currentNode->parentGet();
		}
		
		if (currentNode != nullptr)
		{
			currentNode = currentNode->parentGet();
		}
	}
}

void Tree::RightRotation(Student* nodeToRotate)
{
	Student* temp{ nullptr };
	Student* originalParent{ nodeToRotate->parentGet() };
	Student* grandparent{ nullptr };

	// If original parent is the root, change root to be nodeToRotate
	if (originalParent == root)
	{
		root = nodeToRotate;
	}

	// If nodeToRotate has right child, save to temp
	if (nodeToRotate->rightGet() != nullptr)
	{
		temp = nodeToRotate->rightGet();
	}

	// If grandparent exists
	if (originalParent->parentGet() != nullptr)
	{
		grandparent = originalParent->parentGet();

		// Compare parent value to grandparent to determine child direction
		// Left child
		if (originalParent->studentIdGet()
			< grandparent->studentIdGet())
		{
			// Make grandparent point to nodeToRotate
			grandparent->leftSet(nodeToRotate);
		}
		// Right child
		else
		{
			// Make grandparent point to nodeToRotate
			grandparent->rightSet(nodeToRotate);
		}
	}

	// Set nodeToRotate parent to grandparent
	nodeToRotate->parentSet(originalParent->parentGet());

	//  Original parent will become nodeToRotate's right child
	nodeToRotate->rightSet(originalParent);

	// Make original parent's parent now set to nodeToRotate
	originalParent->parentSet(nodeToRotate);

	// Set original parent's left child to nullptr or temp if it exists
	if (temp == nullptr)
	{
		originalParent->leftSet(nullptr);
	}
	else
	{
		originalParent->leftSet(temp);
		temp->parentSet(originalParent);
	}

    // Starting at original parent, check/update heights to root
    QuickHeightUpdate(originalParent);
}

void Tree::LeftRotation(Student* nodeToRotate)
{
	Student* temp{ nullptr };
	Student* originalParent{ nodeToRotate->parentGet() };
	Student* grandparent{ nullptr };

	// If original parent is the root, change root to be nodeToRotate
	if (originalParent == root)
	{
		root = nodeToRotate;
	}

	// If nodeToRotate has left child, save to temp
	if (nodeToRotate->leftGet() != nullptr)
	{
		temp = nodeToRotate->leftGet();
	}

	// If grandparent exists
	if (originalParent->parentGet() != nullptr)
	{
		grandparent = originalParent->parentGet();

		// Compare parent value to grandparent to determine child direction
		// Left child
		if (originalParent->studentIdGet()
			< grandparent->studentIdGet())
		{
			// Make grandparent point to nodeToRotate
			grandparent->leftSet(nodeToRotate);
		}
		// Right child
		else
		{
			// Make grandparent point to nodeToRotate
			grandparent->rightSet(nodeToRotate);
		}
	}

	// Set nodeToRotate parent to grandparent
	nodeToRotate->parentSet(originalParent->parentGet());

	//  Original parent will become nodeToRotate's left child
	nodeToRotate->leftSet(originalParent);

	// Make original parent's parent now set to nodeToRotate
	originalParent->parentSet(nodeToRotate);

	// Set original parent's right child to nullptr or temp if it exists
	if (temp == nullptr)
	{
		originalParent->rightSet(nullptr);
	}
	else
	{
		originalParent->rightSet(temp);
		temp->parentSet(originalParent);
	}

	// Starting at original parent, check/update heights to root
	QuickHeightUpdate(originalParent);
}

int Tree::QuickBalanceGrab(Student* nodeToCheck)
{
	int rightChildHeight{ 0 };
	int leftChildHeight{ 0 };

	// If left child exists, grab height, otherwise height stays zero
	if (nodeToCheck->leftGet() != nullptr)
	{
		leftChildHeight = static_cast<int>(nodeToCheck->leftGet()->heightGet());
	}

	// If right child exists, grab height, otherwise height stays zero
	if (nodeToCheck->rightGet() != nullptr)
	{
		rightChildHeight = static_cast<int>(nodeToCheck->rightGet()->heightGet());
	}

	// Return "balance = (rightChildHeight - leftChildHeight)"
	return (rightChildHeight - leftChildHeight);
}

void Tree::QuickHeightUpdate(Student* startingNode)
{
	size_t rightHeight{ 0 };
	size_t leftHeight{ 0 };
	Student* currentNode{ startingNode };

	while (currentNode != nullptr)
	{
		// Grab child heights
		if (currentNode->leftGet() != nullptr)
		{
			leftHeight = static_cast<int>(currentNode->leftGet()->heightGet());
		}
		else
		{
			leftHeight = 0;
		}

		if (currentNode->rightGet() != nullptr)
		{
			rightHeight = static_cast<int>(currentNode->rightGet()->heightGet());
		}
		else
		{
			rightHeight = 0;
		}

		// Update height of parent/current node to be greater by one of larger child height
		if (rightHeight == leftHeight)
		{
			if (currentNode->heightGet() != (rightHeight + 1))
			{
				currentNode->heightSet(static_cast<size_t>(rightHeight + 1));
			}
		}
		else if (rightHeight > leftHeight)
		{
			if (currentNode->heightGet() != (rightHeight + 1))
			{
				currentNode->heightSet(static_cast<size_t>(rightHeight + 1));
			}
		}
		else
		{
			if (currentNode->heightGet() != (leftHeight + 1))
			{
				currentNode->heightSet(static_cast<size_t>(leftHeight + 1));
			}
		}

		currentNode = currentNode->parentGet();
	}
}

void Tree::EmptyTree(Student* _root)
{
	// If left exists, go left to further delete, then, nullify left
	if (_root->leftGet() != nullptr)
	{
		EmptyTree(_root->leftGet());
		_root->leftSet(nullptr);
	}

	// If right exists, go right to further delete, then, nullify right
	if (_root->rightGet() != nullptr)
	{
		EmptyTree(_root->rightGet());
		_root->rightSet(nullptr);
	}

	// Now, delete node and nullify _root
	delete _root;
	_root = nullptr;
}

Student* Tree::GetRoot() { return root; }

size_t Tree::GetNodeCount() const { return nodeCount; }

void Tree::InOrderTester(Student* _root, std::vector<int>& nodes)
{
    // Subtree root doesn't exist, happens if tree is empty
    if (_root == nullptr)
    {
        return;
    }

    // Go left recursively if it exists
    if (_root->leftGet() != nullptr)
    {
        InOrderTester(_root->leftGet(), nodes);
    }

    nodes.push_back(_root->studentIdGet());

    // Go right recursively if it exists
    if (_root->rightGet() != nullptr)
    {
        InOrderTester(_root->rightGet(), nodes);
    }
}
