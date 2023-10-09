#include <iostream>
#include <vector>
#include <queue>
#include "Tree.h"

Tree::Tree() {}

// DONE
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

// DONE
void Tree::InsertStudent(std::string studentName, int studentId)
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
	//Student* parent{ nullptr }; // Keep track of parent

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
				//InsertionBalance(currentNode);
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
				//InsertionBalance(currentNode);
				BalanceTree(currentNode);

				nodeCount++;
				std::cout << "successful\n";
				return;
			}
		}
	}




	/*
	while (currentNode != nullptr)
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
			parent = currentNode;
			currentNode = currentNode->leftGet();

			if (currentNode == nullptr)
			{
				// Null reached, insert new student on left of parent node
				parent->leftSet(new Student(studentName, studentId, parent));

				// TESTING
				std::cout << "Sending: " << parent->leftGet()->nameGet() << '\n';

				InsertionBalance(parent->leftGet());
				std::cout << "successful\n";
			}
		}
		// Id is greater than current node, go right
		else
		{
			parent = currentNode;
			currentNode = currentNode->rightGet();
			
			if (currentNode == nullptr)
			{
				// Null reached, insert new student on right of parent node
				parent->rightSet(new Student(studentName, studentId, parent));
				
				// TESTING
				std::cout << "Sending: " << parent->rightGet()->nameGet() << '\n';

				InsertionBalance(parent->rightGet());
				std::cout << "successful\n";
			}
		}
	}
	*/

	// Loop until null child found or non-unique id is determined
		// Start at root
		// Determine if new id matches current node id
			// If yes, print "unsuccessful" and return
		// Go left if less than current node, else go right 
		// Once null is reached, insert student
		
	// Update height & check for balance from current node to root
}

// DONE*****
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
		// Find largest left subtree node, this will become the replacer node
		Student* replacingNode
		{ SearchRightmostNode(studentToRemove->leftGet()) };

		// Store replacingNode's parent for future use
		Student* originalReplacingParent{ replacingNode->parentGet() };

		// Double link studentToRemove's parent and replacer
		if (studentToRemove->parentGet() != nullptr)
		{
			// Check if larger or smaller than parent
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

			replacingNode->parentSet(studentToRemove->parentGet());
		}
		else
		{
			replacingNode->parentSet(nullptr);
		}

		// If replacing node has a left child
		if (replacingNode->leftGet() != nullptr)
		{
			// Grab replacing node's original left child
			Student* originalReplacingLeft{ replacingNode->leftGet() };

			// If replacer's parent is the one being removed
			if (studentToRemove->leftGet() == replacingNode)
			{
				// Do nothing, original left will stay replacer's left child
			}
			else
			{
				// Replacer's parent will double link with 
				// replacer's original left
				originalReplacingParent->rightSet(originalReplacingLeft);
				originalReplacingLeft->parentSet(originalReplacingParent);
			}
		}

		// Adjust children of studentToRemove to double link with replacer
		// If studentToRemove has a left child
		if (studentToRemove->leftGet() != nullptr)
		{
			// If replacer is the immediate left child of studentToRemove
			if (studentToRemove->leftGet() == replacingNode)
			{
				// Do nothing
			}
			else
			{
				replacingNode->leftSet(studentToRemove->leftGet());
			}
		}
		// If studentToRemove has a right child
		if (studentToRemove->rightGet() != nullptr)
		{
			replacingNode->rightSet(studentToRemove->rightGet());
			replacingNode->rightGet()->parentSet(replacingNode);
		}

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

		/*
		// Take original parent of replacing node
		// Set it's right child to the replacing node's left child
		replacingNode->parentGet()->rightSet(origReplacingLeft);
		// Set that child to point back to it's new parent, if child exists
		if (origReplacingLeft != nullptr) 
		{ origReplacingLeft->parentSet(replacingNode->parentGet()); }
		

		// Now, Set replacing node's parent to student to remove's parent
		replacingNode->parentSet(studentToRemove->parentGet());
		// Make parent of "student to remove" point to replacer
		if (studentToRemove->parentGet() != nullptr)
		{
			// Check if larger or smaller than parent
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
		}

		// Set replacing node's children to "student to remove's" children
		replacingNode->leftSet(studentToRemove->leftGet());
		replacingNode->rightSet(studentToRemove->rightGet());
		// Set those children to point back to replacing node, if they exist
		if (studentToRemove->leftGet() != nullptr)
		{ studentToRemove->leftGet()->parentSet(replacingNode); }
		if (studentToRemove->rightGet() != nullptr)
		{ studentToRemove->rightGet()->parentSet(replacingNode); }

		// Check nodes to root for height/bal.
		// If origReplacingLeft isn't null, start there
		if (origReplacingLeft != nullptr) { BalanceTree(origReplacingLeft); }
		// Start at student to remove
		else { BalanceTree(studentToRemove); }
		
		// If "student to delete" was the root, set root to replacer
		if (studentToRemove == root) { root = replacingNode; }

		// Free memory, nullify pointer
		delete studentToRemove;
		studentToRemove = nullptr;

		// Print success and return
		std::cout << "successful\n";
		return;
		*/
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

// DONE
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

// DONE
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

// DONE
void Tree::SearchName(std::string nameToFind, Student* _root,
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

// DONE
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

	return;
}

// DONE
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

	return;


	/*
	// Subtree root doesn't exist, return
	if (_root == nullptr)
	{
		std::cout << "unsuccessful\n";
		return;
	}

	// Print the subtree root
	std::cout << _root->nameGet();

	// If either children exist we need a comma and to check further
	if ((_root->leftGet() != nullptr) || (_root->rightGet() != nullptr))
	{
		std::cout << ", ";
	}
	// No further nodes to check
	else
	{
		return;
	}
	
	// If left exists, recurse left
	if (_root->leftGet() != nullptr)
	{
		printPreorder(_root->leftGet());
	}

	// If both children exist we need another comma
	if ((_root->leftGet() != nullptr) && (_root->rightGet() != nullptr))
	{
		std::cout << ", ";
	}

	// If right exists, recurse right
	if (_root->rightGet() != nullptr)
	{
		printPreorder(_root->rightGet());
	}

	return;*/
}

// DONE
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
	
	return;
}

// DONE
void Tree::printLevelCount()
{
	if (root != nullptr)
	{
		// 1-based level count
		std::cout << root->heightGet() << '\n';
	}
	else
	{
		std::cout << "unsuccessful\n";
	}
}

// DONE
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

// DONE*
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
	nodeCount--;
}

// DO I STILL NEED THIS????
void Tree::InsertionBalance(Student* parent)
{
	// Start at parent node

	// Loop:
		// Update height if needed
		// Grab left and right height
		// calculate balance and store according to "i"
		// rotate if needed
			// exit loop
		// ++i & currentNode move to parent

	Student* currentNode{ parent };
	size_t rightHeight{ 0 };
	size_t leftHeight{ 0 };
	int firstBalance{ 0 };
	int secondBalance{ 0 };
	int i{ 0 };

	while (currentNode != nullptr)
	{
		// Grab left child's height
		if (currentNode->leftGet() != nullptr)
		{
			leftHeight = static_cast<int>(currentNode->leftGet()->heightGet());
		}
		else
		{
			leftHeight = 0;
		}
		
		// Grab right child's height
		if (currentNode->rightGet() != nullptr)
		{
			rightHeight = static_cast<int>(currentNode->rightGet()->heightGet());
		}
		else
		{
			rightHeight = 0;
		}

		// Update height of node:
		if ((currentNode->heightGet() == rightHeight) ||
			(currentNode->heightGet() == leftHeight))
		{
			currentNode->heightSet(currentNode->heightGet() + 1);
		}
		else
		{
			// Do not update height of current node
		}

		// Calculate node balance
		if (i == 0) 
		{ 
			firstBalance = (rightHeight - leftHeight);

			// TESTING:
			//std::cout << "firstBalance: " << currentNode->nameGet() << " : " << firstBalance << '\n';

			i++;
		}
		else if (i == 1)
		{
			secondBalance = (rightHeight - leftHeight);

			// TESTING:
			//std::cout << "secondBalance: " << currentNode->nameGet() << " : " << secondBalance << '\n';

			i--;		
		}
		else
		{
			std::cout << "Error: Balance Calculation\n";
		}

		if (abs(firstBalance) > 1)
		{
			if (firstBalance == -2)
			{
				if (secondBalance == -1)
				{
					// Left-Left Imbalance: Right Rot.
					std::cout << "Left-Left Imbalance: Right Rot.\n";
					RightRotation(currentNode->leftGet());

					// Adjust height of original parent
					currentNode->heightSet(currentNode->heightGet() - 2);
				}
				else if (secondBalance == 1)
				{
					// Left-Right Imbalance: Left-Right Rot.
					std::cout << "Left-Right Imbalance: Left-Right Rot.\n";
					LeftRotation(currentNode->leftGet()->rightGet());
					// Adjust heights d/t rotational change
					currentNode->leftGet()->leftGet()->heightDec();
					currentNode->leftGet()->heightInc();

					RightRotation(currentNode->leftGet());
					// Adjust heights d/t rotational change
					currentNode->heightDec();
					currentNode->heightDec();
				}
				else
				{
					std::cout << "Error: Balance Calculation 1\n";
				}
			}
			else if (firstBalance == 2)
			{
				if (secondBalance == -1)
				{
					// Right-Left Imbalance: Right-Left Rot.
					std::cout << "Right-Left Imbalance: Right-Left Rot.\n";
					RightRotation(currentNode->rightGet()->leftGet());
					// Adjust heights d/t rotational change
					currentNode->rightGet()->rightGet()->heightDec();
					currentNode->rightGet()->heightInc();

					LeftRotation(currentNode->rightGet());
					// Adjust heights d/t rotational change
					currentNode->heightDec();
					currentNode->heightDec();
				}
				else if (secondBalance == 1)
				{
					// Right-Right Imbalance: Left Rot.
					std::cout << "Right-Right Imbalance: Left Rot.\n";
					LeftRotation(currentNode->rightGet());

					// Adjust height of original parent
					currentNode->heightSet(currentNode->heightGet() - 2);
				}
				else
				{
					std::cout << "Error: Balance Calculation 2\n";
				}
			}
			else
			{
				std::cout << "Error: Balance Calculation 3\n";
			}

			// Balanced, so, reset balances
			firstBalance = 0;
			secondBalance = 0;

			// Adjust currentNode to account for rotational changes
			currentNode = currentNode->parentGet();
		}
		else if (abs(secondBalance) > 1)
		{
			if (secondBalance == -2)
			{
				if (firstBalance == -1)
				{
					// Left-Left Imbalance: Right Rot.
					std::cout << "Left-Left Imbalance: Right Rot.\n";
					RightRotation(currentNode->leftGet());

					// Adjust height of original parent
					currentNode->heightSet(currentNode->heightGet() - 2);
				}
				else if (firstBalance == 1)
				{
					// Left-Right Imbalance: Left-Right Rot.
					std::cout << "Left-Right Imbalance: Left-Right Rot.\n";
					LeftRotation(currentNode->leftGet()->rightGet());
					// Adjust heights d/t rotational change
					currentNode->leftGet()->leftGet()->heightDec();
					currentNode->leftGet()->heightInc();

					RightRotation(currentNode->leftGet());
					// Adjust heights d/t rotational change
					currentNode->heightDec();
					currentNode->heightDec();
				}
				else
				{
					std::cout << "Error: Balance Calculation 4\n";
				}
			}
			else if (secondBalance == 2)
			{
				if (firstBalance == -1)
				{
					// Right-Left Imbalance: Right-Left Rot.
					std::cout << "Right-Left Imbalance: Right-Left Rot.\n";
					RightRotation(currentNode->rightGet()->leftGet());
					// Adjust heights d/t rotational change
					currentNode->rightGet()->rightGet()->heightDec();
					currentNode->rightGet()->heightInc();

					LeftRotation(currentNode->rightGet());
					// Adjust heights d/t rotational change
					currentNode->heightDec();
					currentNode->heightDec();
				}
				else if (firstBalance == 1)
				{
					// Right-Right Imbalance: Left Rot.
					std::cout << "Right-Right Imbalance: Left Rot.\n";
					LeftRotation(currentNode->rightGet());

					// Adjust height of original parent
					currentNode->heightSet(currentNode->heightGet() - 2);
				}
				else
				{
					std::cout << "Error: Balance Calculation 5\n";
				}
			}
			else
			{
				std::cout << "Error: Balance Calculation 6\n";
			}

			// Balanced, so, reset balances
			firstBalance = 0;
			secondBalance = 0;

			// Adjust currentNode to account for rotational changes
			currentNode = currentNode->parentGet();
		}

		currentNode = currentNode->parentGet();
	}
}

// DONE*
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
		balance = (rightHeight - leftHeight);

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

					// Adjust height of original parent
					//currentNode->heightSet(currentNode->heightGet() - 2);
				}
				// Left child balance right leaning
				else if (leftChildBalance == 1)
				{
					// Left-Right Imbalance: Left-Right Rot.
					LeftRotation(currentNode->leftGet()->rightGet());
					// Adjust heights d/t rotational change
					//currentNode->leftGet()->leftGet()->heightDec();
					//currentNode->leftGet()->heightInc();

					RightRotation(currentNode->leftGet());
					// Adjust heights d/t rotational change
					//currentNode->heightDec();
					//currentNode->heightDec();
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
					// Adjust heights d/t rotational change
					//currentNode->rightGet()->rightGet()->heightDec();
					//currentNode->rightGet()->heightInc();

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

// DONE
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

// DONE
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

// DONE
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

// DONE
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

// DONE
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

	return;
}

// DONE
Student* Tree::GetRoot() { return root; }

// DONE
size_t Tree::GetNodeCount() { return nodeCount; }

void Tree::InOrderTester(Student* _root, std::vector<int>& nodes)
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
        InOrderTester(_root->leftGet(), nodes);
    }

    nodes.push_back(_root->studentIdGet());

    // Go right recursively if it exists
    if (_root->rightGet() != nullptr)
    {
        InOrderTester(_root->rightGet(), nodes);
    }

    return;
}
