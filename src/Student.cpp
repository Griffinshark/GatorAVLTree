#include "Student.h"
#include <utility>

Student::Student(std::string studentName, int studentId, Student* parent) 
	: studentName(std::move(studentName)), studentId(studentId), parent(parent) {}

Student::~Student() = default;

int Student::studentIdGet() const { return this->studentId; }
Student* Student::leftGet() { return this->leftChild; }
Student* Student::rightGet() { return this->rightChild; }
Student* Student::parentGet() { return this->parent; }
size_t Student::heightGet() const { return nodeHeight; }
std::string Student::nameGet() { return studentName; }
void Student::leftSet(Student* _leftChild) { this->leftChild = _leftChild; }
void Student::rightSet(Student* _rightChild) { this->rightChild = _rightChild; }
void Student::parentSet(Student* _parent) { this->parent = _parent; }
void Student::heightSet(size_t newHeight) { this->nodeHeight = newHeight; }
