#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include "Tree.h"

// Checks for valid name
bool NameChecker(std::string name);

// Checks for valid ID
bool IdChecker(std::string id);

// Checks for valid "n"
bool NCheck(std::string n);

int main()
{
    size_t commandsNum{ 0 };
    std::cin >> commandsNum;

    if (commandsNum < 1) // They may want something different here
    {
        std::cout << "Commands must be 1 or greater\n";
        commandsNum = 0;
    }

    std::string currentCommand{ "" }; // Stores the current command
    std::cin.ignore(); // Flush cin buffer for getline command

    Tree* ourTree = new Tree(); // Create the tree

    // Perform each command
    for (size_t i = 0; i < commandsNum; ++i)
    {
        std::getline(std::cin, currentCommand);

        // insert NAME ID
        if (currentCommand.substr(0, 8) == "insert \"")
        {
            std::string studentName{ "" };
            std::string studentId{ "" };

            // Grab student name
            std::stringstream commandStream{ currentCommand.substr(8) };
            std::getline(commandStream, studentName, '\"');
            // Run name checks
            bool nameCheck = NameChecker(studentName);

            if (!nameCheck)
            {
                std::cout << "unsuccessful\n";
                continue;
            }

            // Grab student id
            studentId = currentCommand.substr(10 + studentName.length());
            // Run id checks
            bool idCheck = IdChecker(studentId);
            
            if (!idCheck)
            {
                std::cout << "unsuccessful\n";
                continue;
            }

            int convertedStudentId{ stoi(studentId) };

            ourTree->InsertStudent(studentName, convertedStudentId);
        }
        // remove ID
        else if (currentCommand.substr(0, 7) == "remove ")
        {
            // Grab student id
            std::string studentId = currentCommand.substr(7);
            // Run id checks
            bool idCheck = IdChecker(studentId);

            if (!idCheck)
            {
                std::cout << "unsuccessful\n";
                continue;
            }

            int convertedStudentId{ stoi(studentId) };

            // Remove the student
            ourTree->RemoveStudent(convertedStudentId);
        }
        // search NAME
        else if (currentCommand.substr(0, 8) == "search \"")
        {
            // Grab student name to search for
            std::string nameToFind{ "" };
            std::stringstream commandStream{ currentCommand.substr(8) };
            std::getline(commandStream, nameToFind, '\"');
            // Run name checks
            bool nameCheck = NameChecker(nameToFind);

            if (!nameCheck)
            {
                std::cout << "unsuccessful\n";
                continue;
            }

            // Will store found matches to print once located with search func.
            std::vector<int> foundMatches;

            // Run search function in the tree, will store results in our
            // created vector
            ourTree->SearchName(nameToFind, ourTree->GetRoot(), foundMatches);

            // No matches found
            if (foundMatches.empty())
            {
                std::cout << "unsuccessful\n";
            }
            // Matches found, will now print
            else
            {
                for (size_t j = 0; j < foundMatches.size(); ++j)
                {
                    std::cout << foundMatches[j] << '\n';
                }
            }
        }
        // search ID
        else if (currentCommand.substr(0, 7) == "search ")
        {
            // Grab student id
            std::string studentId = currentCommand.substr(7);
            // Run id checks
            bool idCheck = IdChecker(studentId);

            if (!idCheck)
            {
                std::cout << "unsuccessful\n";
                continue;
            }

            int convertedStudentId{ stoi(studentId) };

            // Search for student with given id
            Student* foundStudent
            { ourTree->SearchId(convertedStudentId) };

            // If student was found, will not be null
            if (foundStudent != nullptr)
            {
                std::cout << foundStudent->nameGet() << '\n';
            }
            else
            {
                std::cout << "unsuccessful\n";
            }
        }
        // printInorder
        else if (currentCommand == "printInorder")
        {
            ourTree->printInorder(ourTree->GetRoot(), 
                ourTree->SearchRightmostNode(ourTree->GetRoot()));
        }
        // printPreorder
        else if (currentCommand == "printPreorder")
        {
            ourTree->printPreorder(ourTree->GetRoot(),
                ourTree->SearchRightmostNode(ourTree->GetRoot()));
        }
        // printPostorder
        else if (currentCommand == "printPostorder")
        {
            ourTree->printPostorder(ourTree->GetRoot());
        }
        // printLevelCount
        else if (currentCommand == "printLevelCount")
        {
            ourTree->printLevelCount();
        }
        // removeInorder N
        else if (currentCommand.substr(0, 14) == "removeInorder ")
        {
            // Make sure something follows after removeInorder
            if (!(currentCommand.substr(0).length() > 14))
            {
                std::cout << "unsuccessful\n";
                continue;
            }

            // Grab "n" from input
            std::string n{ currentCommand.substr(14) };

            // Check "n" for validity
            if ((NCheck(n)) && (stoi(n) < static_cast<int>((ourTree->GetNodeCount()))))
            {
                // Grab ID of student to remove
                int nthToRemove{ stoi(n) };

                // Call removeInorder
                ourTree->removeInorder(nthToRemove);
            }
            else
            {
                std::cout << "unsuccessful\n";
                continue;
            }
        }
        // TESTING
        else if (currentCommand == "testing1")
        {
            ourTree->InsertStudent("Steve", 9);
            ourTree->InsertStudent("Tom", 12);
            ourTree->InsertStudent("Joey", 7);
            ourTree->InsertStudent("Hunter", 16);
            ourTree->InsertStudent("John", 14);
            //ourTree->InsertStudent("Sam", 16);
        }
        else if (currentCommand == "testing2")
        {
            ourTree->InsertStudent("Steve", 75);
            ourTree->InsertStudent("Tom", 89);
            ourTree->InsertStudent("Joey", 13);
            ourTree->InsertStudent("Hunter", 7);
            ourTree->InsertStudent("John", 95);
            ourTree->InsertStudent("Sam", 45);
            ourTree->InsertStudent("Uncle", 37);
        }
        else if (currentCommand == "testing3")
        {
            ourTree->InsertStudent("Steve", 10293847);
            ourTree->InsertStudent("Tom", 29384728);
            ourTree->InsertStudent("Joey", 10392039);
            ourTree->InsertStudent("Hunter", 29586738);
            ourTree->InsertStudent("John", 48522990);
            ourTree->InsertStudent("Jacob", 99302493);
            ourTree->InsertStudent("Uncle", 83728394);
        }
        else if (currentCommand == "testing4")
        {
            ourTree->InsertStudent("Brandon", 45674567);
            ourTree->InsertStudent("Brian", 35455565);
            ourTree->InsertStudent("Briana", 87878787);
            ourTree->InsertStudent("Bella", 95462138);
        }
        else if (currentCommand == "testingLR")
        {
            ourTree->InsertStudent("Steve", 44958256);
            ourTree->InsertStudent("Tom", 87878787);
            ourTree->InsertStudent("Joey", 99999999);

            ourTree->printInorder(ourTree->GetRoot(),
                ourTree->SearchRightmostNode(ourTree->GetRoot()));

            ourTree->InsertStudent("Hunter", 16344444);

            ourTree->RemoveStudent(99999999);

            ourTree->printInorder(ourTree->GetRoot(),
                ourTree->SearchRightmostNode(ourTree->GetRoot()));

            ourTree->RemoveStudent(44958256);

            ourTree->printInorder(ourTree->GetRoot(),
                ourTree->SearchRightmostNode(ourTree->GetRoot()));
        }
        else
        {
            std::cout << "unsuccessful\n";
        }
    }

    delete ourTree;

    return 0;
}

bool NameChecker(std::string name)
{
    // Check if name is not empty
    if (name.length() == 0)
    {
        return false;
    }

    // Check if name includes only letters and spaces
    for (size_t i = 0; i < name.length(); ++i)
    {
        // Check if character is a letter or space
        if (std::isalpha(name[i]) || std::isblank(name[i])) { continue; }
        // Return false if neither are true
        else { return false; }
    }

    // All checks passed
    return true;
}

bool IdChecker(std::string id)
{
    if (id.length() != 8)
    {
        return false;
    }

    // Check if id includes only numbers
    for (size_t i = 0; i < id.length(); ++i)
    {
        // Check if character is a digit
        if (std::isdigit(id[i])) { continue; }
        // Return false if not a digit/number
        else { return false; }
    }

    // All checks passed
    return true;
}

bool NCheck(std::string n)
{
    // "n" must be all digits
    for (size_t j = 0; j < n.size(); ++j)
    {
        if (isdigit(n[j]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    // All checks passed
    return true;
}

// TESTS
// Removal at root (Yes!)
// Left Rotation (Yes!)

// TODO:
// Adjust functions in public to private for Tree and Student
// See where to pass references or pointers instead of copying

