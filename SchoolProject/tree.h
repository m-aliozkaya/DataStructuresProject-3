
#include "student.h"
#include <fstream>

using namespace std;

// Aðaç yapýsý 
struct StudentTree
{
	StudentNode* root;
	int nodeSize;
	string filePath;
	ofstream fileWriter;
	void ClearTree(StudentNode*);
	void LoadTree();
	void AddNode(StudentNode*);
	void DeleteNode(StudentNode**);
	void SaveTree();
	void WritePreOrdered(StudentNode*);
	void CreateTree(string path);
	void DeleteStudent();
	void ListStudents();
	void ListInOrdered(StudentNode* root);
	void ListPreOrdered(StudentNode* root);
	void ListPostOrdered(StudentNode* root);
	void SearchStudent();
	void SearchDepthFirst(string number);
	void SearchBreadthFirst(string number);
	void CloseTree();
};

