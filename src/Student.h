#pragma once
#include <string>

class Student
{
public:
	Student(std::string studentName, int studentId, Student* parent);
	~Student();
	int studentIdGet();
	Student* leftGet();
	Student* rightGet();
	Student* parentGet();
	size_t heightGet();
	std::string nameGet();
	void leftSet(Student* _leftChild);
	void rightSet(Student* _rightChild);
	void parentSet(Student* _parent);
	void heightSet(size_t newHeight);
	void heightDec();
	void heightInc();



private:
	std::string studentName{""};
	int studentId{ 0 };
	size_t nodeHeight{ 1 }; // Height is "1" for leaf
	Student* parent{ nullptr };
	Student* leftChild{ nullptr };
	Student* rightChild{ nullptr };
};

