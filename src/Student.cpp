#include "Student.h"

Student::Student(std::string studentName, int studentId, Student* parent) 
	: studentName(studentName), studentId(studentId), parent(parent) {}

Student::~Student() {}

int Student::studentIdGet() { return this->studentId; }
Student* Student::leftGet() { return this->leftChild; }
Student* Student::rightGet() { return this->rightChild; }
Student* Student::parentGet() { return this->parent; }
size_t Student::heightGet() { return nodeHeight; }
std::string Student::nameGet() { return studentName; }
void Student::leftSet(Student* _leftChild) { this->leftChild = _leftChild; }
void Student::rightSet(Student* _rightChild) { this->rightChild = _rightChild; }
void Student::parentSet(Student* _parent) { this->parent = _parent; }
void Student::heightSet(size_t newHeight) { this->nodeHeight = newHeight; }

void Student::heightDec() { this->nodeHeight--; }

void Student::heightInc() { this->nodeHeight++; }
