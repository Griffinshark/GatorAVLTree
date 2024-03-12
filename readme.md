# Introduction
This is a project that was designed as an AVL (Self-Balancing Binary Search Tree) for organizing UF student accounts based on an ID number. 

# Installation
Simply clone the repo and run from main.

# Runtime Guide 
1. Enter the number of commands to input
2. Enter commands

**Available Commands:**
- insert NAME ID: Adds a student with their 8-digit ID number
- remove ID: Remove the ID from the tree
- search ID: Search for a student by their ID
- search NAME: Search for a student by their name
- printInorder: Print the inorder traversal of the tree
- printPreorder: Print the preorder traversal of the tree
- printPostorder: Print the postorder traversal of the tree
- printLevelCount: Print the level count of the tree
- removeInorder N: Remove an "nth" student in the tree by inorder traversal.

# Constraints
- 1 <= No. of Commands <= 1000
- 1 <= Unique UFIDs <= 100,000
- 1 <= Length of a command <= 1000
- A command will always run for a single line and will never contain new line characters ('\n'), except at the end.

