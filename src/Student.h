#pragma once
#include <string>

class Student
{
public:
	Student(std::string studentName, int studentId, Student* parent);  // Non-default Constructor
	~Student(); // Default destructor
	int studentIdGet() const; // Student ID getter
	Student* leftGet(); // Left child getter
	Student* rightGet(); // Right child getter
	Student* parentGet(); // Parent getter
	size_t heightGet() const; // Node height getter
	std::string nameGet(); // Student name getter
	void leftSet(Student* _leftChild); // Left child setter
	void rightSet(Student* _rightChild); // Right child setter
	void parentSet(Student* _parent); // Parent setter
	void heightSet(size_t newHeight); // Node height setter

private:
	std::string studentName; // Stores the student's name
	int studentId{ 0 }; // Stores the student's ID
	size_t nodeHeight{ 1 }; // Height is "1" for leaf; Stores the student's/node's height
	Student* parent{ nullptr }; // Stores node's parent
	Student* leftChild{ nullptr }; // Stores node's left child
	Student* rightChild{ nullptr }; // Stores node's right child
};

